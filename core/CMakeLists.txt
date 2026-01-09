file(GLOB_RECURSE CORE_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE CORE_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

add_library(core STATIC
    ${CORE_SRC}
    ${CORE_HEADERS}
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/core
)

target_link_libraries(core PUBLIC
    SDL3::SDL3
    unofficial::skia::skia
)