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

      void AddVertex(const MeshVertex& aVertex);
      void AddIndex(unsigned int aIndex);

    private:
      void Initialize();

      unsigned int mVAO, mVBO, mEBO;

      VertexList mVertices;
      IndexList mIndices;
  };
}

#endif
