#pragma once

namespace Animation
{
    struct SourceRect
    {
        float left;
        float top;
        float right;
        float bottom;
    };

    struct Center
    {
        float x;
        float y;
    };

    struct FrameInfo
    {
        SourceRect sourceRect;
        Center center;
        float duration;
    };
}
