import std.algorithm;
import std.array;
import std.conv;
import std.range;
import std.regex;
import std.stdio;
import std.string;

enum ReleaseType
{
    MAJOR,
    MINOR,
    PATCH,
    PRERELEASE,
};

struct SemVer
{
    uint[3] ids;
    string[] prerelease;
    string[] build;

    bool isValid;

    @disable this();

    this(string semVer)
    {
        isValid = false;
        if (semVer.empty)
            return;
        if (!semVer.skipOver('v'))
            semVer.skipOver('=');

        auto re = regex(`^(\d+)(?:\.(\d+))?(?:\.(\d+))?(?:-([a-zA-Z\d-.]+))?(?:\+([a-zA-Z\d-.]+))?$`);
        auto m = semVer.matchAll(re);
        if (m.empty)
            return;

        foreach (i, ref id; ids)
        {
            if (!m.captures[i+1].empty)
                id = m.captures[i+1].to!uint;
        }

        if (!m.captures[4].empty)
        {
            prerelease = m.captures[4].splitter('.').array;
            if (prerelease.any!empty)
                return;
        }

        if (!m.captures[5].empty)
        {
            build = m.captures[5].splitter('.').array;
            if (build.any!empty)
                return;
        }

        isValid = true;
    }

    string toString() const
    {
        if (!isValid)
            return "<invalid_semver>";

        string semVer = "%(%s.%)".format(ids);
        if (!prerelease.empty)
            semVer ~= "-" ~ "%-(%s.%)".format(prerelease);
        if (!build.empty)
            semVer ~= "+" ~ "%-(%s.%)".format(build);
        return semVer;
    }

    @property bool valid() const
    {
        return isValid;
    }

    SemVer inc(ReleaseType releaseType) const
    in
    {
        assert(this.valid);
    }
    out(result)
    {
        assert(result.valid);
    }
    body
    {
        SemVer result = "0";
        foreach (i; 0..releaseType)
            result.ids[i] = this.ids[i];
        if (releaseType != ReleaseType.PRERELEASE)
            result.ids[releaseType] = this.ids[releaseType]+1;
        return result;
    }

    SemVer appendPrerelease0()
    {
        if (prerelease.empty)
            prerelease ~= "0";
        return this;
    }

    unittest
    {
        assert(SemVer("1.2.3").inc(ReleaseType.MAJOR) == SemVer("2.0.0"));
        assert(SemVer("1.2.3").inc(ReleaseType.MINOR) == SemVer("1.3.0"));
        assert(SemVer("1.2.3-alpha").inc(ReleaseType.MINOR) == SemVer("1.3.0"));
        assert(SemVer("1.2.3").inc(ReleaseType.PATCH) == SemVer("1.2.4"));
        assert(SemVer("1.2.3-alpha").inc(ReleaseType.PATCH) == SemVer("1.2.4"));
        assert(SemVer("1.2.3").inc(ReleaseType.PRERELEASE) == SemVer("1.2.3"));
        assert(SemVer("1.2.3-alpha").inc(ReleaseType.PRERELEASE) == SemVer("1.2.3"));
    }

    int opCmp(ref const SemVer v) const
    in
    {
        assert(this.valid);
        assert(v.valid);
    }
    body
    {
        foreach (i; 0..ids.length)
        {
            if (ids[i] != v.ids[i])
                return ids[i] < v.ids[i] ? -1 : 1;
        }

        if (!prerelease.empty && v.prerelease.empty)
            return -1;
        if (prerelease.empty && !v.prerelease.empty)
            return 1;

        foreach (a, b; lockstep(prerelease, v.prerelease))
        {
            if (a.isNumeric && b.isNumeric)
            {
                if (a.to!uint != b.to!uint)
                    return a.to!uint < b.to!uint ? -1 : 1;
                else
                    continue;
            }
            if (a != b)
                return a < b ? -1 : 1;
        }
        if (prerelease.length != v.prerelease.length)
            return prerelease.length < v.prerelease.length ? -1 : 1;

        return 0;
    }

    int opCmp(const SemVer v) const
    {
        return this.opCmp(v);
    }

    bool opEquals(ref const SemVer v) const
    {
        return this.opCmp(v) == 0;
    }

    bool opEquals(const SemVer v) const
    {
        return this.opEquals(v);
    }
}

