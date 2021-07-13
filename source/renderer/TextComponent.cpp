#include "TextComponent.hpp"

#include "Environment.hpp"

using UrsineRenderer::TextComponent;

/**
 * A static cache of font data; used to prevent reloading
 * the same fonts over and over again.
 */
std::map<std::string, FT_Face> gLoadedFontsMap;

/*****************************************************************************/
TextComponent::TextComponent()
  : mCurrentFontFace(nullptr)
{
}

/*****************************************************************************/
void TextComponent::Render() const
{
  mMesh.Render();
}

/*****************************************************************************/
bool TextComponent::SetFont(const std::string& aFontPath)
{
  bool success = true;

  // If this font has already been loaded, don't load it again.
  auto foundFont = gLoadedFontsMap.find(aFontPath);
  if(foundFont != gLoadedFontsMap.end())
  {
    mCurrentFontFace = &(foundFont->second);
  }
  else
  {
    FT_Face newFace;

    //TODO: load all glyphs into one texture
    if(FT_New_Face(*env.GetFontLibrary(), aFontPath.c_str(), 0, &newFace))
    {
    }
  }

  return success;
}
