cmake_minimum_required(VERSION 3.22)

if(MSVC)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(fbx VERSION 1.0.0 LANGUAGES C CXX)

option(BUILD_SAMPLE "fbx build the sample" FALSE)

set(fbx_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/libfbxsdk.lib)
set(fbx_DLL ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/libfbxsdk.dll)
set(fbx_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(fbx INTERFACE)
add_library(fbx::fbx ALIAS fbx)

include(GNUInstallDirs)

target_include_directories(
    fbx
    INTERFACE
    $<BUILD_INTERFACE:${fbx_INC}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

target_link_libraries(
    fbx
    INTERFACE
    $<BUILD_INTERFACE:${fbx_LIB}>
    $<INSTALL_INTERFACE:${_IMPORT_PREFIX}/libfbxsdk.lib>
)

target_link_directories(
    fbx
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>
)

install(
    TARGETS fbx
    EXPORT fbx-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    FILES_MATCHING PATTERN *.h
)

install(
    EXPORT fbx-targets
    FILE fbx-targets.cmake
    NAMESPACE fbx::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fbx
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fbx-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/fbx-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fbx
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/fbx-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fbx
    )

install(FILES ${fbx_LIB} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${fbx_DLL} DESTINATION ${CMAKE_INSTALL_BINDIR})


if(BUILD_SAMPLE)
    add_subdirectory(sample)
endif()
