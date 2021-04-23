#ifndef MESHCOMPONENT_HPP
#define MESHCOMPONENT_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "GraphicalComponent.hpp"
#include "Texture.hpp"

namespace UrsineRenderer
{
  /**
   * An enumeration for all supported OpenGL draw modes.
   * Values correspond to GL definitions and can be used
   * with glDrawElements.
   */
  enum RenderMode
  {
    ePOINTS     = 0x0000,
    eLINE_LOOP  = 0x0002,
    eLINE_STRIP = 0x0003,
    eTRIANGLES  = 0x0004
  };

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

      void SetRenderMode(const RenderMode& aMode) { mMode = aMode; }

      void AddVertex(const MeshVertex& aVertex);
      void AddIndex(unsigned int aIndex);
      void AddTexture(const Texture& aTexture);

      VertexList& GetVertices()  { return mVertices; }
      IndexList& GetIndices()    { return mIndices; }
      TextureList& GetTextures() { return mTextures; }

    private:
      void Initialize();

      unsigned int mVAO, mVBO, mEBO;

      RenderMode mMode;

      VertexList mVertices;
      IndexList mIndices;
      TextureList mTextures;
  };
}

#endif
