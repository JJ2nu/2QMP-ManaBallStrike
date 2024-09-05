#pragma once

namespace Client::Manager
{
    class Data : public Engine::Manager::Base<Data>
    {
        friend const std::shared_ptr<Data>& Engine::Manager::Base<Data>::GetInstance();

    public:
        static void Initialize();

        static void UpgradeHealth();
        static void UpgradeManaBall();
        static void UpgradeSpeed();
        static void UpgradeManaBallBounce();

        static float GetMaxHealthPoint();
        static float GetHealthPoint();
        static void SetHealthPoint(float value);

        static int GetMaxManaBallCount();
        static int GetManaBallCount();
        static void SetManaBallCount(int value);

        static float GetSpeed();

        static void ResetHealthPoint();
        static void ResetManaBallCount();

        static void SetMonsterCount(int count);
        static void AddMonsterCount(int count);
        static void DecreaseMonsterCount();

        static int GetAdditionalManaBallCount();

        static void Reset();

    private:
        std::shared_ptr<Engine::Manager::Observer<float>::Subject> _maxHealthPoint;
        std::shared_ptr<Engine::Manager::Observer<float>::Subject> _healthPoint;
        std::shared_ptr<Engine::Manager::Observer<int>::Subject> _maxManaBallCount;
        std::shared_ptr<Engine::Manager::Observer<int>::Subject> _manaBallCount;
        std::shared_ptr<Engine::Manager::Observer<float>::Subject> _speed;
        std::shared_ptr<Engine::Manager::Observer<int>::Subject> _monsterCount;

        float _additionalHealth;
        int _additionalManaBall;
        float _additionalSpeedRatio;
        int _additionalManaBallBounce;

        float _initialHealth;
        int _initialManaBall;
        float _initialSpeed;
    };
}
