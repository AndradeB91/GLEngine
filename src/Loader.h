#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "GL/glew.h"

#include "Geometry.h"
#include "Mesh.h"
#include "Texture.h"

class Loader
{
public:
    Loader();

    void loadObj(const std::string &fileName);

    Geometry loadObjGeometry(const std::string &fileName);
    Mesh *geometryToMesh(Geometry geometry);

    void clear();

    std::vector<Mesh *> getMeshList();
    std::vector<Texture *> getTextureList();
    std::vector<unsigned int> getMeshToTex();

    ~Loader();

private:
    void loadNode(aiNode *node, const aiScene *scene);
    void loadMesh(aiMesh *mesh, const aiScene *scene);
    void loadMaterials(const aiScene *scene);

    Geometry loadGeometry(aiMesh *mesh);

    std::vector<Mesh *> _meshList;
    std::vector<Texture *> _textureList;
    std::vector<unsigned int> _meshToTex;
};
