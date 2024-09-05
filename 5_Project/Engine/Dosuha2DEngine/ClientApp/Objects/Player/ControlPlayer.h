#pragma once
#include "PlayerBase.h"

namespace Client
{
    namespace Component
    {
        class TimingBar;
        class Indicator;
        class DashMovement;
        class Staff;
        class SwingEffect;
    }

    class ManaBallPool
    {
        struct Element;

    public:
        explicit ManaBallPool(const size_t size, const float respawnTime)
            : _pool(size, Element(respawnTime))
        {
        }

        void Update(const float deltaGameTime)
        {
            for (auto& element : _pool)
            {
                element.Update(deltaGameTime);
            }
        }

        [[nodiscard]] size_t GetSize() const
        {
            return _pool.size();
        }

        [[nodiscard]] int GetAliveCount() const
        {
            return std::accumulate(_pool.begin(), _pool.end(), 0, [](const size_t count, const Element& element)
            {
                return element.IsAlive() ? count + 1 : count;
            });
        }

        [[nodiscard]] bool AnyAlive() const
        {
            return std::ranges::any_of(_pool, [](const Element& element)
            {
                return element.IsAlive();
            });
        }

        void UseOne(const size_t index)
        {
            _pool[index].SetLimbo();
        }

        void RestoreOne(const size_t index)
        {
            _pool[index].SetDead();
        }

        [[nodiscard]] size_t GetAliveIndex() const
        {
            const auto iter = std::ranges::find_if(_pool, [](const Element& element)
            {
                return element.IsAlive();
            });
            if (iter == _pool.end()) return -1;
            return std::distance(_pool.begin(), iter);
        }

    private:
        std::vector<Element> _pool;

        struct Element
        {
            enum class State : uint8_t
            {
                Alive,
                Limbo,
                Dead
            };

            explicit Element(const float respawnTime)
                : state(State::Alive), respawnTime(respawnTime), elapsedTime(0.f)
            {
            }

            void SetAlive()
            {
                state = State::Alive;
            }

            void SetLimbo()
            {
                state = State::Limbo;
            }

            void SetDead()
            {
                state = State::Dead;
            }

            [[nodiscard]] bool IsAlive() const
            {
                return state == State::Alive;
            }

            void Update(const float deltaGameTime)
            {
                if (state != State::Dead) return;
                elapsedTime += deltaGameTime;
                if (elapsedTime < respawnTime) return;
                state = State::Alive;
                elapsedTime = 0.f;
            }

            State state;
            float respawnTime;
            float elapsedTime;
        };
    };

    namespace Object
    {
        class ControlPlayer : public PlayerBase
        {
        public:
            using Event = std::function<void()>;

            ControlPlayer(float initialYLocation);

            [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

            void OnHit(const float damage, const Engine::Math::Vector2& direction);
            void Healing(const float healing) const;
            void BindOnDeath(Event event);

        protected:
            void OnCreateComponent() override;
            void OnSetup() override;
            void DataSetup() override;
            void ComponentSetup();
            void InputSetup();
            void SoundSetup();
            void AnimationSetup() override;

            void OnPreUpdate(float deltaMetaTime, float deltaGameTime) override;
            void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
            void UpdateSuper(float deltaGameTime);
            void UpdateDelay(float deltaGameTime);
            void UpdateSlow(float deltaMetaTime);

            void OnPreFinalize() override;
            void OnPostFinalize() override;

            void ReleaseInput();

            void Dash() const;
            void Die();

            void OpenTimingBar() const;
            void CloseTimingBar() const;
            void Serve() const;

            void Swing() const;
 
            void OnServeSuccess();
            void OnServeFail();
            void OnSwingHit(Engine::Math::Vector2 ballLocation, size_t id);
            void OnSwingSmash(Engine::Math::Vector2 ballLocation, size_t id);
            void Slow();

            void Aim(const Engine::Math::Vector2& direction) const;
            void MouseAim(const Engine::Math::Vector2& mousePosition) const;

            Engine::Math::Vector2 GetServeLocation() const;
            Engine::Math::Vector2 GetBallDirection() const;

        private:
            std::shared_ptr<Component::SwingEffect> _swingAnimation;
            std::shared_ptr<Component::Indicator> _indicator;
            std::shared_ptr<Component::TimingBar> _timingBar;
            std::shared_ptr<Component::Staff> _weapon;
            std::shared_ptr<Engine::Component::FadeBitmap> _ScreenSmashEffect;

            std::unique_ptr<::Audio::ISound> _swingSfx;
            std::unique_ptr<::Audio::ISound> _normalHitSfx;
            std::unique_ptr<::Audio::ISound> _smashHitSfx;
            std::unique_ptr<::Audio::ISound> _dashSfx;
            std::unique_ptr<::Audio::ISound> _onHitSfx;
            std::unique_ptr<::Audio::ISound> _heartBeatSfx;
            std::unique_ptr<::Audio::ISound> _onDeathSfx;

            int _healthRegister;

            Engine::Math::Collision::Manifold _clampManifold;
            bool IsClamped = false;

            float _weaponRange;
            float cos_30;
            float cos_60;
            float _ballSpawnOffset;

            float _superElapsedTime;
            float _superTime;
            bool _isSuper;
            bool _isDashing;
            float _ballDelay;
            float _ballSpawnElapsedTime;
            bool _isDelay;
            bool _isPoisoned;
            float _posionDamage;
            ManaBallPool _ballPool;

            bool _isSlow;
            float _slowRatio;
            float _slowDuration;
            float _slowElapsedTime;

            Event _onDeath;
            bool _isDead;

            bool _useController;
        };
    }
}
