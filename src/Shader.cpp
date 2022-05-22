#include "Shader.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

const std::string SHADER_FOLDER_PATH = "../res/shaders/";

Shader::Shader(const std::string &filename) : m_filepath( SHADER_FOLDER_PATH + filename)
{
    ShaderProgramSource source = ParseShader();
    m_ShaderID = CreateShader(source.VertexShader, source.FragmentShader);
}

ShaderProgramSource Shader::ParseShader()
{
    std::ifstream stream(m_filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while  ( getline(stream, line) )
    {
        if ( line.find("#shader") != std::string::npos)
        {
            if ( line.find("vertex") != std::string::npos )
                type = ShaderType::VERTEX;
            else if ( line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
            ss[(int)type] << line << '\n';
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader( unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if ( !result )
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader( const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
    if ( m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
    if ( location == -1)
        std::cout << "Warning: Uniform name " << name << " does not exist!" << std::endl;
    else
        m_UniformLocationCache[name] = location;
    return location;
}

void Shader::use() const
{
    glUseProgram(m_ShaderID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{   
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}