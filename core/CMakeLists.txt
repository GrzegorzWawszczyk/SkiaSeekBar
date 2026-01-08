add_library(core STATIC
    App.hpp App.cpp
    Button.hpp Button.cpp
    Drawable.hpp Drawable.cpp
    Interactive.hpp
    Label.hpp Label.cpp
    Rect.hpp Rect.cpp
    Renderer.hpp Renderer.cpp
    SDLInputHandler.hpp SDLInputHandler.cpp
    SeekBarScene.hpp SeekBarScene.cpp
    UIItem.hpp UIItem.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core PUBLIC
    SDL3::SDL3
    unofficial::skia::skia
)