unittest
{
    assert(!SemVer("1.2-.alpha.32").valid);
    assert(!SemVer("1.2-alpha+").valid);
    assert(!SemVer("1.2-alpha_").valid);
    assert(!SemVer("1.2+32.").valid);
    assert(!SemVer("1.2.5.6").valid);
    assert(!SemVer("").valid);
    assert(SemVer("1.0.0-alpha") < SemVer("1.0.0-alpha.1"));
    assert(SemVer("1.0.0-alpha.1") < SemVer("1.0.0-alpha.beta"));
    assert(SemVer("1.0.0-alpha.beta") < SemVer("1.0.0-beta"));
    assert(SemVer("1.0.0-beta") < SemVer("1.0.0-beta.2"));
    assert(SemVer("1.0.0-beta.2") < SemVer("1.0.0-beta.11"));
    assert(SemVer("1.0.0-beta.11") < SemVer("1.0.0-rc.1"));
    assert(SemVer("1.0.0-rc.1") < SemVer("1.0.0"));
    assert(SemVer("1.0.0-rc.1") == SemVer("1.0.0-rc.1+build.5"));
}

struct SemVerRange
{
    struct SimpleRange
    {
        string op;
        SemVer semVer;

        string toString() const
        {
            return op ~ semVer.toString;
        }
    }

    SimpleRange[][] ranges;

    invariant()
    {
        assert(ranges.all!(r => r.all!(r => ["<", "<=", "=", ">=", ">"].canFind(r.op))));
    }

    bool isValid;

    @disable this();

    this(string semVerRange)
    {
        isValid = false;
        auto re = regex(`(~|~>|\^|<|<=|=|>=|>)?[v]?(\d+|\*|X|x)(?:\.(\d+|\*|X|x))?(?:\.(\d+|\*|X|x))?([\S]*)`);

        ranges = [SimpleRange[].init];

        while (!semVerRange.stripLeft.empty)
        {
            auto m = semVerRange.matchFirst(re);
            if (m.empty)
                return;

            auto operator = m.captures[1];
            auto wildcard = wildcardAt([m.captures[2], m.captures[3], m.captures[4]]);
            auto expanded = expand([m.captures[2], m.captures[3], m.captures[4], m.captures[5]]);
            if (expanded.empty)
                return;

            auto semVer = SemVer(expanded);
            if (!semVer.valid)
                return;

            switch (m.captures.pre.strip)
            {
                case "":
                    break;
                case "-":
                    if (ranges[$-1].empty || ranges[$-1][$-1].op != "=" ||
                        operator != "" || wildcard != ReleaseType.PRERELEASE)
                        return;
                    ranges[$-1][$-1].op = ">=";
                    operator = "<=";
                    break;
                case "||":
                    ranges ~= SimpleRange[].init;
                    break;
                default:
                    return;
            }

            switch (operator)
            {
                case "":
                case "=":
                    final switch (wildcard)
                    {
                        case ReleaseType.MAJOR:
                            assert(semVer == SemVer("0.0.0"));
                            ranges[$-1] ~= SimpleRange(">=", semVer.appendPrerelease0);
                            break;
                        case ReleaseType.MINOR:
                        case ReleaseType.PATCH:
                            ranges[$-1] ~= SimpleRange(">=", semVer.appendPrerelease0);
                            ranges[$-1] ~= SimpleRange("<", semVer.inc(--wildcard).appendPrerelease0);
                            break;
                        case ReleaseType.PRERELEASE:
                            ranges[$-1] ~= SimpleRange("=", semVer);
                            break;
                    }
                    break;
                case "<":
                    ranges[$-1] ~= SimpleRange(operator, semVer.appendPrerelease0);
                    break;
                case "<=":
                case ">=":
                case ">":
                    if (wildcard < ReleaseType.PRERELEASE)
                        semVer.appendPrerelease0;
                    ranges[$-1] ~= SimpleRange(operator, semVer);
                    break;
                case "~":
                    final switch (wildcard)
                    {
                        case ReleaseType.MAJOR:
                            return;
                        case ReleaseType.MINOR:
                        case ReleaseType.PATCH:
                            --wildcard;
                            break;
                        case ReleaseType.PRERELEASE:
                            --wildcard;
                            --wildcard;
                            break;
                    }
                    ranges[$-1] ~= SimpleRange(">=", semVer.appendPrerelease0);
                    ranges[$-1] ~= SimpleRange("<", semVer.inc(wildcard).appendPrerelease0);
                    break;
                case "~>":
                    final switch (wildcard)
                    {
                        case ReleaseType.MAJOR:
                            return;
                        case ReleaseType.MINOR:
                            --wildcard;
                            break;
                        case ReleaseType.PATCH:
                        case ReleaseType.PRERELEASE:
                            --wildcard;
                            --wildcard;
                            break;
                    }
                    ranges[$-1] ~= SimpleRange(">=", semVer.appendPrerelease0);
                    ranges[$-1] ~= SimpleRange("<", semVer.inc(wildcard).appendPrerelease0);
                    break;
                case "^":
                    if (wildcard == ReleaseType.MAJOR || !semVer.prerelease.empty)
                        return;
                    if (semVer.ids[ReleaseType.MAJOR] != 0)
                    {
                        ranges[$-1] ~= SimpleRange(">=", semVer.appendPrerelease0);
                        ranges[$-1] ~= SimpleRange("<", semVer.inc(ReleaseType.MAJOR).appendPrerelease0);
                    }
                    else if (semVer.ids[ReleaseType.MINOR] != 0)
                    {
                        ranges[$-1] ~= SimpleRange(">=", semVer.appendPrerelease0);
                        ranges[$-1] ~= SimpleRange("<", semVer.inc(ReleaseType.MINOR).appendPrerelease0);
                    } 
                    else
                    {
                        ranges[$-1] ~= SimpleRange(">=", semVer.appendPrerelease0);
                        ranges[$-1] ~= SimpleRange("<", semVer.inc(ReleaseType.PATCH).appendPrerelease0);
                    }
                    break;
                default:
                    assert(0);
                    break;
            }
            semVerRange = m.captures.post;
        }
        isValid = true;
    }

