file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(renderer ${SOURCES})

target_compile_options(renderer PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
