#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <map>

namespace UrsineRenderer
{
  struct TextureData
  {
    unsigned int mID     = 0;
    unsigned int mWidth  = 0;
    unsigned int mHeight = 0;
  };

  class Texture
  {
    public:
      Texture();

      void LoadImageFromFile(const std::string& aFilePath);
      void Activate() const;

      unsigned int GetHeight() const { return mData.mHeight; }
      unsigned int GetWidth() const  { return mData.mWidth; }

    private:
      TextureData mData;
  };
}

#endif
