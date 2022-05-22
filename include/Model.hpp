#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"

#include "Shader.hpp"
#include "Mesh.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
    std::vector<Textures> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    Model( std::string const &path, bool gamma = false) : gammaCorrection(gamma)  { loadModel(path); }
    void Draw(Shader &shader);
private:
    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Textures> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif