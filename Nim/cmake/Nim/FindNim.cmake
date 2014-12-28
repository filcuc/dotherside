include(CMakeParseArguments)

find_program(NIM_EXECUTABLE nim PATHS ENV PATH)
mark_as_advanced(NIM_EXECUTABLE)

# Determine the nimrod version
if(NIM_EXECUTABLE)
    execute_process(COMMAND ${NIM_EXECUTABLE} "--version" 
        OUTPUT_VARIABLE NIM_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    STRING(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" NIM_VERSION ${NIM_VERSION})
endif(NIM_EXECUTABLE)

# Handle the QUIETLY and REQUIRED arguments, which may be given to the find call.
# set NIM_FOUND to TRUE if Nimrod has been found 

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Nim
    REQUIRED_VARS NIM_EXECUTABLE
    VERSION_VAR NIM_VERSION)

set(NIM_USE_FILE "${CMAKE_CURRENT_LIST_DIR}/UseNim.cmake")