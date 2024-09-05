#pragma once

namespace Engine
{
    class Colored
    {
    public:
        explicit Colored(D2D1_COLOR_F color);

        void SetColor(D2D1_COLOR_F color);

    protected:
        D2D1_COLOR_F _color;
    };
}
