#ifndef FONT_MASTER
#define FONT_MASTER

#include <glm/glm.hpp>
#include <map>
#include <string>
#include "App.h"

using namespace OVR;

namespace FontManager {

    struct Character {
        glm::fvec4 Position;  // the position of the character inside of the texture
        glm::ivec2 Size;      // size of glyph
        glm::ivec2 Bearing;   // offset from baseline to left/top of glyph
        GLuint Advance;       // offset to advance to next glyph
    };

    struct RenderFont {
        int FontSize;
        int offsetY;
        int PHeight;
        int PStart;
        GLuint textureID;
        std::map<GLchar, Character> Characters;
    };

    void Init(int MenuWidth, int MenuHeight);

    void CloseFontLoader();

    int GetWidth(RenderFont font, std::string text);

    void LoadFont(RenderFont *font, const char *filePath, uint fontSize);

    void LoadFontFromAssets(App *app, RenderFont *font, const char *filePath, uint fontSize);

    void Begin();

    void RenderText(RenderFont font, std::string text, GLfloat x, GLfloat y, GLfloat scale, ovrVector4f color, float transparency);

    void RenderFontTexture(FontManager::RenderFont font, ovrVector4f color, float transparency);

    void Close();

}  // namespace FontManager

#endif