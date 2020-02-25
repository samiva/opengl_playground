#ifndef __SHADER_H__
#define __SHADER_H__
#include <GL/gl3w.h>
#include <string>
#include <vector>

struct ShaderInfo {
    const std::string file;
    GLenum type;
};

class Shader {
public:
    Shader();
    ~Shader();
    void createShader(std::vector<ShaderInfo> infos);
    void bind() const;
    void unbind() const;
    void setUniformMatrix4f(const std::string& uname, const GLfloat* val);
    void setUniform1i(const std::string& uname, int val);

private:
    static unsigned int idcount;
    unsigned int _id;
    unsigned int compileShader(const ShaderInfo& info);
    void linkShaders(std::vector<unsigned int> shaders);
    void shaderError(unsigned int shader);
    void programError();
    int getUniform(const std::string& uname);

};
#endif // !__SHADER_H__
