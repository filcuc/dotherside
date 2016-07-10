find_package(Doxygen)

if (DOXYGEN_FOUND)
  set(INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
  set(OUTPUT_FILE ${OUTPUT_DIR}/Doxyfile)
  configure_file(${INPUT_FILE} ${OUTPUT_FILE} @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${OUTPUT_FILE} WORKING_DIRECTORY ${OUTPUT_DIR} COMMENT "Generating the API documentation with Doxygen" VERBATIM)
endif()
