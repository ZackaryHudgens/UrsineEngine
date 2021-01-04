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

  typedef std::vector<MeshVertex> VertexList;
  typedef std::vector<unsigned int> IndexList;
  typedef std::vector<MeshTexture> TextureList;

  class MeshComponent : public GraphicalComponent
  {
    public:
      MeshComponent(const VertexList& aVertices,
                    const IndexList& aIndices,
                    const TextureList& aTextures);

    private:
      void Initialize();

      void PrivateRender() const override;

      unsigned int mVAO, mVBO, mEBO;

      VertexList mVertices;
      IndexList mIndices;
      TextureList mTextures;
  };
}

#endif
