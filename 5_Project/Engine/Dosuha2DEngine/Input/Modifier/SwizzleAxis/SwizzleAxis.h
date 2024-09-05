#pragma once

namespace Input::Modifier
{
    struct SwizzleAxis : IModifier
    {
        SwizzleAxis() {a = 19;};
        Value& operator()(Value& value) const override;
    };
}
