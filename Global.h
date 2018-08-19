#ifndef ANDROID_RESOURCES_H
#define ANDROID_RESOURCES_H

#include "Menu.h"

extern const std::string STR_HEADER, STR_VERSION;
extern const float DisplayRefreshRate;

extern const int SAVE_FILE_VERSION;

extern const int HEADER_HEIGHT, BOTTOM_HEIGHT, MENU_WIDTH, MENU_HEIGHT;

extern int menuItemSize, saveSlot;
extern bool menuOpen, loadedRom, followHead;

extern uint SelectButton, BackButton;
extern Menu *currentMenu;

extern ovrVector4f sliderColor, textColorVersion, headerTextColor, MenuBackgroundColor,
        MenuBackgroundOverlayColor, MenuBackgroundOverlayColorLight, MenuBackgroundOverlayHeader,
        BatteryBackgroundColor, textColor, textSelectionColor, MenuBottomColor, textColorBattery;

extern std::string appStoragePath, saveFilePath, romFolderPath;

extern FontManager::RenderFont fontHeader, fontBattery, fontTime, fontMenu, fontList, fontBottom,
        fontSlot, fontVersion, fontSmall;

extern GLuint textureBackgroundId, textureIdMenu, textureHeaderIconId, textureGbIconId,
        textureGbcIconId, textureVbIconId, textureIpdIconId,
        textureSaveIconId,
        textureLoadIconId, textureWhiteId, textureResumeId, textureSettingsId, texuterLeftRightIconId,
        textureUpDownIconId, textureResetIconId, textureSaveSlotIconId, textureLoadRomIconId,
        textureBackIconId, textureMoveIconId, textureDistanceIconId, textureResetViewIconId,
        textureScaleIconId, textureMappingIconId, texturePaletteIconId, textureButtonAIconId,
        textureButtonBIconId, textureButtonXIconId, textureButtonYIconId, textureFollowHeadIconId,
        textureDMGIconId, textureExitIconId, threedeeIconId, twodeeIconId, mappingLeftDownId, mappingLeftUpId, mappingLeftLeftId, mappingLeftRightId,
        mappingRightDownId, mappingRightUpId, mappingRightLeftId, mappingRightRightId, mappingStartId, mappingSelectId, mappingTriggerLeft, mappingTriggerRight;

extern const ovrJava *java;
extern jclass clsData;

void SaveSettings();

void ResetMenuState();

#endif //ANDROID_RESOURCES_H
