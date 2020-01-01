#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>

#include "Vector2D.hpp"

namespace gCore
{
  class Texture
  {
    public:
      Texture();
      ~Texture();

      bool LoadFromFile(const std::string& aFilePath);
      bool LoadFromPixels(GLuint* aPixelData, int aWidth, int aHeight);

      void Render(const Vector2D& aLocation, double aScalar = 1);
      void RenderPortion(const Vector2D& aLocation, const SDL_Rect& aPortion, double aScalar = 1);

    private:
      void FreeTexture();

      GLuint mTextureID;
      GLuint mTextureWidth;
      GLuint mTextureHeight;
  };
}

#endif
