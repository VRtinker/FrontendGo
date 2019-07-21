#ifndef ANDROID_MENU_H
#define ANDROID_MENU_H

#include <VrApi/Include/VrApi_Input.h>
#include <VrAppSupport/VrGUI/Src/VRMenu.h>
#include "Emulator.h"
#include "App.h"

using namespace OVR;

namespace MenuGo {
    void SetUpMenu();
    void UpdateMenu();
    void DrawMenu();
    ovrFrameResult Update(App *app, const ovrFrameInput &vrFrame);
}

void UpdateInputDevices(App *app, const ovrFrameInput &vrFrame);

//==============================================================
// ovrInputDeviceBase
// Abstract base class for generically tracking controllers of different types.
class ovrInputDeviceBase
{
public:
    ovrInputDeviceBase()
    {
    }

    virtual	~ovrInputDeviceBase()
    {
    }

    virtual const ovrInputCapabilityHeader *	GetCaps() const = 0;
    virtual ovrControllerType 					GetType() const = 0;
    virtual ovrDeviceID							GetDeviceID() const = 0;
    virtual const char *						GetName() const = 0;
};

//==============================================================
// ovrInputDevice_Gamepad
class ovrInputDevice_Gamepad : public ovrInputDeviceBase
{
public:
    ovrInputDevice_Gamepad( const ovrInputGamepadCapabilities & caps )
            : ovrInputDeviceBase()
            , Caps( caps )
    {
    }

    virtual ~ovrInputDevice_Gamepad()
    {
    }

    static ovrInputDeviceBase * 				Create( App & app, const ovrInputGamepadCapabilities & gamepadCapabilities );

    virtual const ovrInputCapabilityHeader *	GetCaps() const OVR_OVERRIDE { return &Caps.Header; }
    virtual ovrControllerType 					GetType() const OVR_OVERRIDE { return Caps.Header.Type; }
    virtual ovrDeviceID  						GetDeviceID() const OVR_OVERRIDE { return Caps.Header.DeviceID; }
    virtual const char *						GetName() const OVR_OVERRIDE { return "Gamepad"; }

    const ovrInputGamepadCapabilities &			GetGamepadCaps() const { return Caps; }

private:
    ovrInputGamepadCapabilities	Caps;
};

//==============================================================
// ovrInputDevice_TrackedRemote
class ovrInputDevice_TrackedRemote : public ovrInputDeviceBase
{
public:
    ovrInputDevice_TrackedRemote( const ovrInputTrackedRemoteCapabilities & caps,
                                  const uint8_t lastRecenterCount )
            : ovrInputDeviceBase()
            , MinTrackpad( FLT_MAX )
            , MaxTrackpad( -FLT_MAX )
            , Caps( caps )
            , LastRecenterCount( lastRecenterCount )
    {
        IsActiveInputDevice = false;
    }

    virtual ~ovrInputDevice_TrackedRemote()
    {
    }

    static ovrInputDeviceBase * 				Create( App & app, const ovrInputTrackedRemoteCapabilities & capsHeader );
    virtual const ovrInputCapabilityHeader *	GetCaps() const OVR_OVERRIDE { return &Caps.Header; }
    virtual ovrControllerType 					GetType() const OVR_OVERRIDE { return Caps.Header.Type; }
    virtual ovrDeviceID 						GetDeviceID() const OVR_OVERRIDE { return Caps.Header.DeviceID; }
    virtual const char *						GetName() const OVR_OVERRIDE { return "TrackedRemote"; }

    bool                                        IsLeftHand() const
    {
        return ( Caps.ControllerCapabilities & ovrControllerCaps_LeftHand ) != 0;
    }

    const ovrTracking &							GetTracking() const { return Tracking; }
    void										SetTracking( const ovrTracking & tracking ) { Tracking = tracking; }

    uint8_t										GetLastRecenterCount() const { return LastRecenterCount; }
    void										SetLastRecenterCount( const uint8_t c ) { LastRecenterCount = c; }

    const ovrInputTrackedRemoteCapabilities &	GetTrackedRemoteCaps() const { return Caps; }

    Vector2f									MinTrackpad;
    Vector2f									MaxTrackpad;
    bool										IsActiveInputDevice;

private:
    ovrInputTrackedRemoteCapabilities	Caps;
    uint8_t								LastRecenterCount;
    ovrTracking							Tracking;
};

#endif //ANDROID_MENU_H