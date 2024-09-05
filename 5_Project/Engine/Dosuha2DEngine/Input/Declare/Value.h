#pragma once

namespace Input
{
    union Value
    {
        struct
        {
            short _;
            bool on;
        };

        struct
        {
            float scalar;
        };

        struct
        {
            float x;
            float y;
        };

        Value& operator+=(const Value& rhs);
        bool operator==(const Value& rhs) const;

        operator bool() const;

        static Value Zero();
    };

    inline Value& Value::operator+=(const Value& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    inline bool Value::operator==(const Value& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    inline Value::operator bool() const
    {
        return on;
    }

    inline Value Value::Zero()
    {
        return Value{};
    }
}
