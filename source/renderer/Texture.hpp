#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <map>

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
       * Constructor.
       */
      Texture();

      /**
       * Loads an image from a file. This uses the DevIL image loading
       * library; most image filetypes are supported. Additionally,
       * files loaded with this function are statically cached,
       * so they don't have to be loaded multiple times over the course
       * of the game.
       *
       * @param aFilePath The path to an image file.
       */
      void LoadImageFromFile(const std::string& aFilePath);

      /**
       * Binds the current texture in OpenGL.
       */
      void Activate() const;

      /**
       * Returns the TextureData associated with this texture.
       *
       * @return A TextureData object for this texture.
       */
      TextureData GetData() const { return mData; }

    private:
      TextureData mData;
  };
}

#endif
