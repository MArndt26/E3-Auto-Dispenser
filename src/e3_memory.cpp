#include "e3_memory.h"
#include <EEPROM.h>

E3_Memory::E3_Memory()
{
    E3_Memory::read();
}

void E3_Memory::read()
{
#ifdef PERMANENT_MEM
    EEPROM.get(fn1_addr, fn1);
    EEPROM.get(fn2_addr, fn2);
    EEPROM.get(fn3_addr, fn3);

    int size = 3;
    int arr[] = {fn1, fn2, fn3};

    for (int i = 0; i < size; i++)
    {
        if (arr[i] > MAX_VAL)
        {
            //limit the maximum value for the storage variable
            arr[i] = MAX_VAL;
        }
    }
#else
    fn1 = 100;
    fn2 = 200;
    fn3 = 300;
#endif
}

void E3_Memory::write()
{
#ifdef PERMANENT_MEM
    EEPROM.put(fn1_addr, fn1);
    EEPROM.put(fn2_addr, fn2);
    EEPROM.put(fn3_addr, fn3);
#endif
}

void E3_Memory::write(int i)
{
#ifdef PERMANENT_MEM
    if (i == 1)
    {
        EEPROM.put(fn1_addr, fn1);
    }
    else if (i == 2)
    {
        EEPROM.put(fn2_addr, fn2);
    }
    else if (i == 3)
    {
        EEPROM.put(fn3_addr, fn3);
    }
#endif
}