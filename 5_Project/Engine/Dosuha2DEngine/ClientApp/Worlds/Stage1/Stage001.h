#pragma once
#include "../BattleStage/BattleStage.h"
#include "BackgroundMusic/BackgroundMusic.h"

namespace Client::World
{
    class Stage001 : public BattleStage , public BackgroundMusic
    {
    public:
        Stage001();
    protected:
        void OnCreateObject() override;
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
        void OnPostFinalize() override;

    private:
        bool _changeBgm;
    };
}
