#include "e3_memory.h"
#include <EEPROM.h>

E3_Memory::E3_Memory()
{
    E3_Memory::readAll();
}

void E3_Memory::readAll()
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
    c_factor = 464.5f;
#endif
}

/**
 * Assuming that i is always in range 1 - 3
 */
void E3_Memory::writeFN(int i, int val)
{
    if (i == 1)
    {
        fn1 = val;
#ifdef PERMANENT_MEM
        EEPROM.put(fn1_ad, fn1);
#endif
    }
    else if (i == 2)
    {
        fn2 = val;
#ifdef PERMANENT_MEM
        EEPROM.put(fn2_addr, fn2);
#endif
    }
    else // i == 3
    {
        fn3 = val;
#ifdef PERMANENT_MEM
        EEPROM.put(fn3_addr, fn3);
#endif
    }
}

/**
 * returns -999 if i is not in range 1-3
 */
int E3_Memory::getFN(int i)
{
    int val = -999;
    if (i == 1)
    {
        val = fn1;
    }
    else if (i == 2)
    {
        val = fn2;
    }
    else if (i == 3)
    {
        val = fn3;
    }
    return val;
}

void E3_Memory::writeCF()
{
#ifdef PERMANENT_MEM
    EEPROM.put(c_fact_addr, c_factor);
#endif
}
