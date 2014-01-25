#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        // if succeeded create our window
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      
        g_pWindow = SDL_CreateWindow("Chapter 1: Setting up SDL",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                width, height,
                SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
		// Create an OpenGL context associated with the window.
        glContext = SDL_GL_CreateContext(g_pWindow);
        if (glContext != NULL)
            std::cout << "GL Context setup properly" << std::endl;        
        
    } else {
        return 1; // sdl could not initialize
    }
    glewExperimental = GL_TRUE;    
    GLenum err = glewInit();
    std::cout << glGetError() << std::endl;
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));  
    }
       
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    GLuint program = LoadShader("vertex_shader.vs", "fragment_shader.fg");
    
    mv_location = glGetUniformLocation(program, "mv_matrix");
    proj_location = glGetUniformLocation(program, "proj_matrix");
    light_pos = glGetUniformLocation(program, "light_pos");

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    glGenVertexArrays(1, &vao);    
    glBindVertexArray(vao);  
     
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);		

    level = new Level();
    x = z = rotY = 0.0f;
    mv_matrix_initial = glm::mat4(1.0f);

    glViewport(0, 0, width, height);
    aspect = (float)width / (float)height;

    proj_matrix = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::render()
{
    static const GLfloat gray[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    static const GLfloat one = 1.0f;
    
    glClearBufferfv(GL_COLOR, 0, gray);
    glClearBufferfv(GL_DEPTH, 0, &one);

	// store the "initial camera" matrix
	stack<glm::mat4> modelviewStack;
		
	mv_rot_camera = glm::rotate(glm::mat4(1.0f), rotY, glm::vec3(0.0f, 1.0f, 0.0f));		
	GLuint rot_location = glGetUniformLocation(program, "rot_matrix");	
	glUniformMatrix4fv(rot_location, 1, GL_FALSE, glm::value_ptr(mv_rot_camera));               

	modelviewStack.push(mv_matrix_initial);
				
	mv_matrix_camera = glm::translate(mv_matrix_initial, glm::vec3(x, -0.0f, 30.0f + z));		
	modelviewStack.push(mv_matrix_camera);		
	GLuint camera_location = glGetUniformLocation(program, "camera_matrix");	
	glUniformMatrix4fv(camera_location, 1, GL_FALSE, glm::value_ptr(mv_matrix_camera));               		
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj_matrix));

	// w=0.0 equals directional light (sunlight), while w=1.0 equals positional light
	glm::vec4 light = glm::vec4(25.0, 20.0, 15.0, 1.0f);
	glUniform4fv(light_pos, 1, glm::value_ptr(light));
	
	glUseProgram(program);
	level->render(program);

	// object in static distance from viewer		
	/*modelviewStack.pop();
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(modelviewStack.top()));        		
	glUseProgram(program);
	level->render(program);*/

    SDL_GL_SwapWindow(g_pWindow);  
}

void Game::clean()
{	
    std::cout << "cleaning game\n";
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    delete level;

    if( glContext ) SDL_GL_DeleteContext(glContext);
    if( g_pWindow ) SDL_DestroyWindow(g_pWindow);
    
    // clean up SDL
    SDL_Quit();    
}

void Game::handleEvents() {
    SDL_Event event;
    float yrotrad = (rotY / 180 * 3.141592654f);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_w) {
                    z += 1.0f * float(cos(yrotrad));
                    x -= 1.0f * float(sin(yrotrad));
                    break;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    z -= 1.0f * float(cos(yrotrad));
                    x += 1.0f * float(sin(yrotrad));
                    break;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    rotY -= 1.0f;
                    if (rotY > 360)
                        rotY -= 360;
                    break;
                }
                if (event.key.keysym.sym == SDLK_e) {
                    rotY += 1.0f;
                    if (rotY < -360)
                        rotY += 360;
                    break;
                }
                break;
            default:
                break;
        }
    }
}

std::string Game::readFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint Game::LoadShader(const char *vertex_path, const char *fragment_path)
{
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders
    std::string vertShaderStr = readFile(vertex_path);
    std::string fragShaderStr = readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();
    
    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader
    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);
    std::cout << "yeah" << glGetError() << std::endl;

    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::cout << "yeah" << glGetError() << std::endl;
    if (logLength > 0) 
    {
        std::vector<char> vertShaderError(logLength);
        glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);    
        std::cout << &vertShaderError[0] << std::endl;
    }
    

    // Compile fragment shader
    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);
       

    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        std::vector<char> fragShaderError(logLength);
        glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
        std::cout << &fragShaderError[0] << std::endl;
    }
    std::cout << "Linking program" << std::endl;
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    std::cout << "Program OK" << std::endl;
    return program;
}