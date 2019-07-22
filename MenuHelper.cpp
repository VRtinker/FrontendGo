#include "MenuHelper.h"
#include "FontMaster.h"
#include "DrawHelper.h"
#include "Global.h"
#include "ButtonMapping.h"

MenuItem::MenuItem() {
    Color = textColor;
    SelectionColor = textSelectionColor;
}

void MenuItem::OnSelect(int direction) {
    if (OnSelectFunction != nullptr) OnSelectFunction(this, direction);
}

void MenuItem::Update(uint *buttonState, uint *lastButtonState) {
    if (UpdateFunction != nullptr) UpdateFunction(this, buttonState, lastButtonState);
}

int MenuItem::PressedUp() { return 0; }

int MenuItem::PressedDown() { return 0; }

int MenuItem::PressedLeft() { return 0; }

int MenuItem::PressedRight() { return 0; }

int MenuItem::PressedEnter() { return 0; }

void MenuItem::Select() { Selected = true; }

void MenuItem::Unselect() { Selected = false; }

void MenuItem::DrawText(float offsetX, float offsetY, float transparency) {}

void MenuItem::DrawTexture(float offsetX, float offsetY, float transparency) {}

void MenuLabel::DrawText(float offsetX, float offsetY, float transparency) {
    if (Visible)
        FontManager::RenderText(*Font, Text, PosX + offsetX + (Selected ? 5 : 0), PosY + offsetY,
                                1.0f, Color,
                                transparency);
}

MenuLabel::MenuLabel(FontManager::RenderFont *font, std::string text, int posX, int posY, int width,
                     int height, ovrVector4f color) {
    Font = font;
    Color = color;

    containerX = posX;
    containerY = posY;
    containerWidth = width;
    containerHeight = height;

    SetText(text);
}

void MenuLabel::SetText(std::string newText) {
    Text = newText;
    // center text
    int textWidth = FontManager::GetWidth(*Font, newText);
    PosX = containerX + containerWidth / 2 - textWidth / 2;
    PosY = containerY + containerHeight / 2 - Font->PHeight / 2 - Font->PStart;
}

MenuLabel::~MenuLabel() {}

void MenuImage::DrawTexture(float offsetX, float offsetY, float transparency) {
    if (Visible)
        DrawHelper::DrawTexture(ImageId, PosX + offsetX + (Selected ? 5 : 0), PosY + offsetY, Width,
                                Height,
                                Color, transparency);
}

MenuImage::MenuImage(GLuint imageId, int posX, int posY, int width, int height, ovrVector4f color) {
    ImageId = imageId;
    PosX = posX;
    PosY = posY;
    Width = width;
    Height = height;
    Color = color;
}

MenuImage::~MenuImage() {}

MenuButton::MenuButton(FontManager::RenderFont *font, GLuint iconId, std::string text, int posX, int posY,
                       void (*pressFunction)(MenuItem *), void (*leftFunction)(MenuItem *), void (*rightFunction)(MenuItem *)) {
    PosX = posX;
    PosY = posY;
    IconId = iconId;
    Text = text;
    Font = font;
    PressFunction = pressFunction;
    LeftFunction = leftFunction;
    RightFunction = rightFunction;
    Selectable = true;
}

MenuButton::MenuButton(FontManager::RenderFont *font, GLuint iconId, std::string text, int posX, int posY, int width, int height,
                       void (*pressFunction)(MenuItem *), void (*leftFunction)(MenuItem *), void (*rightFunction)(MenuItem *)) {
    PosX = posX;
    PosY = posY + (int) (height / 2.0f - font->PHeight / 2.0f) - font->PStart;
    ContainerWidth = width;
    IconId = iconId;
    Font = font;
    PressFunction = pressFunction;
    LeftFunction = leftFunction;
    RightFunction = rightFunction;
    Selectable = true;
    SetText(text);
}

void MenuButton::DrawText(float offsetX, float offsetY, float transparency) {
    if (Visible)
        FontManager::RenderText(*Font, Text, PosX + (IconId > 0 ? 33 : 0) + (Selected ? 5 : 0) + offsetX + OffsetX,
                                PosY + offsetY, 1.0f, Selected ? SelectionColor : Color, transparency);
}

