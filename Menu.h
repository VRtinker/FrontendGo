#ifndef ANDROID_MENU_H
#define ANDROID_MENU_H

#include "Emulator.h"
#include "App.h"

using namespace OVR;

namespace MenuGo {
    void SetUpMenu();
    void UpdateMenu();
    void DrawMenu();
    ovrFrameResult Update(App *app, const ovrFrameInput &vrFrame);
}

#endif //ANDROID_MENU_H