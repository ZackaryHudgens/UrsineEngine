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

  /**
   * A struct that contains all data needed to render a vertex.
   *
   * A vector of each MeshVertex is passed into the active Shader
   * object each time Render() is called; there they can be accessed
   * at the corresponding input location.
   */
  struct MeshVertex
  {
    glm::vec3 mPosition;   // location = 0
    glm::vec3 mColor;      // location = 1
    glm::vec2 mTexCoords;  // location = 2
  };

  typedef std::vector<MeshVertex> VertexList;
  typedef std::vector<unsigned int> IndexList;
  typedef std::vector<Texture> TextureList;

  /**
   * A MeshComponent is essentially all the information needed to render
   * an object; this includes a vector of vertices with positions, indices,
   * colors and texture coordinates for each one.
   */
  class MeshComponent : public GraphicalComponent
  {
    public:

      /**
       * Constructor. Upon construction, IDs are generated for the vertex
       * array, vertex buffer and element buffer.
       */
      MeshComponent();

      /**
       * Renders this MeshComponent using the current vertex information.
       * This process is repeated relative to each Camera in the current
       * Scene.
       */
      void Render() const override;

      /**
       * Sets the OpenGL draw mode. For example, to render this MeshComponent
       * as a wireframe, the mode should be set to RenderMode::eLINE_LOOP.
       *
       * @param aMode The draw mode to use on the next Render() call.
       */
      void SetRenderMode(const RenderMode& aMode) { mMode = aMode; }

      /**
       * Adds a vertex to be drawn on the next Render() call.
       *
       * @param aVertex The MeshVertex to add.
       */
      void AddVertex(const MeshVertex& aVertex);

      /**
       * Adds an index to the end of the vertex draw order; for example,
       * adding an index of 3 will cause the third vertex to be drawn
       * on the next Render() call. Then adding an index of 4 will cause
       * the third and then the fourth vertices to be drawn on the next
       * Render() call.
       *
       * @param aIndex The index of the vertex to draw.
       */
      void AddIndex(unsigned int aIndex);

      /**
       * Adds a Texture object to this MeshComponent. Each Texture will be
       * accessed by each MeshVertex and drawn according to that MeshVertex's
       * texture coordinates; in other words, if a MeshVertex has a texture
       * coordinate pair of (0.5, 0.5), then each Texture will be sampled at
       * (0.5, 0.5) for that MeshVertex.
       *
       * This function fails if the maximum number of Texture objects has
       * already been reached (16).
       *
       * @param aTexture The Texture object to add.
       */
      void AddTexture(const Texture& aTexture);

      /**
       * Returns all MeshVertices for this MeshComponent.
       *
       * @return A vector of MeshVertices.
       */
      VertexList& GetVertices() { return mVertices; }

      /**
       * Returns the vertex draw order for this MeshComponent.
       *
       * @return A vector of unsigned ints.
       */
      IndexList& GetIndices() { return mIndices; }

      /**
       * Returns all Textures for this MeshComponent.
       *
       * @return A vector of Textures.
       */
      TextureList& GetTextures() { return mTextures; }

    private:
      unsigned int mVAO, mVBO, mEBO;

      RenderMode mMode;

      VertexList mVertices;
      IndexList mIndices;
      TextureList mTextures;
  };
}

#endif
