#ifndef MODELCOMPONENT_HPP
#define MODELCOMPONENT_HPP

#include <assimp/scene.h>

#include "MeshComponent.hpp"

namespace UrsineRenderer
{
  class ModelComponent : public GraphicalComponent
  {
    public:
      ModelComponent();

      void LoadModel(const std::string& aFilePath);
      void LoadModel(const void* aBuffer, size_t aBufLength);

    private:
      unsigned int LoadTextureFromFile(const std::string& aFilePath);
      void ProcessNode(aiNode* aNode, const aiScene* aScene);
      std::unique_ptr<MeshComponent> ProcessMesh(aiMesh* aMesh,
                                                 const aiScene* aScene);
      TextureList LoadMaterialTextures(aiMaterial* aMat,
                                       aiTextureType aType,
                                       const std::string& aName);

      TextureList mLoadedTextures;
  };
}

#endif
