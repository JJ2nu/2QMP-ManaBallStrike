#pragma once

namespace Client
{
    namespace Object
    {
        class ControlPlayer;
        class Gate;
        class Title;
        class Background;
    }

    namespace World
    {
        class Stage : public Engine::World
        {
        public:
            using Event = std::function<void()>;
            void BindOnStageClear(Event event);
            void BindPlayerDeath(Event event) const;

        protected:
            void OnCreateObject() override;
            void OnSetup() override;
            //void OnPostUpdate(float d1, float d2) override;

            std::shared_ptr<Object::Gate> _gate;
            std::shared_ptr<Object::ControlPlayer> _player;
            std::shared_ptr<Object::Background> _background;

            Event _onStageClear;
        private:
        };
    }
}
