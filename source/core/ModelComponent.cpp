#include "ModelComponent.hpp"

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <il.h>

using core::MeshComponent;
using core::MeshTexture;
using core::MeshVertex;
using core::ModelComponent;
using core::TextureList;

ModelComponent::ModelComponent()
  : GraphicalComponent()
{
}

void ModelComponent::Render() const
{
  for(const auto& mesh : mMeshes)
  {
    mesh.Render();
  }
}

void ModelComponent::SetShader(Shader& aShader)
{
  for(auto& mesh : mMeshes)
  {
    mesh.SetShader(aShader);
  }

  GraphicalComponent::SetShader(aShader);
}

void ModelComponent::DisableShader()
{
  for(auto& mesh : mMeshes)
  {
    mesh.DisableShader();
  }

  GraphicalComponent::DisableShader();
}

void ModelComponent::LoadModel(const std::string& aFilePath)
{
  Assimp::Importer importer;
  unsigned int postProcessFlags = aiProcess_Triangulate | aiProcess_FlipUVs;
  const aiScene* scene = importer.ReadFile(aFilePath, postProcessFlags);

  if(scene == nullptr ||
     scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
     scene->mRootNode == nullptr)
  {
    std::cout << "Error loading model! " <<
                 importer.GetErrorString() << std::endl;
  }
  else
  {
    mDirectory = aFilePath.substr(0, aFilePath.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
  }
}

unsigned int ModelComponent::LoadTextureFromFile(const std::string& aFilePath)
{
  unsigned int textureID;
  ilGenImages(1, &textureID);
  ilBindImage(textureID);

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
      int w, h;

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
    }
    else
    {
      std::cout << "Error converting image! " << ilGetError() << std::endl;
      ilDeleteImages(1, &textureID);
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
    mMeshes.emplace_back(ProcessMesh(mesh, aScene));
  }

  // Process each of this node's children.
  for(unsigned int j = 0; j < aNode->mNumChildren; ++j)
  {
    ProcessNode(aNode->mChildren[j], aScene);
  }
}

MeshComponent ModelComponent::ProcessMesh(aiMesh* aMesh, const aiScene* aScene)
{
  std::vector<MeshVertex> vertices;
  std::vector<MeshTexture> textures;
  std::vector<unsigned int> indices;

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

    std::vector<MeshTexture> diffuseMaps = LoadMaterialTextures(mat,
                                                                type,
                                                                typeString);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // Load specular textures.
    type = aiTextureType_SPECULAR;
    typeString = "texture_specular";

    std::vector<MeshTexture> specularMaps = LoadMaterialTextures(mat,
                                                                 type,
                                                                 typeString);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }

  return MeshComponent(vertices, indices, textures);
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

    MeshTexture texture;
    ilGenImages(1, &texture.mId);
    texture.mType = aName;
    texture.mPath = str.C_Str();
    textures.emplace_back(texture);
  }

  return textures;
}
