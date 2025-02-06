set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external)

find_package(fbx CONFIG REQUIRED)

add_executable(sample main.cpp)

target_link_libraries(sample PRIVATE fbx::fbx)

message("[package] fbx_RUNTIME : ${fbx_RUNTIME}")

add_custom_command(
    TARGET
    sample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${fbx_RUNTIME} $<TARGET_FILE_DIR:sample>
)