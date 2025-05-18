# Macroboard

DIY Macro keyboard with pedal support based on Arduino Micro.

This project contains the build files and firmware for an plug and play macro keyboard. It doesn't require any third party software on your PC instead it makes use of the **F13** - **F24** keys which are usually unused. The (optional) mode switch allows a secondary layer of macro keys (**F1** - **F12**).
In addition the board has a port for a sustain pedal from a E-Piano with automatic polarity detection. The design includes a separate mode switch for the pedal as well as a manual polarity switch to allow more exceptional use cases like push to mute in games where only push to talk is supported.

## Circuit

Contains the PCB design for the board based around an Arduino Micro development board.

Not all switches/keys need to be populated. You can omit _Special Key_, _Mode Switch_ and _Special Switch 1/2_ based on your needs and disable the corresponding features in the firmware.

## Firmware

Contains the Arduino sketch which should be flashed onto the Arduino Micro. The firmware relies on the Arduino Keyboard library and can be configured using macros in the `settings.h`.

## Case

Contains the FreeCAD as well as STL files for a simple printable enclosure for the _Macroboard_.
