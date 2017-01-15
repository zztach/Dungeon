cmake_minimum_required(VERSION 3.6)
project(Dungeon)

set(CMAKE_CXX_STANDARD 11)

include_directories(/opt/glew-1.11.0/include/GL /usr/include/GL /opt/glm/glm /usr/include/SDL2)

set(SOURCE_FILES map/controls/Control.cpp
        map/controls/Control.h
        map/controls/ListBox.cpp
        map/controls/ListBox.h
        map/engine/Camera.cpp
        map/engine/Camera.h
        map/engine/Game.cpp
        map/engine/Game.h
        map/engine/Level.cpp
        map/engine/Level.h
        map/engine/Timer.cpp
        map/engine/Timer.h
        map/image/BmpImageLoader.cpp
        map/image/BmpImageLoader.h
        map/image/ImageLoader.h
        map/image/ImageLoaderFactory.cpp
        map/image/ImageLoaderFactory.h
        map/image/TgaImageLoader.cpp
        map/image/TgaImageLoader.h
        map/rendering/particles/Emitter.cpp
        map/rendering/particles/Emitter.h
        map/rendering/particles/Particle.cpp
        map/rendering/particles/Particle.h
        map/rendering/textures/Texture.cpp
        map/rendering/textures/Texture.h
        map/rendering/textures/TextureFactory.cpp
        map/rendering/textures/TextureFactory.h
        map/rendering/textures/TextureImage.h
        map/rendering/IDrawable.h
        map/rendering/TextRenderer.cpp
        map/rendering/TextRenderer.h
        map/inputhander/InputHandler.h
        map/inputhander/InputHandler.cpp
        map/inputhander/InputProcessor.h
        map/inputhander/InputState.h
        map/inputhander/InputState.cpp
        map/utils/FileUtil.cpp
        map/utils/FileUtil.h
        map/utils/pugiconfig.hpp
        map/utils/pugixml.cpp
        map/utils/pugixml.hpp
        map/utils/ShaderLoader.cpp
        map/utils/ShaderLoader.h
        map/utils/ShaderUniform.h
        map/Main.cpp)

find_package(SDL2 REQUIRED)
set(OPENGL64_LIB /opt/amdgpu-pro/lib/x86_64-linux-gnu/libGL.so)
set(SDL2_LIB /usr/lib/x86_64-linux-gnu/libSDL2.so )
set(GLEW_LIB /usr/lib64/libGLEW.so.1.11 )
link_directories(${OPENGL64_LIB} ${SDL2_LIB} ${GLEW_LIB})

add_executable(Dungeon ${SOURCE_FILES})
target_link_libraries(Dungeon ${OPENGL64_LIB} ${SDL2_LIB} ${GLEW_LIB})

configure_file(map/resources/textures/font.tga ${CMAKE_BINARY_DIR}/textures/font.tga COPYONLY)
configure_file(map/resources/textures/mossy_wall.tga ${CMAKE_BINARY_DIR}/textures/mossy_wall.tga COPYONLY)
configure_file(map/resources/textures/particle.tga ${CMAKE_BINARY_DIR}/textures/particle.tga COPYONLY)
configure_file(map/resources/textures/smoke.tga ${CMAKE_BINARY_DIR}/textures/smoke.tga COPYONLY)
configure_file(map/resources/textures/stone_wall.bmp ${CMAKE_BINARY_DIR}/textures/stone_wall.bmp COPYONLY)
configure_file(map/resources/textures/sunflower.tga ${CMAKE_BINARY_DIR}/textures/sunflower.tga COPYONLY)
configure_file(map/resources/textures/textures.xml ${CMAKE_BINARY_DIR}/textures/textures.xml COPYONLY)
configure_file(map/resources/shaders/vertex_shader.vs ${CMAKE_BINARY_DIR}/shaders/vertex_shader.vs COPYONLY)
configure_file(map/resources/shaders/fragment_shader.fg ${CMAKE_BINARY_DIR}/shaders/fragment_shader.fg COPYONLY)
configure_file(map/resources/map.txt ${CMAKE_BINARY_DIR}/map.txt COPYONLY)