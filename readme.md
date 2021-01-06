# Auto Adhesive Dispenser

###### This Project is used to create a control pad and scale to dispense adhesive until a weight limit is reached.

## External Libraries used:

- EEPROM.h
- Keypad.h
- Wire.h
- LiquidCrystal_I2c.h
- HX711.h

## Resources/Inspiration:

### Load Cell:

- https://www.instructables.com/id/Arduino-Bathroom-Scale-With-50-Kg-Load-Cells-and-H/
- https://create.arduino.cc/projecthub/Fedeasche/arduino-uno-high-precision-counting-scale-3f484b
- https://github.com/bogde/HX711

### Keypad:

- https://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/

### Display:

- https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/
- https://maxpromer.github.io/LCD-Character-Creator/
- http://avtanski.net/projects/lcd/

## Schematic:

![schematic](/docs/images/schematic.png)

## Development tools

- Download [Arduino IDE](https://www.arduino.cc/en/software)
- Download [Visual Studio Code](https://code.visualstudio.com/download) (VS code)
- Open VS code and click on the Extensions button on left nav bar (Ctrl+Shift+X)
- Search for PlatformIO IDE and install
- use [git bash](https://git-scm.com/downloads) or [wsl](https://docs.microsoft.com/en-us/windows/wsl/install-win10) to pull from this repository to your local machine
  - see [GitHub documentation](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/cloning-a-repository) for how to do this

## Calibration Procedure

- Go to main.h and ensure that `CALIBRATE` is `#defined` to be `1`:
  - `#define CALIBRATE 1`
- upload sketch by pressing the [->] upload button
- follow calibration instructions:
  - Remove all weight from scale
  - After readings begin, tare scale then place known weight on scale
  - For Computer Serial interation use the following
    ```
    q, w, e, r --> calibration factor += 0.1, 1, 10, 100
    a, s, d, f --> calibration factor -= 0.1, 1, 10, 100
    ```
  - For Keypad Matrix interaction use the following
    ```
    1, 2, 3, A --> calibration factor += 0.1, 1, 10, 100
    4, 5, 6, B --> calibration factor -= 0.1, 1, 10, 100
    ```
  - Press `t` on computer or `D` button on keypad to tare scale
  - Using the instructions above manipulate the calibration factor until the known value matches the displayed value

## TODO:

- [x] Digitally filter/smooth scale data
- [x] Test with Hardware
- [ ] Change all String variables to char arrays
- [ ] Only update display when text has changed for performance update
