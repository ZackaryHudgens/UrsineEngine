#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GraphicalComponent.hpp"
#include "MeshComponent.hpp"
#include "Texture.hpp"

namespace UrsineRenderer
{
  /**
   * A struct that contains all the information to render a single
   * character.
   */
  struct Character
  {
    char mChar;              // The character to represent
    unsigned int mWidth;     // The width of the character in pixels
    unsigned int mHeight;    // The height of the character in pixels
    unsigned int mXBearing;  // The horizontal distance from the local y-axis in pixels
    unsigned int mYBearing;  // The vertical distance above the local x-axis in pixels
    unsigned int mAdvance;   // The horizontal kerning for this character (in 1/64th pixels)
  };

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
       * Loads and sets the given font. This function fails if
       * the given font doesn't exist or can't be loaded.
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
       *
       */
      void LoadCharacters();

      /**
       */
      void HandleShaderAdded(GraphicalComponent* aComponent,
                             const Shader& aShader,\
                             const std::string& aName);

      /**
       */
      void HandleShaderRemoved(GraphicalComponent* aComponent,
                               const std::string& aName);

      /**
       */
      void HandleShaderChanged(GraphicalComponent* aComponent,
                               const std::string& aName);

      FT_Face mCurrentFont;

      std::map<Character, MeshComponent> mCharacterMeshMap;

      std::string mText;
  };
}

#endif
