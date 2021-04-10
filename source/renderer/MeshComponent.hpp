#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "GraphicalComponent.hpp"
#include "Texture.hpp"

namespace UrsineRenderer
{
  struct MeshVertex
  {
    glm::vec3 mPosition;
    glm::vec3 mColor;
    glm::vec2 mTexCoords;
  };

  typedef std::vector<MeshVertex> VertexList;
  typedef std::vector<unsigned int> IndexList;
  typedef std::vector<Texture> TextureList;

  class MeshComponent : public GraphicalComponent
  {
    public:
      MeshComponent();

      void Render() const override;

      void AddVertex(const MeshVertex& aVertex);
      void AddIndex(unsigned int aIndex);
      void AddTexture(const Texture& aTexture);

    private:
      void Initialize();

      unsigned int mVAO, mVBO, mEBO;

      VertexList mVertices;
      IndexList mIndices;
      TextureList mTextures;
  };
}

#endif
