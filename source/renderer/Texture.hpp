#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <map>

#include <GL/glew.h>

namespace UrsineRenderer
{
  /**
   * A struct containing helpful data for a Texture object.
   */
  struct TextureData
  {
    unsigned int mID     = 0;  // The OpenGL ID of this texture.
    unsigned int mWidth  = 0;  // The width of this texture in pixels.
    unsigned int mHeight = 0;  // The height of this texture in pixels.
  };

  /**
   * A class that encapsulates an OpenGL texture.
   */
  class Texture
  {
    public:

      /**
       * Constructor. Generates an empty OpenGL texture using glGenTextures().
       */
      Texture();

      /**
       * Creates an OpenGL texture using the path to an image file.
       * This uses the DevIL image loading library; most image filetypes
       * are supported. Additionally, files loaded with this function
       * are cached, so they don't have to be loaded multiple times over
       * the course of the game.
       *
       * Note that this class can only contain one texture at a time;
       * calling either CreateTexture function will overwrite any
       * current data.
       *
       * @param aFilePath The path to an image file.
       */
      void CreateTextureFromFile(const std::string& aFilePath);

      /**
       * Creates an OpenGL texture from preloaded image data.
       *
       * Note that this class can only contain one texture at a time;
       * calling either CreateTexture function will overwrite any
       * current data.
       *
       * @param aData A pointer to the image data.
       * @param aWidth The width of the image.
       * @param aHeight The height of the image.
       */
      void CreateTextureFromData(unsigned char* aData,
                                 unsigned int aWidth,
                                 unsigned int aHeight);

      /**
       * Binds the current texture in OpenGL.
       */
      void Activate() const;

      /**
       * Sets the OpenGL format for texture loading. This defaults to
       * GL_RGBA.
       *
       * @param aFormat The format to set.
       */
      void SetLoadFormat(GLint aFormat);

      /**
       * Returns the TextureData associated with this texture.
       *
       * @return A TextureData object for this texture.
       */
      TextureData GetData() const { return mData; }

    private:
      GLint mFormat;

      TextureData mData;
  };
}

#endif
