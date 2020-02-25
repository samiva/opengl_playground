#include "Application.h"
#include<string>
#include <fstream>
#include <iostream>
#include<utility>
#include<glm/gtc/type_ptr.hpp>
#include <functional>
#include "mesh.h"

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}



Application::Application() {
}


Application::~Application() {
}

void Application::run() {
    init();
    while (glfwWindowShouldClose(window) == false) {
        display();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << std::endl;

    }

    window = glfwCreateWindow(Width, Height, "OPENGL playground", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowPos(window, 0, 1000);
    glfwMakeContextCurrent(window);
    if (gl3wInit() != GL3W_OK) {
        std::cerr << "failed to initialize gl3w" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    cam = Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0, 0, 0));
    _vb_cube.genBuffers(1);
    _eb_cube.genBuffers(1);
    _va_cube.genVertexArrays(1);

    _vb_skybox.genBuffers();
    _eb_skybox.genBuffers();
    _va_skybox.genVertexArrays();

	_vb_reflection_cube.genBuffers();
	_eb_reflection_cube.genBuffers();
	_va_reflection_cube.genVertexArrays();

    // setup for cube
    model = ObjModel("untitled.obj");

    float cube_v_pos_texcoords[] = {
     0.5f,  0.5f, 0.5f,     1.0f, 1.0f,
     0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
    -0.5f,  0.5f, 0.5f,     0.0f, 1.0f,

     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f
    };

    unsigned int cube_indices[] = {
        0,1,2,  // Front
        0,3,2,

        4,5,1,  // left
        4,0,1,

        4,5,6,  // Back
        4,7,6,

        3,2,6,  // Right
        3,7,6,

        4,0,3,  // Top
        4,7,3,

        5,1,2,   // bottom
        5,6,2
    };

    float reflection_cube_v_pos[] = {
         0.5f,  0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,

         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };

    unsigned int reflection_cube_indices[] = {
        0,1,2,  // Front
        0,3,2,

        4,5,1,  // left
        4,0,1,

        4,7,6,
        4,5,6,  // Back

        3,2,6,  // Right
        3,7,6,

        4,7,3,
        4,0,3,  // Top

        5,1,2,   // bottom
        5,6,2
    };

    float skybox_v_pos_col[] = {
         10.0f,  10.0f, 10.0f,   1.0f, 0.0f, 0.0f,   
         10.0f, -10.0f, 10.0f,   0.0f, 1.0f, 0.0f,   
        -10.0f, -10.0f, 10.0f,   0.0f, 0.0f, 1.0f,   
        -10.0f,  10.0f, 10.0f,   0.0f, 0.0f, 1.0f,   
                 
         10.0f,  10.0f, -10.0f,  1.0f, 0.0f, 0.0f,   
         10.0f, -10.0f, -10.0f,  0.0f, 1.0f, 0.0f,   
        -10.0f, -10.0f, -10.0f,  0.0f, 0.0f, 1.0f,   
        -10.0f,  10.0f, -10.0f,  0.0f, 0.0f, 1.0f
    };

    unsigned int skybox_indices[] = {
        4,5,1,  // left
        4,0,1,

        3,2,6,  // Right
        3,7,6,
                
        5,1,2,   // bottom
        5,6,2,

        4,0,3,  // Top
        4,7,3,

        0,1,2,  // Front
        0,3,2,

        4,5,6,  // Back
        4,7,6
    };

    _va_cube.bind();
    _vb_cube.bind();
    _eb_cube.bind();

    _vb_cube.setData(static_cast<void*>(cube_v_pos_texcoords), sizeof(cube_v_pos_texcoords));
    _eb_cube.setData(static_cast<void*>(cube_indices), sizeof(cube_indices), sizeof(cube_indices) / sizeof(cube_indices[0]));
    

    BufferLayout layout_cube;
    layout_cube.push<float>(3);
    layout_cube.push<float>(2);
    _va_cube.addBufferLayout(_vb_cube, layout_cube);

    std::vector<ShaderInfo> cube_shaderInfos = {
        {"vertex_shader.glsl",GL_VERTEX_SHADER },
        {"frag_shader.glsl", GL_FRAGMENT_SHADER }
    };

    // Shader for the cube
    _cubeshader.createShader(cube_shaderInfos);

    
    _vb_cube.unbind();
    _eb_cube.unbind();
    _va_cube.unbind();

    // Set skybox
    _va_skybox.bind();
    _vb_skybox.bind();
    _eb_skybox.bind();

    _vb_skybox.setData(static_cast<void*>(skybox_v_pos_col), sizeof(skybox_v_pos_col));
    _eb_skybox.setData(static_cast<void*>(skybox_indices), sizeof(skybox_indices), sizeof(skybox_indices) / sizeof(skybox_indices[0]));

    BufferLayout layout_skybox;
    layout_skybox.push<float>(3);
    layout_skybox.push<float>(3);
    _va_skybox.addBufferLayout(_vb_skybox, layout_skybox);

    // Shader for the skybox
    std::vector<ShaderInfo>skyboxShader_info = {
        {"skybox_vshader.glsl", GL_VERTEX_SHADER},
        {"skybox_fshader.glsl", GL_FRAGMENT_SHADER}
    };
    _skyboxShader.createShader(skyboxShader_info);
    
    _vb_skybox.unbind();
    _eb_skybox.unbind();
    _va_skybox.unbind();


	reflection_cube_mesh = createMesh(reflection_cube_v_pos, reflection_cube_indices, true);

	_vb_reflection_cube.bind();
	_eb_reflection_cube.bind();
	_va_reflection_cube.bind();

	// Doesn't work
	// Problem might be with the mesh class. Maybe test mesh another cube without normals.
	_vb_reflection_cube.setData(static_cast<void*>(reflection_cube_mesh._vdata.data()), reflection_cube_mesh._vdata.size()*sizeof(float));
	_eb_reflection_cube.setData(static_cast<void*>(reflection_cube_mesh._indices),
		sizeof(unsigned int)*reflection_cube_mesh._indiceCount, 
		reflection_cube_mesh._indiceCount);


	BufferLayout layout_reflection_cube;
	layout_reflection_cube.push<float>(3);
	layout_reflection_cube.push<float>(3);
	_va_reflection_cube.addBufferLayout(_vb_reflection_cube, layout_reflection_cube);

	// 	Shader for the reflection cube
	std::vector<ShaderInfo> reflectionCubeShaderInfo = { 
		{"reflection_cube_vshader.glsl", GL_VERTEX_SHADER},
		{"reflection_cube_fshader.glsl", GL_FRAGMENT_SHADER} };

	_reflectionCubeShader.createShader(reflectionCubeShaderInfo);

	_vb_reflection_cube.unbind();
	_eb_reflection_cube.unbind();
	_va_reflection_cube.unbind();

    _skyboxTransform.setPos({ -5.0f, 0.0f, 0.0f });

	_reflectionCubeTransform.setPos({ 5.0f, 0.0f,-5.0f});

    _cubeTex.createTexture2D("res/spurdo.jpg");

    std::vector<std::string> imagepaths = { 
                                            "res/PereaBeach1/posx.jpg", "res/PereaBeach1/negx.jpg", 
                                            "res/PereaBeach1/posy.jpg", "res/PereaBeach1/negy.jpg",
                                            "res/PereaBeach1/posz.jpg", "res/PereaBeach1/negz.jpg"  
                                          };
    _skyboxTex.createCubemap(imagepaths);

    setEventHandling();
    glEnable(GL_DEPTH_TEST);
    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    
    //cam.rotateYaw(180);
    //cam.rotatePitch(180);
}

