#pragma once
#include "../Stage/Stage.h"
#include "BackgroundMusic/BackgroundMusic.h"

namespace Client::World
{
    class MainStage : public Stage, public BackgroundMusic
    {
    public:
        MainStage();

    protected:
        void OnCreateObject() override;
        void OnSetup() override;
        void OnPostFinalize() override;

    private:
        std::shared_ptr<Object::Title> _title;
        std::shared_ptr<Object::ControlPlayer> _player;
    };
}
