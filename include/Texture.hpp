#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include "glad/glad.h"

class Texture
{
public:
    Texture(const std::string &filename);
    ~Texture() { glDeleteTextures(1, &m_textureID); }

    void Bind(unsigned int slot) const;
    void Unbind() const;

    inline int getWidth() { return m_width; }
    inline int getHeight() { return m_height; }
private:
    unsigned int m_textureID;
    std::string m_filepath;
    int m_width, m_height, m_BPP;
    unsigned char *m_Data;
};

#endif 