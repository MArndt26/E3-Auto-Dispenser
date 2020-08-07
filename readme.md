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

![schematic](/images/schematic.png)

## TODO:

- [x] Digitally filter/smooth scale data
- [x] Test with Hardware
- [ ] Change all String variables to char arrays
- [ ] Only update display when text has changed for performance update

## Collabroators
- MArndt26
- JArndt94
