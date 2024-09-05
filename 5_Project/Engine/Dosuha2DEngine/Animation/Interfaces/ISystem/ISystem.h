#pragma once

namespace Animation
{
    struct ISystem : Dosuha::IReferenceCounter
    {
        virtual void CreateLoader(ILoader** loader) = 0;
    };
}
