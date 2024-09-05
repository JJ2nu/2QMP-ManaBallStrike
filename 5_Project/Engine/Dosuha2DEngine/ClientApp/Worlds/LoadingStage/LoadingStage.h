#pragma once
#include "BackgroundMusic/BackgroundMusic.h"

namespace Client
{
    namespace Object
    {
        class AutoMovePlayer;
    }

    namespace World
    {
        class LoadingStage : public Engine::World, public BackgroundMusic
        {
        public:
            using Event = std::function<void()>;

            LoadingStage();
            void BindRequestOpenUI(const Event& event);
            void StopLoop() const;
            void BindOnExit(Event event) const;

        protected:
            void OnCreateObject() override;
            void OnSetup() override;
            void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
            void OnPostFinalize() override;

        
        private:
            std::shared_ptr<Object::AutoMovePlayer> _player;
            Event _requestOpenUI;

            float _elapsedTime;
            float _delay;
            bool _isOpenUI;
        };
    }
}