    private static ReleaseType wildcardAt(string[3] semVer)
    {
        foreach (i; ReleaseType.MAJOR..ReleaseType.PRERELEASE)
        {
            if (["", "*", "X", "x"].canFind(semVer[i]))
                return i;
        }
        return ReleaseType.PRERELEASE;
    }

    unittest
    {
        assert(wildcardAt(["*", "", ""]) == ReleaseType.MAJOR);
        assert(wildcardAt(["X", "", ""]) == ReleaseType.MAJOR);
        assert(wildcardAt(["1", "", ""]) == ReleaseType.MINOR);
        assert(wildcardAt(["1", "x", ""]) == ReleaseType.MINOR);
        assert(wildcardAt(["1", "2", ""]) == ReleaseType.PATCH);
        assert(wildcardAt(["1", "2", "x"]) == ReleaseType.PATCH);
        assert(wildcardAt(["1", "2", "3"]) == ReleaseType.PRERELEASE);
    }

    private static string expand(string[4] semVer)
    {
        ReleaseType wildcard = wildcardAt(semVer[0..3]);
        if (wildcard != ReleaseType.PRERELEASE)
        {
            if (semVer[wildcard+1..$].any!`!["", "*", "X", "x"].canFind(a)`)
                return "";
            foreach (j; wildcard..ReleaseType.PRERELEASE)
                semVer[j] = "0";
        }
        string result = "%-(%s.%)".format(semVer[0..3]);
        if (!semVer[3].empty)
            result ~= semVer[3];
        return result;
    }

    unittest
    {
        assert(expand(["*", "", "", ""]) == "0.0.0");
        assert(expand(["X", "", "", ""]) == "0.0.0");
        assert(expand(["1", "2", "3", ""]) == "1.2.3");
        assert(expand(["1", "2", "3", "-abc"]) == "1.2.3-abc");
        assert(expand(["1", "2", "", ""]) == "1.2.0");
        assert(expand(["1", "2", "", "-abc"]) == "");
        assert(expand(["1", "2", "x", ""]) == "1.2.0");
        assert(expand(["1", "", "", ""]) == "1.0.0");
        assert(expand(["1", "x", "", ""]) == "1.0.0");
    }

    string toString() const
    {
        if (!isValid)
            return "<invalid_semver_range>";

        return "%(%(%s %) || %)".format(ranges);
    }

    @property bool valid() const
    {
        return isValid;
    }

    private static bool simpleRangeSatisfiedBy(SimpleRange simpleRange, SemVer semVer)
    in
    {
        assert(semVer.valid);
        assert(["<", "<=", "=", ">=", ">"].canFind(simpleRange.op));
        assert(simpleRange.semVer.valid);
    }
    body
    {
        switch (simpleRange.op)
        {
            case "<":
                return semVer < simpleRange.semVer;
            case "<=":
                return semVer <= simpleRange.semVer;
            case "=":
                return semVer == simpleRange.semVer;
            case ">=":
                return semVer >= simpleRange.semVer;
            case ">":
                return semVer > simpleRange.semVer;
            default:
                return false;
        }
    }

