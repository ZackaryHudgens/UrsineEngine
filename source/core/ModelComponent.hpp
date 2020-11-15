#ifndef MODELCOMPONENT_HPP
#define MODELCOMPONENT_HPP

#include <assimp/scene.h>

#include "MeshComponent.hpp"

namespace core
{
  class ModelComponent : public GraphicalComponent
  {
    public:
      ModelComponent();

      void Update() override {}

      void LoadModel(const std::string& aFilePath);

    private:
      void PrivateRender() const override {}

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
