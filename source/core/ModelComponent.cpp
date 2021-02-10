#include "ModelComponent.hpp"

#include <iostream>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <cmrc/cmrc.hpp>

#include <il.h>

CMRC_DECLARE(ShaderLib);

using core::MeshComponent;
using core::MeshTexture;
using core::MeshVertex;
using core::ModelComponent;
using core::TextureList;

ModelComponent::ModelComponent()
  : GraphicalComponent()
{
  // Add the base model shader.
  auto fs = cmrc::ShaderLib::get_filesystem();
  auto vertexFile = fs.open("shaders/ModelBase.vert");
  auto fragmentFile = fs.open("shaders/ModelBase.frag");
  AddShader(vertexFile.begin(), fragmentFile.begin());
}

void ModelComponent::LoadModel(const std::string& aFilePath)
{
  Assimp::Importer importer;
  unsigned int postProcessFlags = aiProcess_Triangulate | aiProcess_FlipUVs;
  const aiScene* scene = importer.ReadFile(aFilePath, postProcessFlags);

  if(scene == nullptr ||
     scene->mRootNode == nullptr ||
     scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
  {
    std::cout << "Error loading model! " <<
                 importer.GetErrorString() << std::endl;
  }
  else
  {
    ProcessNode(scene->mRootNode, scene);
  }
}

void ModelComponent::LoadModel(const void* aBuffer, size_t aBufLength)
{
  Assimp::Importer importer;
  unsigned int postProcessFlags = aiProcess_Triangulate | aiProcess_FlipUVs;
  const aiScene* scene = importer.ReadFileFromMemory(aBuffer, aBufLength, postProcessFlags);

  if(scene == nullptr ||
     scene->mRootNode == nullptr ||
     scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
  {
    std::cout << "Error loading model! " <<
                 importer.GetErrorString() << std::endl;
  }
  else
  {
    ProcessNode(scene->mRootNode, scene);
  }
}

unsigned int ModelComponent::LoadTextureFromFile(const std::string& aFilePath)
{
  std::cout << aFilePath << std::endl;
  ILuint imageID;          // Used for loading images with DevIL
  unsigned int textureID;  // Used for OpenGL texture binding

  ilGenImages(1, &imageID);
  ilBindImage(imageID);

  // Attempt to load the image.
  ILboolean success = ilLoadImage(aFilePath.c_str());
  if(success == IL_TRUE)
  {
    // Attempt to convert image to RGBA.
    success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    if(success == IL_TRUE)
    {
      // Generate an OpenGL texture.
      unsigned char* data = ilGetData();
      int w = ilGetInteger(IL_IMAGE_WIDTH);
      int h = ilGetInteger(IL_IMAGE_HEIGHT);

      glGenTextures(1, &textureID);
      glBindTexture(GL_TEXTURE_2D, textureID);
      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   GL_RGBA,
                   w,
                   h,
                   0,
                   GL_RGBA,
                   GL_UNSIGNED_BYTE,
                   data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      ilDeleteImages(1, &imageID);
    }
    else
    {
      std::cout << "Error converting image! " << ilGetError() << std::endl;
      ilDeleteImages(1, &imageID);
    }
  }
  else
  {
    std::cout << "Error loading image! " << ilGetError() << std::endl;
  }

  return textureID;
}

void ModelComponent::ProcessNode(aiNode* aNode, const aiScene* aScene)
{
  // Process each mesh contained in the given node.
  for(unsigned int i = 0; i < aNode->mNumMeshes; ++i)
  {
    aiMesh* mesh = aScene->mMeshes[aNode->mMeshes[i]];
    AddChild(ProcessMesh(mesh, aScene));
  }

  // Process each of this node's children.
  for(unsigned int j = 0; j < aNode->mNumChildren; ++j)
  {
    ProcessNode(aNode->mChildren[j], aScene);
  }
}

std::unique_ptr<MeshComponent> ModelComponent::ProcessMesh(aiMesh* aMesh,
                                                           const aiScene* aScene)
{
  VertexList vertices;
  TextureList textures;
  IndexList indices;

  for(unsigned int i = 0; i < aMesh->mNumVertices; i++)
  {
    MeshVertex vertex;
    glm::vec3 vec;

    // Populate the vertex's position.
    vec.x = aMesh->mVertices[i].x;
    vec.y = aMesh->mVertices[i].y;
    vec.z = aMesh->mVertices[i].z;
    vertex.mPosition = vec;

    // Populate the vertex's normal vector.
    vec.x = aMesh->mNormals[i].x;
    vec.y = aMesh->mNormals[i].y;
    vec.z = aMesh->mNormals[i].z;
    vertex.mNormal = vec;

    // Populate the vertex's texture coordinates (if any exist).
    if(aMesh->mTextureCoords[0] != nullptr)
    {
      // TODO: Assimp allows for up to 8 different texture coordinates
      // per vertex. Here we only grab the first pair; we might want
      // more later.
      glm::vec2 vec;
      vec.x = aMesh->mTextureCoords[0][i].x;
      vec.y = aMesh->mTextureCoords[0][i].y;
      vertex.mTexCoords = vec;
    }
    else
    {
      vertex.mTexCoords = glm::vec2(0.0, 0.0);
    }

    vertices.push_back(vertex);
  }

  // Assimp defines each mesh as having an array of faces, from which
  // we can extract the drawing order indices.
  for(unsigned int i = 0; i < aMesh->mNumFaces; ++i)
  {
    for(unsigned int j = 0; j < aMesh->mFaces[i].mNumIndices; ++j)
    {
      indices.emplace_back(aMesh->mFaces[i].mIndices[j]);
    }
  }

  // If this mesh contains any materials, we need to load our
  // diffuse/specular textures from them.
  if(aMesh->mMaterialIndex >= 0)
  {
    aiMaterial* mat = aScene->mMaterials[aMesh->mMaterialIndex];

    // Load diffuse textures.
    aiTextureType type = aiTextureType_DIFFUSE;
    std::string typeString = "texture_diffuse";

    TextureList diffuseMaps = LoadMaterialTextures(mat, type, typeString);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // Load specular textures.
    type = aiTextureType_SPECULAR;
    typeString = "texture_specular";

    TextureList specularMaps = LoadMaterialTextures(mat, type, typeString);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }

  return std::make_unique<MeshComponent>(vertices, indices, textures);
}

TextureList ModelComponent::LoadMaterialTextures(aiMaterial* aMat,
                                                 aiTextureType aType,
                                                 const std::string& aName)
{
  TextureList textures;
  for(unsigned int i = 0; i < aMat->GetTextureCount(aType); ++i)
  {
    aiString str;
    aMat->GetTexture(aType, i, &str);

    // Skip loading already loaded textures.
    bool skip = false;
    for(const auto& t : mLoadedTextures)
    {
      if(t.mPath == str.C_Str())
      {
        textures.emplace_back(t);
        skip = true;
        break;
      }
    }

    if(!skip)
    {
      MeshTexture texture;
      texture.mId = LoadTextureFromFile(str.C_Str());
      texture.mType = aName;
      texture.mPath = str.C_Str();
      textures.emplace_back(texture);
      mLoadedTextures.emplace_back(texture);
    }
  }

  return textures;
}
