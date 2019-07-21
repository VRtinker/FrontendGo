#ifndef ANDROID_BUTTONMAPPING_H
#define ANDROID_BUTTONMAPPING_H

#include "App.h"

class MappedButton {
public:
    bool IsSet = false;
    // Gamepad = 0; LTouch = 1; RTouch = 2
    int    InputDevice;
    int    ButtonIndex;
    uint    Button;
};

class MappedButtons {
public:
    MappedButton Buttons[2];
};

const int DeviceGamepad       = 0;
const int DeviceLeftTouch     = 1;
const int DeviceRightTouch    = 2;

const uint EmuButton_A                  = 0x00000001;
const uint EmuButton_B                  = 0x00000002;
const uint EmuButton_RThumb             = 0x00000004;
const uint EmuButton_RShoulder          = 0x00000008;
const uint EmuButton_X                  = 0x00000100;
const uint EmuButton_Y                  = 0x00000200;
const uint EmuButton_LThumb             = 0x00000400;
const uint EmuButton_LShoulder          = 0x00000800;
const uint EmuButton_Up                 = 0x00010000;
const uint EmuButton_Down               = 0x00020000;
const uint EmuButton_Left               = 0x00040000;
const uint EmuButton_Right              = 0x00080000;
const uint EmuButton_Enter              = 0x00100000;
const uint EmuButton_Back               = 0x00200000;
const uint EmuButton_GripTrigger        = 0x04000000;
const uint EmuButton_Trigger            = 0x20000000;
const uint EmuButton_Joystick           = 0x80000000;

const uint EmuButton_LeftStickUp        = 0x00000010;
const uint EmuButton_LeftStickDown      = 0x00000020;
const uint EmuButton_LeftStickLeft      = 0x00000040;
const uint EmuButton_LeftStickRight     = 0x00000080;
const uint EmuButton_RightStickUp       = 0x00400000;
const uint EmuButton_RightStickDown     = 0x00800000;
const uint EmuButton_RightStickLeft     = 0x01000000;
const uint EmuButton_RightStickRight    = 0x02000000;
const uint EmuButton_L2                 = 0x08000000;
const uint EmuButton_R2                 = 0x10000000;

const int EmuButtonCount = 27;
const uint ButtonMapping[] = {
        0x00000001, 0x00000002, 0x00000004, 0x00000008,
        0x00000100, 0x00000200, 0x00000400, 0x00000800,
        0x00010000, 0x00020000, 0x00040000, 0x00080000,
        0x00100000, 0x00200000, 0x04000000, 0x20000000,
        0x80000000, 0x00000010, 0x00000020, 0x00000040,
        0x00000080, 0x00400000, 0x00800000, 0x01000000,
        0x02000000, 0x08000000, 0x10000000 };

void GetButtonIndex();

#endif //ANDROID_BUTTONMAPPING_H
