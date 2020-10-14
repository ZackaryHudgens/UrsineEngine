#ifndef MODELCOMPONENT_HPP
#define MODELCOMPONENT_HPP

#include <assimp/scene.h>

#include "MeshComponent.hpp"

namespace core
{
  typedef std::vector<MeshTexture> TextureList;
  typedef std::vector<MeshComponent> MeshList;

  class ModelComponent : public GraphicalComponent
  {
    public:
      ModelComponent();

      void Update() override {}
      void Render() const override;

      void SetShader(Shader& aShader) override;
      void DisableShader() override;

      void LoadModel(const std::string& aFilePath);

    private:
      unsigned int LoadTextureFromFile(const std::string& aFilePath);
      void ProcessNode(aiNode* aNode, const aiScene* aScene);
      MeshComponent ProcessMesh(aiMesh* aMesh, const aiScene* aScene);
      TextureList LoadMaterialTextures(aiMaterial* aMat,
                                       aiTextureType aType,
                                       const std::string& aName);

      std::vector<MeshTexture> mLoadedTextures;
      MeshList mMeshes;
  };
}

#endif
