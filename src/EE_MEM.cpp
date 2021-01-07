// /*-------------EEPROM VARS------------*/
// //https://www.arduino.cc/en/Reference/EEPROMGet

// #include "EE_MEM.h"
// #include <EEPROM.h>
// #include <LiquidCrystal_I2C.h>
// #include "lcd.h"
// #include "buttons.h"

// int checkValidMem(char c)
// {
//     if ((c <= '9' && c >= '0') || c == '.') //only read in digits and dp as valid input
//     {
//         return true;
//     }
//     return false;
// }

// int readChunck(int start, byte mem_type)
// {
//     String update = "";
//     int i;
//     for (i = start; i < start + DISP_SET_STR_MAX_LEN; i++)
//     {
//         c = EEPROM.read(i);
// #if HUSH
//         Serial.print("c: ");
//         Serial.print(c);
//         Serial.print(", i: ");
//         Serial.println(i);
// #endif
//         if (checkValidMem(c)) //only read in digits and dp as valid input
//         {
//             update += c;
//         }
//     }

//     switch (mem_type)
//     {
//     case SET_MEM:
//         setString = update;
// #if HUSH
//         Serial.print("setString = ");
//         Serial.println(setString);
// #endif
//         break;
//     case FN1_MEM:
//         fn1String = update;
// #if HUSH
//         Serial.print("fn1String = ");
//         Serial.println(fn1String);
// #endif
//         break;
//     case FN2_MEM:
//         fn2String = update;
// #if HUSH
//         Serial.print("fn2String = ");
//         Serial.println(fn2String);
// #endif
//         break;
//     case FN3_MEM:
//         fn3String = update;
// #if HUSH
//         Serial.print("fn3String = ");
//         Serial.println(fn3String);
// #endif
//         break;
//     }

//     return i;
// }

// /* Function reads in the following variables from eeprom memory:
//  *      -setStr
//  */
// void EEPROM_ReadAll()
// {
//     int eeAddressOffset = 0; //reset eeAddressOffset

//     eeAddressOffset = readChunck(eeAddressOffset, SET_MEM);

//     eeAddressOffset = readChunck(eeAddressOffset, FN1_MEM);

//     eeAddressOffset = readChunck(eeAddressOffset, FN2_MEM);

//     eeAddressOffset = readChunck(eeAddressOffset, FN3_MEM);
// }

// int writeChunk(int start, byte mem_type)
// {
//     String update;

//     switch (mem_type)
//     {
//     case SET_MEM:
//         update = setString;
//         break;
//     case FN1_MEM:
//         update = fn1String;
//         break;
//     case FN2_MEM:
//         update = fn2String;
//         break;
//     case FN3_MEM:
//         update = fn3String;
//         break;
//     }

// #if HUSH
//     Serial.print("update: ");
//     Serial.println(update);
// #endif

//     unsigned int i = 0; //index var
//     for (i = start; i < start + DISP_SET_STR_MAX_LEN; i++)
//     {
// #if HUSH
//         Serial.print("c[");
//         Serial.print(i - start);
//         Serial.print(']');
// #endif

//         if (i - start < update.length())
//         {
// #if HUSH
//             Serial.print(update[i - start]);
// #endif
//             EEPROM.update(i, update[i - start]);
//         }
//         else
//         {
// #if HUSH
//             Serial.print("*");
// #endif
//             EEPROM.update(i, 0xFF); //clear memory
//         }

// #if HUSH
//         Serial.print(", ind: ");
//         Serial.println(i);
// #endif
//     }
//     return i;
// }

// void EEPROM_WriteAll()
// {
//     int eeAddrOffset = 0;

//     eeAddrOffset = writeChunk(eeAddrOffset, SET_MEM);

//     eeAddrOffset = writeChunk(eeAddrOffset, FN1_MEM);

//     eeAddrOffset = writeChunk(eeAddrOffset, FN2_MEM);

//     eeAddrOffset = writeChunk(eeAddrOffset, FN3_MEM);
// }

// int save()
// {
//     if (cur_FN_Button == FN1_Button)
//     {
//         fn1String = curString;
//     }
//     else if (cur_FN_Button == FN2_Button)
//     {
//         fn2String = curString;
//     }
//     else if (cur_FN_Button == FN3_Button)
//     {
//         fn3String = curString;
//     }
//     else
//     {
// #if HUSH_ERRORS
//         Serial.println("tried to save invalid fn button");
// #endif
//     }
//     //else not trying to save fn button
//     Serial.print("fn1String: ");
//     Serial.println(fn1String);
//     EEPROM_WriteAll();
//     setString = curString;
//     curString = "";
//     return true;
// }

// void memoryInit()
// {
//     EEPROM_ReadAll();
//     c = '\0'; //reset global character c

// #if HUSH
//     Serial.println("Memory Initialized");
// #endif
// }