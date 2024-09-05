#pragma once

namespace Input::Modifier
{
    struct Negative : IModifier
    {
        Value& operator()(Value& value) const override;
    };
}
