#include "Texture.hpp"

#include <iostream>

#include "glad/glad.h"
#include "stb_image.h"

const std::string TEXTURE_FILE_PATH = "../res/textures/";

Texture::Texture(const std::string &filename) : m_filepath( TEXTURE_FILE_PATH + filename )
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    stbi_set_flip_vertically_on_load(true);
    m_Data = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

    if ( !m_Data)
    {
        std::cout << "Texture not found on given path. " << m_filepath << std::endl;
        exit(0);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    if ( m_Data )
        stbi_image_free(m_Data);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}