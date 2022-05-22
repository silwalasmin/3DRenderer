#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader
{
public:
    Shader(const std::string &filename);
    ~Shader() { glDeleteProgram(m_ShaderID); }

    void use() const;
    
    //uniform setting functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

    inline unsigned int GetID() { return m_ShaderID; }

private:
    unsigned int m_ShaderID;
    std::string m_filepath;
    mutable std::unordered_map<std::string,GLint> m_UniformLocationCache;
    //privateFunctions
    ShaderProgramSource ParseShader();
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    GLint GetUniformLocation(const std::string& name) const;
};

#endif 