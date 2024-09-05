#include "pch.h"
#include "SwizzleAxis.h"

Input::Value& Input::Modifier::SwizzleAxis::operator()(Value& value) const
{
    const float temp = value.x;
    value.x = value.y;
    value.y = temp;
    return value;
}
