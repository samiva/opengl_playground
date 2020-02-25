#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader() {
    _id = idcount;
    ++idcount;
}

Shader::~Shader() {
    glDeleteProgram(_id);
}

void Shader::createShader(std::vector<ShaderInfo> infos) {
    std::vector<unsigned int> shaders;
    for (const auto& info : infos) {

        auto shader = compileShader(info);
        shaders.push_back(shader);        
    }
    linkShaders(shaders);
}

void Shader::bind() const {
    glUseProgram(_id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string & uname, int val) {
    int uniform = getUniform(uname);
    glUniform1i(uniform, val);
}

void Shader::setUniformMatrix4f(const std::string & uname, const GLfloat * val) {
    int uniform = getUniform(uname);
    glUniformMatrix4fv(uniform, 1, GL_FALSE, val);
}


unsigned int Shader::compileShader(const ShaderInfo & info) {
    // Read shader source from a file as a string
    std::ifstream ifs(info.file, std::ios::binary);

    //std::string src;
    ifs.seekg(0, ifs.end);
    auto sz = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    // Maybe unique ptr?
    char *src = new char[sz];
    ifs.read(src, sz);
    ifs.close();
    unsigned int shader = glCreateShader(info.type);
    glShaderSource(shader, 1, &src, (int*)&sz);
    glCompileShader(shader);

    int compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE) {
        shaderError(shader);
        return 0;
    }
    delete src;
    return shader;
}

void Shader::linkShaders(std::vector<unsigned int> shaders) {
    _id = glCreateProgram();

    for (auto shader : shaders) {
        glAttachShader(_id, shader);
    }

    glLinkProgram(_id);

    int status{ 0 };
    glGetProgramiv(_id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        programError();
    }

    glValidateProgram(_id);
    status = 0;
    glGetProgramiv(_id, GL_VALIDATE_STATUS, &status);

    if (status != GL_TRUE) {
        programError();
    }
}

void Shader::shaderError(unsigned int shader) {
    int len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    char *log = new char[len];
    glGetShaderInfoLog(shader, len, nullptr, log);
    std::cerr << log << std::endl;
    delete log;
}

void Shader::programError() {
    int len;
    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &len);
    char* log = new char[len];
    glGetProgramInfoLog(_id, len, nullptr, log);
    std::cerr << log << std::endl;
    delete log;
}

int Shader::getUniform(const std::string& uname) {
    int uniformLoc = glGetUniformLocation(_id, uname.c_str());
    if (uniformLoc == -1) {
        std::cerr << "Shader warning: couldn't find uniform " << uname << std::endl;
    }
    return uniformLoc;
}

unsigned int Shader::idcount = 1;
