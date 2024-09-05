#pragma once

namespace Time
{
    class System : public ISystem
    {
    public:
        System();

        void Initialize() noexcept override;
        void Update() noexcept override;
        
        float SetTimeScale(float timeScale) noexcept override;
        [[nodiscard]] float GetTimeScale() const noexcept override;
        
        [[nodiscard]] float GetDeltaMetaTime() const noexcept override;
        [[nodiscard]] float GetDeltaGameTime() const noexcept override;

    private:
        std::chrono::steady_clock::time_point _currentTime;
        std::chrono::steady_clock::time_point _previousTime;
        float _deltaTime;
        float _timeScale;
    };
}
