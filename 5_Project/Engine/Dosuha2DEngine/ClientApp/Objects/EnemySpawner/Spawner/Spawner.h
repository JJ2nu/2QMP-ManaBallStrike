#pragma once

namespace Client::Object
{
    class Spawner : public Engine::Object::Base
    {
    public:
        using Event = std::function<void()>;
        
        explicit Spawner(Manager::SpawnerData data, const Engine::Math::Vector2& location, bool isBottom);
        void OnCreateComponent() override;
        void OnSetup() override;
        void SetTargetScene(const std::shared_ptr<Engine::Scene>& targetScene);
        const Engine::Math::Rect& GetBound() const override;
        void NextWave();

        void BindOnWaveEnd(Event event);
        void BindOnFinish(Event event);

        bool IsFinished() const;
   

    protected:
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

    private:
        void SpawnWave(float deltaTime);
        void SpawnEnemy(float deltaTime);
        void UpdateRenderOrder();
        Engine::Math::Vector2 GetSpawnLocation() const;

        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::Bitmap> _bitmapComponent;
        std::shared_ptr<Engine::Component::Animation> _doorEye;
        std::shared_ptr<Engine::Component::Animation> _doorShadow;

        Manager::SpawnerData _data;
        bool _isBottom;
        std::shared_ptr<Engine::Scene> _targetScene;
        size_t _waveIndex;
        bool _isSpawning;
        std::deque<Manager::Wave::EnemyType> _currentWave;
        float _waveElapsedTime;
        float _spawnElapsedTime;

        Event _onWaveEnd;
        Event _onFinish;

        Engine::Math::Vector2 _location;

        bool _isFinish;
    };
}
