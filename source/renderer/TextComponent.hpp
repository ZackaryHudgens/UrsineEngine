#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GraphicalComponent.hpp"
#include "MeshComponent.hpp"

namespace UrsineRenderer
{
  /**
   */
  class TextComponent : public GraphicalComponent
  {
    public:

      /**
       */
      TextComponent();

      /**
       */
      void Render() const override;

      /**
       */
      void SetText(const std::string& aText) { mText = aText; };

      /**
       */
      std::string GetText() const { return mText; };

      /**
       * Loads and sets the given font. Fonts loaded with this function
       * are cached, so they don't have to be loaded multiple times. This
       * function fails if the given font doesn't exist or can't be loaded.
       *
       * @param aFontPath The path to a font.
       * @return True if successful, false otherwise.
       */
      bool SetFont(const std::string& aFontPath);

      /**
       * Sets the font size. This function fails if there is no current
       * font specified.
       *
       * @param aSize The desired size of the font.
       * @return True if successful, false otherwise.
       */
      bool SetSize(unsigned int aSize);

    private:

      /**
       */
      void GenerateTextureAtlas();

      MeshComponent mMesh;

      std::string mCurrentFont;
      std::string mText;
  };
}

#endif