void MenuButton::DrawTexture(float offsetX, float offsetY, float transparency) {
    if (IconId > 0 && Visible)
        DrawHelper::DrawTexture(IconId, PosX + (Selected ? 5 : 0) + offsetX,
                                PosY + Font->PStart + Font->PHeight / 2 - 14 + offsetY, 28,
                                28, Selected ? SelectionColor : Color, transparency);
}

void MenuButton::SetText(std::string newText) {
    Text = newText;

    // center text
    if (ContainerWidth > 0) {
        int textWidth = FontManager::GetWidth(*Font, newText);
        OffsetX = ContainerWidth / 2 - textWidth / 2;
    }
}

MenuButton::~MenuButton() {}

int MenuButton::PressedLeft() {
    if (LeftFunction != nullptr) {
        LeftFunction(this);
        return 1;
    }
    return 0;
}

int MenuButton::PressedRight() {
    if (RightFunction != nullptr) {
        RightFunction(this);
        return 1;
    }
    return 0;
}

int MenuButton::PressedEnter() {
    if (PressFunction != nullptr) {
        PressFunction(this);
        return 1;
    }
    return 0;
}

void MenuContainer::DrawText(float offsetX, float offsetY, float transparency) {
    for (int i = 0; i < MenuItems.size(); ++i) {
        MenuItems.at(i)->DrawText(offsetX, offsetY, transparency);
    }
}

void MenuContainer::DrawTexture(float offsetX, float offsetY, float transparency) {
    for (int i = 0; i < MenuItems.size(); ++i) {
        MenuItems.at(i)->DrawTexture(offsetX, offsetY, transparency);
    }
}

int MenuContainer::PressedLeft() { return MenuItems.at(0)->PressedLeft(); }

int MenuContainer::PressedRight() { return MenuItems.at(0)->PressedRight(); }

int MenuContainer::PressedEnter() { return MenuItems.at(0)->PressedEnter(); }

void MenuContainer::Select() {
    for (int i = 0; i < MenuItems.size(); ++i) {
        MenuItems.at(i)->Select();
    }
}

void MenuContainer::Unselect() {
    for (int i = 0; i < MenuItems.size(); ++i) {
        MenuItems.at(i)->Unselect();
    }
}

void ClearButtonState(uint *buttonState) {
    for (int i = 0; i < 3; ++i) {
        buttonState[i] = 0;
    }
}

