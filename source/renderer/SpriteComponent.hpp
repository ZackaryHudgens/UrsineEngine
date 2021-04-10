#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "GraphicalComponent.hpp"
#include "MeshComponent.hpp"

namespace UrsineRenderer
{
  class SpriteComponent : public GraphicalComponent
  {
    public:
      SpriteComponent();

      void Render() const override;

      void SetTexture(const Texture& aTexture);
      void SetRenderDimensions(unsigned int aX,
                               unsigned int aY,
                               unsigned int aWidth,
                               unsigned int aHeight);

      MeshComponent& GetMesh() { return mMesh; }

    private:
      MeshComponent mMesh;
  };
}

#endif
