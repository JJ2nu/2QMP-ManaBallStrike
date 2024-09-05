#pragma once

namespace Time
{
    struct ISystem
    {
        ISystem() = default;
        ISystem(const ISystem& other) = default;
        ISystem(ISystem&& other) noexcept = default;
        ISystem& operator=(const ISystem& other) = default;
        ISystem& operator=(ISystem&& other) noexcept = default;
        virtual ~ISystem() = default;

        virtual void Initialize() noexcept = 0;
        virtual void Update() noexcept = 0;

        virtual float SetTimeScale(float timeScale) noexcept = 0;
        [[nodiscard]] virtual float GetTimeScale() const noexcept = 0;
        
        [[nodiscard]] virtual float GetDeltaMetaTime() const noexcept = 0;
        [[nodiscard]] virtual float GetDeltaGameTime() const noexcept = 0;
    };
}
