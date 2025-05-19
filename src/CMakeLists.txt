file(GLOB MB_SRC "*.cxx")

add_executable(winlofi WIN32 ${MB_SRC})

target_compile_options(winlofi PRIVATE /options:strict /W4 /WX
                                        /std:c++latest)
set(CXX_STANDARD 23)
target_compile_features(winlofi PUBLIC cxx_std_23)

set_target_properties(winlofi 
                      PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/debug/bin"
)

add_custom_command(TARGET winlofi POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_BINARY_DIR}/.."
)