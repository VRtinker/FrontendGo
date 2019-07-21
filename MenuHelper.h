#ifndef ANDROID_MENUHELPER_H
#define ANDROID_MENUHELPER_H

#include <string>
#include <vector>
#include "App.h"
#include "FontMaster.h"

using namespace OVR;

class MenuItem {
public:
    bool Selectable = false;
    bool Selected = false;
    bool Visible = true;
    int PosX = 100, PosY = 100;
    int ScrollDelay = 15;
    int ScrollTimeV = 5;
    int ScrollTimeH = 5;
    int Tag = 0;
    int Tag2 = 0;
    ovrVector4f Color;
    ovrVector4f SelectionColor;

    void (*OnSelectFunction)(MenuItem *item, int direction) = nullptr;

    void (*UpdateFunction)(MenuItem *item, uint *buttonState, uint *lastButtonState) = nullptr;

    MenuItem();

    virtual ~MenuItem() {}

    virtual void Update(uint *buttonState, uint *lastButtonState);

    virtual int PressedUp();

    virtual int PressedDown();

    virtual int PressedLeft();

    virtual int PressedRight();

    virtual int PressedEnter();

    virtual void OnSelect(int direction);

    virtual void Select();

    virtual void Unselect();

    virtual void DrawText(float offsetX, float offsetY, float transparency);

    virtual void DrawTexture(float offsetX, float offsetY, float transparency);
};

class Menu {
public:
    std::vector<MenuItem *> MenuItems;

    int CurrentSelection = 0;
    int buttonDownCount = 0;

public:
    void (*BackPress)() = nullptr;

    void Init();

    bool ButtonPressed(uint *buttonState, uint *lastButtonState, uint device, uint button);

    void MoveSelection(int dir, bool onSelect);

    void Update(uint *buttonState, uint *lastButtonState);

    void Draw(int transitionDirX, int transitionDirY, float moveProgress, int moveDist,
              float fadeProgress);
};

class MenuLabel : public MenuItem {
public:
    int containerX, containerY, containerWidth, containerHeight;

    FontManager::RenderFont *Font;

    std::string Text;

    MenuLabel(FontManager::RenderFont *font, std::string text, int posX, int posY, int width,
              int height, ovrVector4f color);

    void SetText(std::string newText);

    virtual ~MenuLabel();

    virtual void DrawText(float offsetX, float offsetY, float transparency) override;
};

class MenuImage : public MenuItem {
public:
    MenuImage(GLuint imageId, int posX, int posY, int width, int height, ovrVector4f color);

    ovrVector4f Color;

    GLuint ImageId;

    int Width, Height;

    virtual ~MenuImage();

    virtual void DrawTexture(float offsetX, float offsetY, float transparency) override;
};

class MenuButton : public MenuItem {
public:
    MenuButton(FontManager::RenderFont *font, GLuint iconId, std::string text, int posX, int posY,
               void (*pressFunction)(MenuItem *item), void (*leftFunction)(MenuItem *item), void (*rightFunction)(MenuItem *item));

    MenuButton(FontManager::RenderFont *font, GLuint iconId, std::string text, int posX, int posY, int width, int height,
               void (*pressFunction)(MenuItem *item), void (*leftFunction)(MenuItem *item), void (*rightFunction)(MenuItem *item));

    virtual ~MenuButton();

    void (*PressFunction)(MenuItem *item) = nullptr;

    void (*LeftFunction)(MenuItem *item) = nullptr;

    void (*RightFunction)(MenuItem *item) = nullptr;

    FontManager::RenderFont *Font;

    GLuint IconId;

    std::string Text;

    int ContainerWidth = 0;
    int OffsetX = 0;

    virtual int PressedLeft() override;

    virtual int PressedRight() override;

    virtual int PressedEnter() override;

    void SetText(std::string newText);

    virtual void DrawText(float offsetX, float offsetY, float transparency) override;

    virtual void DrawTexture(float offsetX, float offsetY, float transparency) override;
};

class MenuContainer : public MenuItem {
public:
    MenuContainer() { Selectable = true; }

    virtual ~MenuContainer() {}

    std::vector<MenuItem *> MenuItems;

    virtual int PressedLeft() override;

    virtual int PressedRight() override;

    virtual int PressedEnter() override;

    virtual void DrawText(float offsetX, float offsetY, float transparency) override;

    virtual void DrawTexture(float offsetX, float offsetY, float transparency) override;

    virtual void Select() override;

    virtual void Unselect() override;
};

template<class MyType>
class MenuList : public MenuItem {
public:
    MenuList(FontManager::RenderFont *font, void (*pressFunction)(MyType *),
             std::vector<MyType> *romList, int posX, int posY, int width, int height) {
        Font = font;
        PressFunction = pressFunction;
        ItemList = romList;

        PosX = posX;
        PosY = posY;
        Width = width;
        Height = height;

        listItemSize = (font->FontSize + 8);
        itemOffsetY = 4;
        maxListItems = height / listItemSize;
        scrollbarHeight = height;
        listStartY = posY + (scrollbarHeight - (maxListItems * listItemSize)) / 2;
        Selectable = true;
    }

    virtual ~MenuList() {}

    FontManager::RenderFont *Font;

    void (*PressFunction)(MyType *item) = nullptr;

    std::vector<MyType> *ItemList;

    int maxListItems = 0;
    int Width = 0, Height = 0;
    int scrollbarWidth = 14, scrollbarHeight = 0;
    int listItemSize = 0;
    int itemOffsetY = 0;
    int listStartY = 0;

    int CurrentSelection = 0;
    int menuListState = 0;

    float menuListFState = 0;

    int PressedUp() {
        CurrentSelection--;
        if (CurrentSelection < 0) CurrentSelection = (int) (ItemList->size() - 1);
        return 1;
    }

    int PressedDown() {
        CurrentSelection++;
        if (CurrentSelection >= ItemList->size()) CurrentSelection = 0;
        return 1;
    }

    int PressedEnter() {
        if (ItemList->size() <= 0) return 1;

        if (PressFunction != nullptr) PressFunction(&ItemList->at(CurrentSelection));

        return 1;
    }

    void Update(uint *buttonState, uint *lastButtonState) {
        // scroll the list to the current Selection
        if (CurrentSelection - 2 < menuListState && menuListState > 0) {
            menuListState--;
        }
        if (CurrentSelection + 2 >= menuListState + maxListItems &&
            menuListState + maxListItems < ItemList->size()) {
            menuListState++;
        }

        float dist = menuListState - menuListFState;

        if (dist < -0.0125f) {
            if (dist < -0.25f)
                menuListFState += dist * 0.1f + 0.00625f;
            else
                menuListFState -= ((dist * 8) * (dist * 8)) * 0.00625f + 0.00625f;
        } else if (dist > 0.0125f) {
            if (dist > 0.25f)
                menuListFState += dist * 0.1f + 0.00625f;
            else
                menuListFState += ((dist * 8) * (dist * 8)) * 0.00625f + 0.00625f;
        } else
            menuListFState = menuListState;
    }

    virtual void DrawText(float offsetX, float offsetY, float transparency) override;

    virtual void DrawTexture(float offsetX, float offsetY, float transparency) override;
};

#endif  // ANDROID_MENUHELPER_H
