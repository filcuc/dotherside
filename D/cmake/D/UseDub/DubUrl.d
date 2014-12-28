import std.algorithm;
import std.array;
import std.file;
import std.getopt;
import std.json;
import std.stdio;
import std.string;
import semver;

/**
 * Finds the best match of $(D range) in $(D choices) versions list.
 *
 * Params:
 * range = Match criteria.
 * choices = Versions list it is matched against.
 *
 * Returns:
 * Best match in $(D choices) or empty string if no match is found.
 *
 * See_Also:
 * $(WEB https://github.com/npm/npm/blob/master/doc/misc/semver.md#ranges Ranges definition)
 */
string matchVersion(string range, string[] choices)
{
    foreach (ref choice; choices)
    {
        choice.skipOver('~');
    }

    if (range.skipOver('~'))
    {
        foreach (choice; choices)
        {
            if (choice.startsWith(range))
                return choice;
        }
        return "";
    }

    return "";
}

unittest
{

}

int main(string[] args)
{
    string registryFile = "";
    string packageVersion = "";
    bool listVersions;
    string outputPath = ".";

    getopt(args,
           "package|p", &registryFile,
           "tag|t", &packageVersion,
           "list|l", &listVersions,
           "output|o", &outputPath);

    if (registryFile.empty)
    {
        stderr.writeln("Package registry file (<package_name>.json) need to be specified.");
        return -1;
    }

    if (!exists(registryFile) && !registryFile.endsWith(".json"))
        registryFile ~= ".json";

    if (!exists(registryFile))
    {
        stderr.writefln("Package registry file '%s' not found.", registryFile);
        return -1;
    }

    string json = readText(registryFile);
    JSONValue node;
    JSONValue root = parseJSON(json);

    if (packageVersion.empty)
    {
        packageVersion = "*";
    }

    auto versionRange = SemVerRange(packageVersion);

    if (!versionRange.valid)
    {
        // try exact string match
        auto range = root["versions"].array.find!`a["version"].str == b`(packageVersion);
        if (!range.empty)
        {
            node = range[0];
        }
        else
        {
            stderr.writefln("%s has no version tagged %s.", root["name"].str, packageVersion);
            return -1;
        }
    }
    else
    {
        string nodeVersionString(JSONValue node)
        {
            auto ver = node["version"].str;
            ver.skipOver('~');
            return ver;
        }

        auto nodes = root["versions"].array.filter!(a => SemVer(nodeVersionString(a)).valid).array;
        auto maxVersion = nodes.map!(a => SemVer(nodeVersionString(a))).array.maxSatisfying(versionRange);

        if (maxVersion.valid)
        {
            auto range = nodes.find!((a, b) => SemVer(nodeVersionString(a)) == b)(maxVersion);
            assert(!range.empty);
            node = range[0];
        }
        else
        {
            stderr.writefln("%s has no version %s.", root["name"].str, versionRange);
            return -1;
        }
    }

    if (registryFile.endsWith(".json"))
    {
        registryFile = registryFile[0..$-5];
    }   
    
    if (listVersions)
    {
        writefln("Package '%s'", registryFile);
        
        foreach(n; root["versions"].array)
        {
            writefln("  %s => %s", n["version"].str, n["downloadUrl"].str);
        }
    }

    packageVersion = node["version"].str;
    auto packageUrl = node["downloadUrl"].str;
    auto packageName = root["name"].str;

    if (!outputPath.isDir)
    {
        stderr.writefln("Output path '%s' need to be a directory.", outputPath);
        return -1;
    }

    string output = "set(DUB_PACKAGE_NAME, \"%s\")\n".format(packageName) ~
                    "set(DUB_PACKAGE_VERSION \"%s\")\n".format(packageVersion) ~
                    "set(DUB_PACKAGE_URL \"%s\")\n".format(packageUrl);

    std.file.write(outputPath ~ "/" ~ packageName ~ ".cmake", output);

    return 0;
}
