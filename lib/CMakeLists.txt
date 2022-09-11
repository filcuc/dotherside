include(GNUInstallDirs)

set(QTPREFIX "Qt")

find_package(Qt6 COMPONENTS Core Qml Gui Quick QuickControls2 Widgets)
if (NOT Qt6_FOUND)
    set(QTPREFIX "Qt5")
    find_package(Qt5 COMPONENTS Core Qml Gui Quick QuickControls2 Widgets)
endif()

# Macro for merging common code between static and shared
macro(add_target name type)
    add_library(${name} ${type}
        include/DOtherSide/DOtherSideTypes.h
        include/DOtherSide/DOtherSideTypesCpp.h
        include/DOtherSide/DOtherSide.h
        include/DOtherSide/DosQDeclarative.h
        include/DOtherSide/DosQObjectWrapper.h
        include/DOtherSide/DosQAbstractItemModelWrapper.h
        include/DOtherSide/DosQObject.h
        include/DOtherSide/DosQObjectImpl.h
        include/DOtherSide/DosIQObjectImpl.h
        include/DOtherSide/DosQMetaObject.h
        include/DOtherSide/DosIQAbstractItemModelImpl.h
        include/DOtherSide/DosQAbstractItemModel.h
        include/DOtherSide/Utils.h
        include/DOtherSide/DosQtCompatUtils.h
        include/DOtherSide/DosLambdaInvoker.h
        src/DOtherSide.cpp
        src/DosQMetaObject.cpp
        src/DosQDeclarative.cpp
        src/DosQObject.cpp
        src/DOtherSideTypesCpp.cpp
        src/DosQObjectImpl.cpp
        src/DosQAbstractItemModel.cpp
        src/DosQQuickImageProvider.cpp
        src/DosLambdaInvoker.cpp
    )

    if (WIN32)
        target_compile_definitions(${name} PRIVATE -DWIN32)
    endif()

    if(NOT MSVC)
      target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

    set_target_properties(${name} PROPERTIES CXX_STANDARD 11 AUTOMOC ON)

    target_include_directories(${name} PUBLIC include)

    target_link_libraries(${name} PRIVATE ${QTPREFIX}::Core ${QTPREFIX}::CorePrivate ${QTPREFIX}::Gui ${QTPREFIX}::Widgets ${QTPREFIX}::Qml ${QTPREFIX}::Quick)

    if (${Qt5QuickControls2_FOUND})
        target_link_libraries(${name} PRIVATE ${QTPREFIX}::QuickControls2)
    endif()
endmacro()

# Add shared version
add_target(${PROJECT_NAME} SHARED)

set(soversion "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}")

set_target_properties(${PROJECT_NAME}
PROPERTIES
    SOVERSION "${soversion}"
    VERSION "${CMAKE_PROJECT_VERSION}"
)

# Add static version
add_target(${PROJECT_NAME}Static STATIC)

# Install directive for header files
install(FILES
  include/DOtherSide/DOtherSide.h
  include/DOtherSide/DOtherSideTypes.h
  DESTINATION include/DOtherSide
)

# Install directive for binaries
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install Pkg-Config definition
configure_file(DOtherSide.pc.in DOtherSide.pc @ONLY)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/DOtherSide.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
