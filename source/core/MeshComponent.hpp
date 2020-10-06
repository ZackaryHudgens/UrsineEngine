#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "GraphicalComponent.hpp"

namespace core
{
  struct MeshVertex
  {
    glm::vec3 mPosition;  // 0
    glm::vec3 mNormal;    // 1
    glm::vec2 mTexCoords; // 2
  };

  struct MeshTexture
  {
    unsigned int mId;
    std::string mType;
    std::string mPath;
  };

  class MeshComponent : public GraphicalComponent
  {
    public:
      MeshComponent(const std::vector<MeshVertex>& aVertices,
                    const std::vector<unsigned int> aIndices,
                    const std::vector<MeshTexture> aTextures);

      void Update() override {}
      void Render() const override;

    private:
      void Initialize();

      unsigned int mVAO, mVBO, mEBO;

      std::vector<MeshVertex>   mVertices;
      std::vector<unsigned int> mIndices;
      std::vector<MeshTexture>  mTextures;
  };
}

#endif