void Application::setEventHandling() {
    
    glfwSetKeyCallback(window, keyCallback);

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cout << "Key pressed" << std::endl;
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    else if (key == GLFW_KEY_W) {
        //t.rotX(0.01f);
        app->cam.rotatePitch(2.0f);
    }
    else if (key == GLFW_KEY_S) {
        //t.rotX(-0.01f);
        app->cam.rotatePitch(-2.0f);
    }
    else if (key == GLFW_KEY_Q) {
        app->cubeTransform.rotY(0.01f);
    }
    else if (key == GLFW_KEY_E) {
        app->cubeTransform.rotY(-0.01f);
    }
    else if (key == GLFW_KEY_D) {
        //t.setScale(glm::vec3(0.5f));
        //t.rotZ(0.1f);
        app->cam.rotateYaw(2.0f);
    }
    else if (key == GLFW_KEY_A) {
        //t.setScale(glm::vec3(1.0f));
        //t.rotZ(-0.1f);
        app->cam.rotateYaw(-2.0f);
    }
    else if (key == GLFW_KEY_UP) {
        app->cam.moveForward(0.5f);
    }
    else if (key == GLFW_KEY_DOWN) {
        app->cam.moveBackward(0.5f);
    }
    else if (key == GLFW_KEY_RIGHT) {
        //cam.move(glm::vec3(0.1f, 0.0f, 0.0f));
        app->cam.moveRight(0.5f);
    }
    else if (key == GLFW_KEY_LEFT) {
        //cam.move(glm::vec3(-0.1f, 0.0f, 0.0f));
        app->cam.moveLeft(0.5f);
    }
}

void Application::display() {
    _renderer.clear();

    auto M = cubeTransform.getModelMatrix();
    auto view = cam.getViewMatrix();
    auto proj = cam.getProjMatrix(Width, Height);
    auto MVP = proj * view * M;
    _cubeshader.bind();
    _cubeshader.setUniformMatrix4f("transform", glm::value_ptr(MVP));
    _cubeshader.setUniform1i("tex", 0);
    _cubeshader.unbind();
    _cubeTex.bind();
    _renderer.draw(_va_cube, _eb_cube, _cubeshader);

    M = _skyboxTransform.getModelMatrix();

    // Remove translation from the camera's view matrix
    view = glm::mat4(glm::mat3(view));

    MVP = proj * view*M;
    _skyboxShader.bind();
    _skyboxShader.setUniformMatrix4f("mvp", glm::value_ptr(MVP));
    _skyboxShader.unbind();
    _skyboxTex.bind();
    _renderer.draw(_va_skybox, _eb_skybox, _skyboxShader);

	auto refl_cube_M = _reflectionCubeTransform.getModelMatrix();
	view = cam.getViewMatrix();
	auto refl_cube_MVP = proj * view*refl_cube_M;
	_reflectionCubeShader.bind();
	_reflectionCubeShader.setUniformMatrix4f("mat_mvp", glm::value_ptr(refl_cube_MVP));
	auto refl_cube_MV = view * refl_cube_M;
	_reflectionCubeShader.setUniformMatrix4f("mat_mv", glm::value_ptr(refl_cube_MV));
	_reflectionCubeShader.setUniform1i("tex", 0);
	_reflectionCubeShader.unbind();
	_renderer.draw(_va_reflection_cube, _eb_reflection_cube, _reflectionCubeShader);

}
