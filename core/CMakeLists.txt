add_library(core STATIC
    App.hpp App.cpp
    Renderer.hpp Renderer.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core PUBLIC
    SDL3::SDL3
    unofficial::skia::skia
)