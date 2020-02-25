#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include <GL/gl3w.h>
#include<GLFW/glfw3.h>
#include<cstdio>
#include"Transform.h"
#include"Camera.h"
#include "vertex.h"
#include "objloader.h"
#include"vertexbuffer.h"
#include "ElementBuffer.h"
#include"vertexarray.h"
#include "Shader.h"
#include "Renderer.h"
#include "texture.h"
#include "mesh.h"


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Application {

public:
    Application();
    ~Application();
    void run();
    Camera cam;
    Transform cubeTransform;

private:

    void init();
    void setEventHandling();

    void display();

    GLFWwindow *window;
    const int Width = 1920;
    const int Height = 1080;

    ObjModel model;
    VertexBuffer _vb_cube;
    IndexBuffer _eb_cube;
    VertexArray _va_cube;

    VertexBuffer _vb_skybox;
    IndexBuffer _eb_skybox;
    VertexArray _va_skybox;

	VertexBuffer _vb_reflection_cube;
	IndexBuffer _eb_reflection_cube;
	VertexArray _va_reflection_cube;

	Mesh reflection_cube_mesh;

    Shader _cubeshader;
    Shader _skyboxShader;
	Shader _reflectionCubeShader;
    Renderer _renderer;
    Texture _cubeTex;
    Texture _skyboxTex;

    Transform _skyboxTransform;
	Transform _reflectionCubeTransform;
};
#endif // !__APPLICATION_H__