void Menu::Update(uint *buttonState, uint *lastButtonState) {
    MenuItems[CurrentSelection]->Unselect();

    if ((buttonState[DeviceGamepad] &
         (EmuButton_Up | EmuButton_Down | EmuButton_Left | EmuButton_Right |
          EmuButton_LeftStickUp | EmuButton_LeftStickDown | EmuButton_LeftStickLeft | EmuButton_LeftStickRight)) ||
        (buttonState[DeviceLeftTouch] & (EmuButton_Up | EmuButton_Down | EmuButton_Left | EmuButton_Right)) ||
        (buttonState[DeviceRightTouch] & (EmuButton_Up | EmuButton_Down | EmuButton_Left | EmuButton_Right))) {
        buttonDownCount++;
    } else {
        buttonDownCount = 0;
    }

    for (int i = 0; i < MenuItems.size(); ++i) {
        MenuItems[i]->Update(buttonState, lastButtonState);
    }

    if (ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_Left) ||
        ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_LeftStickLeft) ||
        ButtonPressed(buttonState, lastButtonState, DeviceLeftTouch, EmuButton_Left) ||
        ButtonPressed(buttonState, lastButtonState, DeviceRightTouch, EmuButton_Left)) {
        buttonDownCount -= MenuItems[CurrentSelection]->ScrollTimeH;
        if (MenuItems[CurrentSelection]->PressedLeft() != 0) {
            ClearButtonState(buttonState);
        }
    }

    if (ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_Right) ||
        ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_LeftStickRight) ||
        ButtonPressed(buttonState, lastButtonState, DeviceLeftTouch, EmuButton_Right) ||
        ButtonPressed(buttonState, lastButtonState, DeviceRightTouch, EmuButton_Right)) {
        buttonDownCount -= MenuItems[CurrentSelection]->ScrollTimeH;
        if (MenuItems[CurrentSelection]->PressedRight() != 0) {
            ClearButtonState(buttonState);
        }
    }

    if (ButtonPressed(buttonState, lastButtonState, DeviceGamepad, SwappSelectBackButton ? EmuButton_B : EmuButton_A) ||
        ButtonPressed(buttonState, lastButtonState, DeviceRightTouch, SwappSelectBackButton ? EmuButton_B : EmuButton_A)) {
        buttonDownCount -= MenuItems[CurrentSelection]->ScrollTimeH;
        if (MenuItems[CurrentSelection]->PressedEnter() != 0) {
            ClearButtonState(buttonState);
        }
    } else if (ButtonPressed(buttonState, lastButtonState, DeviceGamepad, SwappSelectBackButton ? EmuButton_A : EmuButton_B) ||
               ButtonPressed(buttonState, lastButtonState, DeviceRightTouch, SwappSelectBackButton ? EmuButton_A : EmuButton_B)) {
        if (BackPress != nullptr) BackPress();
    }

    if (ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_Up) ||
        ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_LeftStickUp) ||
        ButtonPressed(buttonState, lastButtonState, DeviceLeftTouch, EmuButton_Up) ||
        ButtonPressed(buttonState, lastButtonState, DeviceRightTouch, EmuButton_Up)) {
        buttonDownCount -= MenuItems[CurrentSelection]->ScrollTimeV;
        if (MenuItems[CurrentSelection]->PressedUp() == 0) {
            MoveSelection(-1, true);
        }
    }

    if (ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_Down) ||
        ButtonPressed(buttonState, lastButtonState, DeviceGamepad, EmuButton_LeftStickDown) ||
        ButtonPressed(buttonState, lastButtonState, DeviceLeftTouch, EmuButton_Down) ||
        ButtonPressed(buttonState, lastButtonState, DeviceRightTouch, EmuButton_Down)) {
        buttonDownCount -= MenuItems[CurrentSelection]->ScrollTimeV;
        if (MenuItems[CurrentSelection]->PressedDown() == 0) {
            MoveSelection(1, true);
        }
    }

    MenuItems[CurrentSelection]->Select();
}

void Menu::Draw(int transitionDirX, int transitionDirY, float moveProgress, int moveDist,
                float fadeProgress) {
    // draw the menu textures
    for (uint i = 0; i < MenuItems.size(); i++)
        MenuItems[i]->DrawTexture(transitionDirX * moveProgress * moveDist,
                                  transitionDirY * moveProgress * moveDist, fadeProgress);

    // draw menu text
    FontManager::Begin();
    for (uint i = 0; i < MenuItems.size(); i++)
        MenuItems[i]->DrawText(transitionDirX * moveProgress * moveDist,
                               transitionDirY * moveProgress * moveDist, fadeProgress);
    FontManager::Close();
}

void Menu::MoveSelection(int dir, bool onSelect) {
    // WARNIGN: this will not work if there is nothing selectable
    // OVR_LOG("Move %i" + dir);
    do {
        CurrentSelection += dir;
        if (CurrentSelection < 0) CurrentSelection = (int) (MenuItems.size() - 1);
        if (CurrentSelection >= MenuItems.size()) CurrentSelection = 0;
    } while (!MenuItems[CurrentSelection]->Selectable);

    if (onSelect)
        MenuItems[CurrentSelection]->OnSelect(dir);
}

bool Menu::ButtonPressed(uint *buttonState, uint *lastButtonState, uint device, uint button) {
    return (buttonState[device] & button) && (
            !(lastButtonState[device] & button) ||
            buttonDownCount > MenuItems[CurrentSelection]->ScrollDelay);
}

void Menu::Init() { MenuItems[CurrentSelection]->Select(); }