    bool satisfiedBy(SemVer semVer)
    in
    {
        assert(semVer.valid);
        assert(valid);
    }
    body
    {
        return ranges.any!(r => r.all!(s => simpleRangeSatisfiedBy(s, semVer)));
    }

}

bool satisfies(SemVer semVer, SemVerRange semVerRange)
{
    return semVerRange.satisfiedBy(semVer);
}

SemVer maxSatisfying(SemVer[] semVers, SemVerRange semVerRange)
in
{
    assert(semVers.all!"a.valid");
    assert(semVerRange.valid);
}
body
{
    auto found = semVers.sort!"a > b".find!(a => satisfies(a, semVerRange));
    return found.empty ? SemVer("invalid") : found[0];
}

unittest
{
    assert(SemVerRange("1.x || >=2.5.0 || 5.0.0 - 7.2.3").valid);
    assert(!SemVerRange("blerg").valid);
    assert(!SemVerRange("git+https://user:password0123@github.com/foo").valid);

    assert(SemVer("1.2.3").satisfies(SemVerRange("1.x || >=2.5.0 || 5.0.0 - 7.2.3")));

    assert(SemVer("1.2.3").satisfies(SemVerRange("1.0.0 - 2.0.0")));
    assert(SemVer("1.0.0").satisfies(SemVerRange("1.0.0")));
    assert(SemVer("0.2.4").satisfies(SemVerRange(">=*")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("*")));
    assert(SemVer("v1.2.3-foo").satisfies(SemVerRange("*")));
    assert(SemVer("1.0.0").satisfies(SemVerRange(">=1.0.0")));
    assert(SemVer("1.0.1").satisfies(SemVerRange(">=1.0.0")));
    assert(SemVer("1.1.0").satisfies(SemVerRange(">=1.0.0")));
    assert(SemVer("1.0.1").satisfies(SemVerRange(">1.0.0")));
    assert(SemVer("1.1.0").satisfies(SemVerRange(">1.0.0")));
    assert(SemVer("2.0.0").satisfies(SemVerRange("<=2.0.0")));
    assert(SemVer("1.9999.9999").satisfies(SemVerRange("<=2.0.0")));
    assert(SemVer("0.2.9").satisfies(SemVerRange("<=2.0.0")));
    assert(SemVer("1.9999.9999").satisfies(SemVerRange("<2.0.0")));
    assert(SemVer("0.2.9").satisfies(SemVerRange("<2.0.0")));
    assert(SemVer("1.0.0").satisfies(SemVerRange(">=1.0.0")));
    assert(SemVer("1.0.1").satisfies(SemVerRange(">=1.0.0")));
    assert(SemVer("1.1.0").satisfies(SemVerRange(">=1.0.0")));
    assert(SemVer("1.0.1").satisfies(SemVerRange(">1.0.0")));
    assert(SemVer("1.1.0").satisfies(SemVerRange(">1.0.0")));
    assert(SemVer("2.0.0").satisfies(SemVerRange("<=2.0.0")));
    assert(SemVer("1.9999.9999").satisfies(SemVerRange("<=2.0.0")));
    assert(SemVer("0.2.9").satisfies(SemVerRange("<=2.0.0")));
    assert(SemVer("1.9999.9999").satisfies(SemVerRange("<2.0.0")));
    assert(SemVer("0.2.9").satisfies(SemVerRange("<2.0.0")));
    assert(SemVer("v0.1.97").satisfies(SemVerRange(">=0.1.97")));
    assert(SemVer("0.1.97").satisfies(SemVerRange(">=0.1.97")));
    assert(SemVer("1.2.4").satisfies(SemVerRange("0.1.20 || 1.2.4")));
    assert(SemVer("0.0.0").satisfies(SemVerRange(">=0.2.3 || <0.0.1")));
    assert(SemVer("0.2.3").satisfies(SemVerRange(">=0.2.3 || <0.0.1")));
    assert(SemVer("0.2.4").satisfies(SemVerRange(">=0.2.3 || <0.0.1")));
    assert(SemVer("2.1.3").satisfies(SemVerRange("2.x.x")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("1.2.x")));
    assert(SemVer("2.1.3").satisfies(SemVerRange("1.2.x || 2.x")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("1.2.x || 2.x")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("x")));
    assert(SemVer("2.1.3").satisfies(SemVerRange("2.*.*")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("1.2.*")));
    assert(SemVer("2.1.3").satisfies(SemVerRange("1.2.* || 2.*")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("1.2.* || 2.*")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("*")));
    assert(SemVer("2.1.2").satisfies(SemVerRange("2")));
    assert(SemVer("2.3.1").satisfies(SemVerRange("2.3")));
    assert(SemVer("2.4.0").satisfies(SemVerRange("~2.4")));
    assert(SemVer("2.4.5").satisfies(SemVerRange("~2.4")));
    assert(SemVer("3.2.2").satisfies(SemVerRange("~>3.2.1")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~1")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~>1")));
    assert(SemVer("1.0.2").satisfies(SemVerRange("~1.0")));
    assert(SemVer("1.0.12").satisfies(SemVerRange("~1.0.3")));
    assert(SemVer("1.0.0").satisfies(SemVerRange(">=1")));
    assert(SemVer("1.1.1").satisfies(SemVerRange("<1.2")));
    assert(SemVer("1.1.9").satisfies(SemVerRange("<=1.2")));
    assert(SemVer("1.0.0-bet").satisfies(SemVerRange("1")));
    assert(SemVer("0.5.5").satisfies(SemVerRange("~v0.5.4-pre")));
    assert(SemVer("0.5.4").satisfies(SemVerRange("~v0.5.4-pre")));
    assert(SemVer("0.7.2").satisfies(SemVerRange("=0.7.x")));
    assert(SemVer("0.7.2").satisfies(SemVerRange(">=0.7.x")));
    assert(SemVer("0.7.0-asdf").satisfies(SemVerRange("=0.7.x")));
    assert(SemVer("0.7.0-asdf").satisfies(SemVerRange(">=0.7.x")));
    assert(SemVer("0.6.2").satisfies(SemVerRange("<=0.7.x")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~1.2.1 >=1.2.3")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~1.2.1 =1.2.3")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~1.2.1 1.2.3")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~1.2.1 >=1.2.3 1.2.3")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~1.2.1 1.2.3 >=1.2.3")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("~1.2.1 1.2.3")));
    assert(SemVer("1.2.3").satisfies(SemVerRange(">=1.2.1 1.2.3")));
    assert(SemVer("1.2.3").satisfies(SemVerRange("1.2.3 >=1.2.1")));
    assert(SemVer("1.2.3").satisfies(SemVerRange(">=1.2.3 >=1.2.1")));
    assert(SemVer("1.2.3").satisfies(SemVerRange(">=1.2.1 >=1.2.3")));
    assert(SemVer("1.2.3-beta").satisfies(SemVerRange("<=1.2.3")));
    assert(SemVer("1.3.0-beta").satisfies(SemVerRange(">1.2")));
    assert(SemVer("1.2.8").satisfies(SemVerRange(">=1.2")));
    assert(SemVer("1.8.1").satisfies(SemVerRange("^1.2.3")));
    assert(SemVer("1.2.3-beta").satisfies(SemVerRange("^1.2.3")));
    assert(SemVer("0.1.2").satisfies(SemVerRange("^0.1.2")));
    assert(SemVer("0.1.2").satisfies(SemVerRange("^0.1")));
    assert(SemVer("1.4.2").satisfies(SemVerRange("^1.2")));
    assert(SemVer("1.4.2").satisfies(SemVerRange("^1.2 ^1")));
    assert(SemVer("1.2.0-pre").satisfies(SemVerRange("^1.2")));
    assert(SemVer("1.2.3-pre").satisfies(SemVerRange("^1.2.3")));

    assert(!SemVer("2.2.3").satisfies(SemVerRange("1.0.0 - 2.0.0")));
    assert(!SemVer("1.0.1").satisfies(SemVerRange("1.0.0")));
    assert(!SemVer("0.0.0").satisfies(SemVerRange(">=1.0.0")));
    assert(!SemVer("0.0.1").satisfies(SemVerRange(">=1.0.0")));
    assert(!SemVer("0.1.0").satisfies(SemVerRange(">=1.0.0")));
    assert(!SemVer("0.0.1").satisfies(SemVerRange(">1.0.0")));
    assert(!SemVer("0.1.0").satisfies(SemVerRange(">1.0.0")));
    assert(!SemVer("3.0.0").satisfies(SemVerRange("<=2.0.0")));
    assert(!SemVer("2.9999.9999").satisfies(SemVerRange("<=2.0.0")));
    assert(!SemVer("2.2.9").satisfies(SemVerRange("<=2.0.0")));
    assert(!SemVer("2.9999.9999").satisfies(SemVerRange("<2.0.0")));
    assert(!SemVer("2.2.9").satisfies(SemVerRange("<2.0.0")));
    assert(!SemVer("v0.1.93").satisfies(SemVerRange(">=0.1.97")));
    assert(!SemVer("0.1.93").satisfies(SemVerRange(">=0.1.97")));
    assert(!SemVer("1.2.3").satisfies(SemVerRange("0.1.20 || 1.2.4")));
    assert(!SemVer("0.0.3").satisfies(SemVerRange(">=0.2.3 || <0.0.1")));
    assert(!SemVer("0.2.2").satisfies(SemVerRange(">=0.2.3 || <0.0.1")));
    assert(!SemVer("1.1.3").satisfies(SemVerRange("2.x.x")));
    assert(!SemVer("3.1.3").satisfies(SemVerRange("2.x.x")));
    assert(!SemVer("1.3.3").satisfies(SemVerRange("1.2.x")));
    assert(!SemVer("3.1.3").satisfies(SemVerRange("1.2.x || 2.x")));
    assert(!SemVer("1.1.3").satisfies(SemVerRange("1.2.x || 2.x")));
    assert(!SemVer("1.1.3").satisfies(SemVerRange("2.*.*")));
    assert(!SemVer("3.1.3").satisfies(SemVerRange("2.*.*")));
    assert(!SemVer("1.3.3").satisfies(SemVerRange("1.2.*")));
    assert(!SemVer("3.1.3").satisfies(SemVerRange("1.2.* || 2.*")));
    assert(!SemVer("1.1.3").satisfies(SemVerRange("1.2.* || 2.*")));
    assert(!SemVer("1.1.2").satisfies(SemVerRange("2")));
    assert(!SemVer("2.4.1").satisfies(SemVerRange("2.3")));
    assert(!SemVer("2.5.0").satisfies(SemVerRange("~2.4")));
    assert(!SemVer("2.3.9").satisfies(SemVerRange("~2.4")));
    assert(!SemVer("3.3.2").satisfies(SemVerRange("~>3.2.1")));
    assert(!SemVer("3.2.0").satisfies(SemVerRange("~>3.2.1")));
    assert(!SemVer("0.2.3").satisfies(SemVerRange("~1")));
    assert(!SemVer("2.2.3").satisfies(SemVerRange("~>1")));
    assert(!SemVer("1.1.0").satisfies(SemVerRange("~1.0")));
    assert(!SemVer("1.0.0").satisfies(SemVerRange("<1")));
    assert(!SemVer("1.1.1").satisfies(SemVerRange(">=1.2")));
    assert(!SemVer("1.3.0").satisfies(SemVerRange("<=1.2")));
    assert(!SemVer("2.0.0-beta").satisfies(SemVerRange("1")));
    assert(!SemVer("0.5.4-alpha").satisfies(SemVerRange("~v0.5.4-beta")));
    assert(!SemVer("1.0.0-beta").satisfies(SemVerRange("<1")));
    assert(!SemVer("0.8.2").satisfies(SemVerRange("=0.7.x")));
    assert(!SemVer("0.6.2").satisfies(SemVerRange(">=0.7.x")));
    assert(!SemVer("0.7.2").satisfies(SemVerRange("<=0.7.x")));
    assert(!SemVer("1.2.3-beta").satisfies(SemVerRange("<1.2.3")));
    assert(!SemVer("1.2.3-beta").satisfies(SemVerRange("=1.2.3")));
    assert(!SemVer("1.2.8").satisfies(SemVerRange(">1.3")));
    assert(!SemVer("2.0.0-alpha").satisfies(SemVerRange("^1.2.3")));
    assert(!SemVer("1.2.2").satisfies(SemVerRange("^1.2.3")));
    assert(!SemVer("1.1.9").satisfies(SemVerRange("^1.2")));
    assert(!SemVer("2.0.0-pre").satisfies(SemVerRange("^1.2.3")));

    auto semVers = [SemVer("0.8.0"), SemVer("1.0.0"), SemVer("1.1.0")];
    assert(semVers.maxSatisfying(SemVerRange("<=1.0.0")) == SemVer("1.0.0"));
    assert(semVers.maxSatisfying(SemVerRange(">=1.0")) == SemVer("1.1.0"));
}
