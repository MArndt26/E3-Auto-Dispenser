/*-----------STATE VARS-------------*/
const byte HOME_STATE = 0;
const byte PRESET_STATE = 1;
const byte PROGRAM_STATE = 2;
const byte RUN_STATE = 3;

byte curState = HOME_STATE; //starts in HOME_STATE