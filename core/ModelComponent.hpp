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
      ModelComponent(const std::string& aFilePath);

      void Update() override {}
      void Render() const override;

      void SetShader(Shader* aShader) override;

    private:
      void Load(const std::string& aFilePath);
      unsigned int LoadTextureFromFile(const std::string& aFilePath);
      void ProcessNode(aiNode* aNode, const aiScene* aScene);
      MeshComponent ProcessMesh(aiMesh* aMesh, const aiScene* aScene);
      std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* aMat,
                                                    aiTextureType aType,
                                                    const std::string& aName);

      std::string mDirectory;
      MeshList mMeshes;
  };
}

#endif
