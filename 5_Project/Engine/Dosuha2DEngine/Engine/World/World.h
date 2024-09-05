#pragma once
#include "../Objects/Base/ObjectBase.h"

namespace Engine
{
    class World : public std::enable_shared_from_this<World>
    {
    public:
        World();
        World(const World& other) = default;
        World(World&& other) noexcept = default;
        World& operator=(const World& other) = default;
        World& operator=(World&& other) noexcept = default;
        virtual ~World() = default;

        void Initialize(Manager::Resource::Loader loader);
        void FixedUpdate(float interval);
        void Update(float deltaMetaTime, float deltaGameTime);
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) const;
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix,
                    const Math::Rect& cullingBound) const;
        void Finalize();

        void AddObject(const std::shared_ptr<Object::Base>& object);

        void AddCollisionable(const std::shared_ptr<Collisionable>& collisionable);

        template <typename T, typename... Args> requires std::derived_from<T, Object::Base>
        std::shared_ptr<T> CreateObject(Args&&... args)
        {
            std::shared_ptr<T> object = std::make_shared<T>(std::forward<Args>(args)...);
            AddObject(object);
            if constexpr (std::derived_from<T, Collisionable>) AddCollisionable(object);
            return object;
        }

    protected:
        virtual void OnCreateObject();
        virtual void OnSetup();

        virtual void OnPreUpdate(float deltaMetaTime, float deltaGameTime);
        virtual void OnPostUpdate(float deltaMetaTime, float deltaGameTime);

        void UpdateObjects(float deltaMetaTime, float deltaGameTime) const;
        void UpdateCollision() const;

        virtual void OnPreFinalize();
        virtual void OnPostFinalize();

    private:
        void CheckDestroyedObject();
        void CheckReleasedCollisionable();

        std::list<std::shared_ptr<Object::Base>> _objects;
        std::list<std::shared_ptr<Collisionable>> _collisionables;

        bool _isFinalized;
    };
}
