// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "<https://github.com/willwm/layouts-model01>"
#endif

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 * Includes modifications from': https://github.com/keyboardio/Chrysalis-Firmware-Bundle/blob/master/Keyboardio/Model01/experimental/Model01.ino
 */

#include "Kaleidoscope.h"

#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-NumPad.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-USB-Quirks.h"

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LED-ActiveLayerColor.h"
#include "Kaleidoscope-LED-ActiveModColor.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-LED-Stalker.h"

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum
{
  MACRO_VERSION_INFO,
  MACRO_ONESHOT_CANCEL,
};

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum
{
  PRIMARY,
  NUMPAD,
  FUNCTION
}; // layers



/* Key Aliases */
#define Key_Grave       Key_Backtick
#define Key_PrtSc       Key_PrintScreen
#define Key_Del         Key_Delete
#define Key_BkSp        Key_Backspace

#define Key_LCurly      Key_LeftCurlyBracket
#define Key_RCurly      Key_RightCurlyBracket

#define Key_Mute        Consumer_Mute
#define Key_VolUp       Consumer_VolumeIncrement
#define Key_VolDn       Consumer_VolumeDecrement

#define Key_LEDNext     Key_LEDEffectNext
#define Key_LEDPrev     Key_LEDEffectPrevious

#define Key_CtrlAlt     LCTRL(Key_LeftAlt)
#define Key_CtrlAltUp   LCTRL(LALT(Key_UpArrow))
#define Key_CtrlAltDn   LCTRL(LALT(Key_DownArrow))

#define M_Version       M(MACRO_VERSION_INFO)
#define M_OSCancel      M(MACRO_ONESHOT_CANCEL)

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(

    [PRIMARY] = KEYMAP_STACKED(Key_Esc, Key_1, Key_2, Key_3, Key_4, Key_5, Key_Del,
                               Key_Grave, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
                               Key_PageUp, Key_A, Key_S, Key_D, Key_F, Key_G,
                               Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, OSM(LeftAlt),
                               OSM(LeftControl), Key_BkSp, Key_LGui, OSM(LeftShift),
                               OSL(FUNCTION),

                               Key_BkSp, Key_6, Key_7, Key_8, Key_9, Key_0, Key_Minus,
                               Key_Enter, Key_Y, Key_U, Key_I, Key_O, Key_P, Key_Equals,
                               Key_H, Key_J, Key_K, Key_L, Key_Semicolon, Key_Quote,
                               Key_RGui, Key_N, Key_M, Key_Comma, Key_Period, Key_Slash, Key_Minus,
                               OSM(RightShift), OSM(RightAlt), Key_Space, OSM(RightControl),
                               OSL(FUNCTION)),

    [NUMPAD] = KEYMAP_STACKED(___, ___, ___, ___, ___, ___, ___,
                              ___, ___, Key_Home, Key_UpArrow, Key_End, ___, ___,
                              ___, ___, Key_LArrow, Key_DnArrow, Key_RArrow, ___,
                              ___, ___, ___, ___, ___, ___, Key_Esc,
                              ___, ___, ___, ___,
                              ___,

                              ___, ___, Key_Keypad7, Key_Keypad8, Key_Keypad9, Key_KeypadSubtract, UnlockLayer(NUMPAD),
                              ___, ___, Key_Keypad4, Key_Keypad5, Key_Keypad6, Key_KeypadAdd, Key_KeypadEquals,
                              ___, Key_Keypad1, Key_Keypad2, Key_Keypad3, Key_KeypadMultiply, Key_Insert,
                              ___, ___, Key_Keypad0, ___, ___, Key_KeypadDivide, Key_Enter,
                              ___, ___, ___, ___,
                              ___),

    [FUNCTION] = KEYMAP_STACKED(___, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, Key_BkSp,
                                Key_LEDNext, M_OSCancel, ___, ___, ___, ___, ___,
                                Key_Home, ___, ___, ___, ___, ___,
                                Key_End, Key_PrtSc, Key_Cut, Key_Copy, Key_Paste, Key_CtrlAlt, ___,
                                ___, ___, ___, ___,
                                ___,

                                Key_Del, Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, LockLayer(NUMPAD),
                                ___, Key_Home, Key_LCurly, Key_RCurly, Key_LBracket, Key_RBracket, Key_F11,
                                Key_LeftArrow, Key_DnArrow, Key_UpArrow, Key_RightArrow, ___, Key_F12,
                                ___, Key_End, Key_Mute, Key_VolDn, Key_VolUp, Key_Backslash, Key_Pipe,
                                ___, ___, ___, ___,
                                ___)) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
    case MACRO_VERSION_INFO:
      if (keyToggledOn(keyState)) {
        Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
        Macros.type(PSTR(BUILD_INFORMATION));
      }
      break;

    case MACRO_ONESHOT_CANCEL:
      if (keyToggledOn(keyState))
        OneShot.cancel(true);
      break;
  }

  return MACRO_NONE;
}


// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.

static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event)
{
  switch (event)
  {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event)
{
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum
{
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE
};

/** A tiny wrapper, to be used by MagicCombo.
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/* A "reset" of sorts. */
static void doubleFnCombo(uint8_t combo_index) {
  LockLayer(FUNCTION);
  LEDControl.refreshAll();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = doubleFnCombo,
                  // Left Fn + Right Fn
                  .keys = {R3C6, R3C9}});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
    // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
    // editable keymap in EEPROM.
    EEPROMSettings,
    EEPROMKeymap,

    // Focus allows bi-directional communication with the host, and is the
    // interface through which the keymap in EEPROM can be edited.
    Focus,

    // FocusSettingsCommand adds a few Focus commands, intended to aid in
    // changing some settings of the keyboard, such as the default layer (via the
    // `settings.defaultLayer` command)
    FocusSettingsCommand,

    // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
    // both debugging, and in backing up one's EEPROM contents.
    FocusEEPROMCommand,

    // LEDControl provides support for other LED modes
    LEDControl,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    LEDRainbowWaveEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    //solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,
    solidGreen, solidBlue, solidIndigo, solidViolet,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    NumPad,

    // The macros plugin adds support for macros
    Macros,

    // The HostPowerManagement plugin allows us to turn LEDs off when then host
    // goes to sleep, and resume them when it wakes up.
    HostPowerManagement,

    // The MagicCombo plugin lets you use key combinations to trigger custom
    // actions - a bit like Macros, but triggered by pressing multiple keys at the
    // same time.
    MagicCombo,

    // https://github.com/keyboardio/Kaleidoscope-Escape-OneShot
    OneShot,
    EscapeOneShot,

    // The USBQuirks plugin lets you do some things with USB that we aren't
    // comfortable - or able - to do automatically, but can be useful
    // nevertheless. Such as toggling the key report protocol between Boot (used
    // by BIOSes) and Report (NKRO).
    USBQuirks,

    // LEDActiveLayerColorEffect and ActiveModColor
    LEDActiveLayerColorEffect,
    ActiveModColorEffect);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  static const cRGB layerColormap[] PROGMEM = {
    CRGB(128, 0, 0),
    CRGB(0, 128, 0)
  };

  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  //LEDOff.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command.
  EEPROMKeymap.setup(5, EEPROMKeymap.Mode::EXTEND);

  // https://github.com/keyboardio/Kaleidoscope/blob/master/examples/LEDs/LED-ActiveLayerColor/LED-ActiveLayerColor.ino
  LEDActiveLayerColorEffect.setColormap(layerColormap);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop()
{
  Kaleidoscope.loop();
}
