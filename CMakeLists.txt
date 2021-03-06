cmake_minimum_required(VERSION 3.5)
project(Dungeon)

set(CMAKE_CXX_STANDARD 11)

include_directories(/opt/glew-1.11.0/include/GL /usr/include/GL /opt/glm/glm /usr/include/SDL2)

set(SOURCE_FILES src/controls/Control.cpp
        src/controls/Control.h
        src/controls/ListBox.cpp
        src/controls/ListBox.h
        src/engine/Camera.cpp
        src/engine/Camera.h
        src/engine/Game.cpp
        src/engine/Game.h
        src/engine/Level.cpp
        src/engine/Level.h
        src/engine/Timer.cpp
        src/engine/Timer.h
        src/image/BmpImageLoader.cpp
        src/image/BmpImageLoader.h
        src/image/ImageLoader.h
        src/image/ImageLoaderFactory.cpp
        src/image/ImageLoaderFactory.h
        src/image/TgaImageLoader.cpp
        src/image/TgaImageLoader.h
        src/rendering/particles/Emitter.cpp
        src/rendering/particles/Emitter.h
        src/rendering/particles/Particle.cpp
        src/rendering/particles/Particle.h
        src/rendering/textures/Texture.cpp
        src/rendering/textures/Texture.h
        src/rendering/textures/TextureFactory.cpp
        src/rendering/textures/TextureFactory.h
        src/rendering/textures/TextureImage.h
        src/rendering/IDrawable.h
        src/rendering/TextRenderer.cpp
        src/rendering/TextRenderer.h
        src/inputhander/InputHandler.h
        src/inputhander/InputHandler.cpp
        src/inputhander/InputProcessor.h
        src/inputhander/InputState.h
        src/inputhander/InputState.cpp
        src/utils/FileUtil.cpp
        src/utils/FileUtil.h
        src/utils/pugiconfig.hpp
        src/utils/pugixml.cpp
        src/utils/pugixml.hpp
        src/utils/ShaderLoader.cpp
        src/utils/ShaderLoader.h
        src/utils/ShaderUniform.h
        src/model/Mesh.cpp
        src/model/Mesh.h
        src/Main.cpp)

find_package(SDL2 REQUIRED)
set(OPENGL64_LIB /usr/lib/x86_64-linux-gnu/libGL.so)
set(SDL2_LIB /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(GLEW_LIB /usr/lib64/libGLEW.so)
link_directories(${OPENGL64_LIB} ${SDL2_LIB} ${GLEW_LIB})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/cmake-build-debug)
add_executable(Dungeon ${SOURCE_FILES})
target_link_libraries(Dungeon ${OPENGL64_LIB} ${SDL2_LIB} ${GLEW_LIB})

configure_file(src/resources/textures/font.tga ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/font.tga COPYONLY)
configure_file(src/resources/textures/mossy_wall.tga ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/mossy_wall.tga COPYONLY)
configure_file(src/resources/textures/particle.tga ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/particle.tga COPYONLY)
configure_file(src/resources/textures/smoke.tga ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/smoke.tga COPYONLY)
configure_file(src/resources/textures/stone_wall.bmp ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/stone_wall.bmp COPYONLY)
configure_file(src/resources/textures/sunflower.tga ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/sunflower.tga COPYONLY)
configure_file(src/resources/textures/crate.tga ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/crate.tga COPYONLY)
configure_file(src/resources/textures/textures.xml ${CMAKE_BINARY_DIR}/cmake-build-debug/textures/textures.xml COPYONLY)
configure_file(src/resources/models/crate.obj ${CMAKE_BINARY_DIR}/cmake-build-debug/models/crate.obj COPYONLY)
configure_file(src/resources/models/crate.mtl ${CMAKE_BINARY_DIR}/cmake-build-debug/models/crate.mtl COPYONLY)
configure_file(src/resources/shaders/vertex_shader.vert ${CMAKE_BINARY_DIR}/cmake-build-debug/shaders/vertex_shader.vert COPYONLY)
configure_file(src/resources/shaders/fragment_shader.frag ${CMAKE_BINARY_DIR}/cmake-build-debug/shaders/fragment_shader.frag COPYONLY)
configure_file(src/resources/map.txt ${CMAKE_BINARY_DIR}/cmake-build-debug/map.txt COPYONLY)