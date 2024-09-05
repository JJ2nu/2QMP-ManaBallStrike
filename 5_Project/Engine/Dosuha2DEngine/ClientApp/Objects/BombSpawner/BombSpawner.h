#pragma once

namespace Client::Object
{
    class BombSpawner : public Engine::Object::Base
    {
    public:
        BombSpawner();

        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

        float _spawnTime;
        float _spawnInterval;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
    };
}