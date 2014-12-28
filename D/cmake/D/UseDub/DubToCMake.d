import std.file;
import std.getopt;
import std.json;
import std.stdio;
import std.string;

int main(string[] args)
{
    string dubFile = "dub.json";
    string cmakeFile = "CMakeLists.txt";

    getopt(args,
           "package|p", &dubFile,
           "output|o", &cmakeFile);

    if (!exists(dubFile))
    {
        stderr.writefln("Cannot find file: '%s'", dubFile);
        return -1;
    }

    string json = readText(dubFile);
    JSONValue root = parseJSON(json);
    string target = root["targetName"].str;

    string cmake = q"<
cmake_minimum_required(VERSION 2.8)

project(%1$s D)

find_file(APP_MAIN_FILE
    NAMES app.d main.d %1$s/main.d %1$s/app.d
    PATHS source src NO_DEFAULT_PATH)

file(GLOB_RECURSE SRC_FILES source/*.d src/*.d)
if(APP_MAIN_FILE)
    list(REMOVE_ITEM SRC_FILES ${APP_MAIN_FILE})
endif(APP_MAIN_FILE)

include_directories(source src)
>".format(root["name"].str);

    switch ("targetType" in root.object ? root["targetType"].str : "autodetect")
    {
        case "autodetect":
            cmake ~= q"<
if(APP_MAIN_FILE)
    add_executable(%1$s ${SRC_FILES} ${APP_MAIN_FILE})
else(APP_MAIN_FILE)
    add_library(%1$s ${SRC_FILES})
endif(APP_MAIN_FILE)
>".format(target);
            break;
        case "none":
            break;
        case "executable":
            cmake ~= q"<
add_executable(%s ${SRC_FILES} ${APP_MAIN_FILE})
>".format(target);
            break;
        case "library":
            cmake ~= q"<
add_library(%s ${SRC_FILES})
>".format(target);
            break;
        case "sourceLibrary":
            break;
        case "staticLibrary":
            cmake ~= q"<
add_library(%s STATIC ${SRC_FILES})
>".format(target);
            break;
        case "dynamicLibrary":
            cmake ~= q"<
add_library(%s SHARED ${SRC_FILES})
>".format(target);
            break;
        default:
            assert(false, "Unknown targetType");
            break;
    }

    cmake ~= q"<
install(TARGETS %s
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
>".format(target);

    if ("dependencies" in root.object)
    {
        cmake ~= "\ninclude(UseDub)\n";
        foreach (dependency, version_; root["dependencies"].object)
        {
            cmake ~= "DubProject_Add(%s %s)\n".format(dependency, version_.str);
        }
        cmake ~= "\nadd_dependencies(%s %-(%s %))\n".format(target, root["dependencies"].object.keys);
    }

    std.file.write(cmakeFile, cmake);

    return 0;
}
