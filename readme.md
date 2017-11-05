# PG5500 Embedded Systems assignment 02: alarm clock

## Functionality

The screen displays the current time, date, and day of the week, along with four alarms. All the alarms can be set independently of each other and are almost completely independent.

The one exception to their independence is that they all play sound to the same pin, which means turning off one alarm turns off all alarms. This would be a simple thing to rectify with more pins and speakers, however, it is the author's opinion that if you want to turn off an alarm, you probably want them all to stop ringing and wouldn't want to have to figure out wich one you want.

Active alarms are green, inactive alarms are red, and if you are currently editing one, it will be highlighted in orange and grey.

### Manual

Seeing as the alarm comes with so many input keys and different modes, it is probably worth giving a brief introduction to it all.

The keypad operates in two different modes and uses the `#` and `*` keys as special 'leader' keys, meaning that you use them for key combinations (or chords, if you will), and that they expect a follow-up key press to determine what action should be executed.

#### Modes

The alarm operates in two different modes: normal mode and edit mode, with some key combinations being shared between them.

**Shared keymap**

| Leader | Key | Result                     |
|--------|-----|----------------------------|
|None    |[A-D]| Toggles corresponding alarm
|`#`     |[A-D]| Edit corresponding alarm
|`*`     |[A-D]| Turn off ringing alarm


Normal mode lets you toggle all the alarms and enter into edit mode, as well as to turn off any ringing alarms.

**Normal mode keymap**

| Leader | Key | Result                     |
|--------|-----|----------------------------|
|`*`     |`*`  | Turn off ringing alarm

Edit mode lets you edit one specific alarm at a time and will highlight the current alarm in orange and grey, with the time division (hours or minutes) being edited in orange.

**Edit mode keymap**

| Leader | Key | Result                     |
|--------|-----|----------------------------|
|None    |[0-9]| Enters numeric value into time division
|`*`     |`*`  | Switch active time division
|`#`     |`#`  | Set alarm
|`#`     |`*`  | Cancel and return alarm to previous time

## Schematics

The schematics are drawn in Fritzing and are available in both Fritzing and SVG file formats.

The TFT screen in the schematics is not the exact same one as has been used, but the wiring corresponds to how it should be wired on an ST7735. For clarity, the connected pins are (in order bottom to top):

    - VCC
    - GND
    - SCL
    - SDA
    - DC
    - RES
    - CS

## Video documentation

The end product is documented in [this video](https://youtu.be/z0CtOcUocZ4).

## Code

### Libraries

For interfacing with the various parts and for structuring certain parts of the application, the following libraries have been used:

#### TFT

The TFT library handles all writing to the screen and makes the TFT very easy to work with.

Bundled in with the Arduino IDE. Information available [here](https://www.arduino.cc/en/Reference/TFTLibrary)

#### RTClib

Time management library for RTC devices by Adafruit.

Available on [GitHub](https://github.com/adafruit/RTClib)

#### SimpleTimer

Library for setting up time-based, repeating functions with Arduino, used in the `tick()` function in `app.ino`.

By Marcello Romani.

Available on the [Arduino Playground](https://playground.arduino.cc/Code/SimpleTimer)

#### Keypad

Library for working with the external keypad, used in `InputHandler.h`.

Adaptations to the setup for a 4x4 matrix taken from [this guide](http://www.instructables.com/id/Connecting-a-4-x-4-Membrane-Keypad-to-an-Arduino/)

By Mark Stanley and Alexander Brevig.

Available on the [Arduino Playground](https://playground.arduino.cc/Code/Keypad)

### Notes

#### Header file inconsistency

Throughout working on the project and splitting the behaviour into smaller classes, the approach used changed quite drastically. Initially, everything was split into corresponding `.cpp` and `.h` files, but as the project grew, this approach became more and more difficult to work with, and for the last few classes, they were implemented directly in the `.h` files.

This latter approach is more in line with what is usually seen in most languages these days, and while there may well be good arguments for splitting up declaration and definition, in a project like this it appears to cause more issues and overhead than any potential benefit.

That said, the classes that were originally split remain that way, as there is neither time nor will left to correct it.

### Further development

Further refinements to the alarm clock include things like a more pleasing (or at least interesting) alarm tone, the potential for timers as well as alarms, and just general tweaks. However, I am fairly happy with the execution, and would not consider these to be very important to the current iteration.

## Authors

Thomas Hartmann
