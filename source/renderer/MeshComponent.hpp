#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "GraphicalComponent.hpp"

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

  class MeshComponent : public GraphicalComponent
  {
    public:
      MeshComponent();

      void Render() const override;

      void SetVertices(const VertexList& aVertices);
      VertexList GetVertices() const { return mVertices; }

      void SetIndices(const IndexList& aIndices);
      IndexList GetIndices() const { return mIndices; }

    private:
      void Initialize();

      unsigned int mVAO, mVBO, mEBO;

      VertexList mVertices;
      IndexList mIndices;
  };
}

#endif
