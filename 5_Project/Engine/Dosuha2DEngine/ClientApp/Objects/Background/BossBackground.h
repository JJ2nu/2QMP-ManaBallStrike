#pragma once
#include "Background.h"

namespace Client::Object
{
    class BossBackground : public Background
    {
    public:
        void OnCreateComponent() override;
    };
}
