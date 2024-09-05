#pragma once

namespace Engine
{
    class Collisionable;

    namespace Component::Collider
    {
        class Base : public Component::Base
        {
        public:
            enum class Type;
            using ColliderShape = std::variant<Math::Rect, Math::Circle, Math::RoundRect>;
            using Event = std::function<void(std::weak_ptr<Base>, Math::Collision::Manifold)>;

            explicit Base(Type type);

            [[nodiscard]] virtual ColliderShape GetShape() = 0;
            [[nodiscard]] virtual Math::Vector2 GetShapeCenter() = 0;
            [[nodiscard]] Type GetType() const;

            void Activate();
            void Deactivate();
            [[nodiscard]] bool IsActivated() const;

            void Reset();

            void InsertBlockState(std::shared_ptr<Base> other, const Math::Collision::Manifold& manifold);
            void ProcessBlock() const;

            void InsertOverlapState(std::shared_ptr<Base> other, const Math::Collision::Manifold& manifold);
            void ProcessOverlap() const;

            void BindOnBeginBlock(Event onBeginBlock);
            void BindOnBlock(Event OnBlock);
            void BindOnEndBlock(Event onEndBlock);
            void BindOnBeginOverlap(Event onBeginOverlap);
            void BindOnEndOverlap(Event onEndOverlap);

        protected:
            Type _type;

            bool _isActivated;

            Event _onBeginBlock;
            Event _onBlock;
            Event _onEndBlock;
            Event _onBeginOverlap;
            Event _onEndOverlap;

            std::map<std::shared_ptr<Base>, Math::Collision::Manifold> _currentOverlapState;
            std::map<std::shared_ptr<Base>, Math::Collision::Manifold> _previousOverlapState;
            std::map<std::shared_ptr<Base>, Math::Collision::Manifold> _currentBlockState;
            std::map<std::shared_ptr<Base>, Math::Collision::Manifold> _previousBlockState;

        public:
            enum class Type
            {
                NoCollision,
                Block,
                Overlap
            };
        };
    }
}
