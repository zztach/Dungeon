This is an experimental project in an effort to apply basic design principles and OpenGL.
The core idea revolves around a first person labyrinth/dungeon game similar to "Legends of Grimrock".<br>
The whole project started after playing Grimrock, which reminded me how huge of a dungeon-crawling R.P.Gs fan I am.<br>
Sample documentation (work in progress) is available at http://zztach.github.io/Dungeon/index.html

<b>How to run on Ubuntu</b>
<ul>
<li>Install SDL2</li>
<i>sudo apt-get install libsdl2-dev</i>
<li>Install CMake</li>
<i>sudo apt-get install cmake</i>
<li>Install GLEW under /opt</li>
<i>sudo wget https://sourceforge.net/projects/glew/files/glew/1.11.0/glew-1.11.0.tgz; tar -xvzf glew-1.11.0.tgz -C /opt;rm -f glew-1.11.0.tgz</i><br>
<i>cd /opt/glew-1.11.0; sudo make install</i> to get the libGLEW lib deployed
<li>Install glm under /opt</li>
<i>sudo wget https://github.com/g-truc/glm/releases/download/0.9.4.6/glm-0.9.4.6.zip; unzip glm-0.9.4.6.zip -d /opt;rm -f glm-0.9.4.6.zip</i>
<li>Compile Code</li>
<i>Go to root project directory and execute cmake .</i>
<li>Run Executable</li>
<i>cmake-build-debug/Dungeon</i>
</ul>

<b>Core Features</b>
<ul>
<li>Camera</li>
   Player can move/strafe using the WASD keys and rotate his view with the mouse
<li>Image loading</li>
   Ability to load .BPM/.TGA image files
<li>Textures</li>
   Load texture objects at startup using .xml configuration file<br>
</ul>

<b>3D effects</b>
<ul>
<li>Particle engine</li>
   Basic particle engine (used to simulate a fire effect)
</ul>

<b>2D effects</b>
<ul>
<li>2D text</li>
   Display text on screen (e.g FPS Counter)
<li>2D Controls</li>
   Primitive display of 2D controls like listbox
</ul>

<b>Libraries Used</b>
<ul>
<li>OpenGL 4.2 core profile</li>
<li>SDL2 : window/keyboard/mouse management</li>
<li>glm-0.9.4.6 : math operations</li>
<li>glew-1.11.0 : OpenGL extentions</li>
<li>pugixml : handle xml files</li>
</ul>
