#include "Loader.h"

Loader::Loader()
{
}

std::vector<Mesh *> Loader::getMeshList()
{
    return this->_meshList;
}

std::vector<Texture *> Loader::getTextureList()
{
    return this->_textureList;
}

std::vector<unsigned int> Loader::getMeshToTex()
{
    return this->_meshToTex;
}

void Loader::loadObj(const std::string &fileName)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName,
                                             aiProcess_Triangulate |
                                                 aiProcess_FlipUVs |
                                                 aiProcess_GenSmoothNormals |
                                                 aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        printf("Model (%s) failed to load: %s", fileName.c_str(), importer.GetErrorString());
        return;
    }

    this->loadNode(scene->mRootNode, scene);

    loadMaterials(scene);
}

void Loader::loadNode(aiNode *node, const aiScene *scene)
{
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        this->loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        this->loadNode(node->mChildren[i], scene);
    }
}

void Loader::loadMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {

        vertices.insert(vertices.end(), {mesh->mVertices[i].x,
                                         mesh->mVertices[i].y,
                                         mesh->mVertices[i].z});

        if (mesh->mTextureCoords[0])
        {
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x,
                                             mesh->mTextureCoords[0][i].y});
        }
        // else
        // {
        //     vertices.insert(vertices.end(), {0.0f, 0.0f});
        // }

        vertices.insert(vertices.end(), {-mesh->mNormals[i].x,
                                         -mesh->mNormals[i].y,
                                         -mesh->mNormals[i].z});
    }

    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh *newMesh = new Mesh();

    if (mesh->mTextureCoords[0])
    {
        newMesh->createMesh(&vertices[0],
                            &indices[0],
                            vertices.size(),
                            indices.size(),
                            3,
                            (GLint[]){0, 1, 2},
                            (GLint[]){3, 2, 3},
                            (GLenum[]){GL_FLOAT, GL_FLOAT, GL_FLOAT},
                            8,
                            (unsigned int[]){0, 3, 5});
    }
    else
    {
        newMesh->createMesh(&vertices[0],
                            &indices[0],
                            vertices.size(),
                            indices.size(),
                            2,
                            (GLint[]){0, 1},
                            (GLint[]){3, 3},
                            (GLenum[]){GL_FLOAT, GL_FLOAT},
                            6,
                            (unsigned int[]){0, 3});
    }

    this->_meshList.push_back(newMesh);
    this->_meshToTex.push_back(mesh->mMaterialIndex);
}

void Loader::loadMaterials(const aiScene *scene)
{
    this->_textureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial *material = scene->mMaterials[i];

        this->_textureList[i] = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {
                int idx = std::string(path.data).rfind("\\");
                std::string fileName = std::string(path.data).substr(idx + 1);

                std::string texPath = std::string("textures/") + fileName;

                this->_textureList[i] = new Texture(texPath.c_str());

                if (!this->_textureList[i]->loadTexture())
                {
                    printf("Failed to load texture at: %s\n", texPath.c_str());
                    delete this->_textureList[i];
                    this->_textureList[i] = nullptr;
                }
            }
        }

        if (!this->_textureList[i])
        {
            this->_textureList[i] = new Texture("textures/plain.png");
            this->_textureList[i]->loadTextureWithAlpha();
        }
    }
}

void Loader::clearModel()
{
    for (size_t i = 0; i < this->_meshList.size(); i++)
    {
        if (this->_meshList[i])
        {
            delete this->_meshList[i];
            this->_meshList[i] = nullptr;
        }
    }

    for (size_t i = 0; i < this->_textureList.size(); i++)
    {
        if (this->_textureList[i])
        {
            delete this->_textureList[i];
            this->_textureList[i] = nullptr;
        }
    }
}

Loader::~Loader()
{
}