#pragma once
#include "../BattleStage/BattleStage.h"
#include "BackgroundMusic/BackgroundMusic.h"

namespace Client::World
{
    class Stage003 : public BattleStage, public BackgroundMusic
    {
    public:
        Stage003();

    protected:
        void OnCreateObject() override;
        void OnSetup() override;
        void OnPostFinalize() override;
    };
}
