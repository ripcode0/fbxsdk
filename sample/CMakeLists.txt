# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external)

# find_package(fbx QUIET NO_MODULE)

# if(fbx_FOUND)
#     message(STATUS "[fbx] founded fbx package build sample ...")
#     add_executable(sample main.cpp)
#     target_link_libraries(sample PRIVATE fbx::fbx)    
# else()
#     message(STATUS "[fbx] founded fbx library build sample ...")
#     add_executable(sample main.cpp)
#     target_link_libraries(sample PRIVATE fbx)
#     set(fbx_RUNTIME fbx_DLL)
# endif()

add_executable(sample main.cpp)
target_link_libraries(sample PRIVATE fbx::fbx)
set(fbx_RUNTIME ${fbx_DLL})

add_custom_command(
    TARGET
    sample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${fbx_RUNTIME} $<TARGET_FILE_DIR:sample>
)
