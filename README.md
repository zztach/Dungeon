This is an experimental project in an effort to apply basic design principles and OpenGL.
The core idea revolves around a first person labyrinth/dungeon game similar to "Legends of Grimrock".
The whole project started after playing Grimrock, which reminded me how huge of a dungeon-crawling R.P.Gs fan I am.

Core Features
-> Camera
   Player can move/strafe using the WASD keys and rotate his view with the mouse
-> Image loading
   Ability to load .BPM/.TGA image files
-> Textures
   Load texture objects at startup using .xml configuration file.

3D effects\n
-> Particle engine\n
   Basic particle engine (used to simulate a fire effect)\n\n

2D effects
-> 2D text
   Display text on screen
-> 2D Controls
   Primitive display of 2D controls like listbox

SETUP LINUX/NETBEANS
TODO

SETUP WINDOWS/VS2012
TODO

LIBRARIES USED
-> OpenGL 4.2 core profile
-> SDL2 : window/keyboard/mouse management
-> glm  : math operations
-> glew : OpenGL extentions
-> pugixml : handle xml files