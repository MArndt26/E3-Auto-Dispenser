#include "FixedPoint.h"

FixedPoint::FixedPoint()
{
    _val = 0;
}

FixedPoint operator+(const FixedPoint &lhs, const FixedPoint &rhs)
{
    FixedPoint temp;
    temp._val = lhs._val + rhs._val;
    return temp;
}

FixedPoint operator-(const FixedPoint &lhs, const FixedPoint &rhs)
{
    FixedPoint temp;
    temp._val = lhs._val - rhs._val;
    return temp;
}

FixedPoint operator*(const FixedPoint &lhs, const FixedPoint &rhs)
{
    FixedPoint temp;
    temp._val = lhs._val * rhs._val;
    return temp;
}

FixedPoint operator/(const FixedPoint &lhs, const FixedPoint &rhs)
{
    FixedPoint temp;
    temp._val = lhs._val / rhs._val;
    return temp;
}