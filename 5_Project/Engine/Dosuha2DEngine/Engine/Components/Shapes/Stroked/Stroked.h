#pragma once

namespace Engine
{
    class Stroked
    {
    public:
        explicit Stroked(float strokeWidth = 1.0f);

        void SetStrokeWidth(float strokeWidth);

    protected:
        float _strokeWidth;
    };
}
