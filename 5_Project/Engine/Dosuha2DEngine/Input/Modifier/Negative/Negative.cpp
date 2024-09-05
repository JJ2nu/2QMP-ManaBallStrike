#include "pch.h"
#include "Negative.h"

Input::Value& Input::Modifier::Negative::operator()(Value& value) const
{
    value.x = -value.x;
    value.y = -value.y;
    return value;
}
