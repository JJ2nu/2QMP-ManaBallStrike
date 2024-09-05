#pragma once
#include "PlayerBase.h"

namespace Client::Object
{
    class AutoMovePlayer : public PlayerBase
    {
    public:
        using Event = std::function<void()>;

        explicit AutoMovePlayer(float initialYLocation);

        void BindOnExit(Event event);

        void LoopStop();

    protected:
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

    private:
        Event _onExit;
        bool _isLoopStop;
        float _endYLocation;
    };
}
