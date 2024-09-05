#pragma once

namespace Engine::Manager
{
    class Time : public Base<Time>
    {
        friend const std::shared_ptr<Time>& Manager::Base<Time>::GetInstance();

    public:
        static void Initialize() noexcept;
        static void Update() noexcept;

        static float SetTimeScale(float timeScale) noexcept;
        [[nodiscard]] static float GetTimeScale() noexcept;

        [[nodiscard]] static float GetDeltaMetaTime() noexcept;
        [[nodiscard]] static float GetDeltaGameTime() noexcept;

    protected:
        Time();

    private:
        std::unique_ptr<::Time::ISystem> _system;
    };
}
