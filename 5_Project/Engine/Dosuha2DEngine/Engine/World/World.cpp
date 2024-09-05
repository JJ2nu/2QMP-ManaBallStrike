#include "pch.h"
#include "World.h"

Engine::World::World()
    : _isFinalized(false)
{
}

void Engine::World::Initialize(Manager::Resource::Loader loader)
{
    OnCreateObject();
    std::ranges::for_each(_objects, [loader](const std::shared_ptr<Object::Base>& object)
    {
        object->Initialize(loader);
    });
    OnSetup();
}

void Engine::World::Update(const float deltaMetaTime, const float deltaGameTime)
{
    CheckDestroyedObject();
    CheckReleasedCollisionable();
    UpdateCollision();
    if (_isFinalized) return;
    OnPreUpdate(deltaMetaTime, deltaGameTime);
    UpdateObjects(deltaMetaTime, deltaGameTime);
    OnPostUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::World::FixedUpdate(float interval)
{
    std::ranges::for_each(_objects, [interval](const std::shared_ptr<Object::Base>& object)
    {
        object->FixedUpdate(interval);
    });
}

void Engine::World::LazyUpdate(float deltaMetaTime, float deltaGameTime) const
{
    std::ranges::for_each(_objects, [deltaMetaTime, deltaGameTime](const std::shared_ptr<Object::Base>& object)
    {
        object->LazyUpdate(deltaMetaTime, deltaGameTime);
    });
}

void Engine::World::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix,
                           const Math::Rect& cullingBound) const
{
    std::vector<std::shared_ptr<Object::Base>> _renderObjects{std::begin(_objects), std::end(_objects)};
    std::sort(_renderObjects.begin(), _renderObjects.end(),
              [](std::shared_ptr<Object::Base> o1, std::shared_ptr<Object::Base> o2)-> bool
              {
                  return o1.get()->GetRenderOrder() < o2.get()->GetRenderOrder();
              });

    std::ranges::for_each(_renderObjects,
                          [renderer, cameraMatrix, cullingBound](const std::shared_ptr<Object::Base>& object)
                          {
                              if (Math::Collision::AABB()(cullingBound, object->GetBound())) object->Render(
                                  renderer, cameraMatrix);
                          });
}

void Engine::World::Finalize() 
{
    OnPreFinalize();
    std::ranges::for_each(_objects, [](const std::shared_ptr<Object::Base>& object) { object->Finalize(); });
    _isFinalized = true;
    OnPostFinalize();
}

void Engine::World::AddObject(const std::shared_ptr<Object::Base>& object)
{
    object->SetOwner(weak_from_this());
    _objects.push_back(object);
}

void Engine::World::AddCollisionable(const std::shared_ptr<Collisionable>& collisionable)
{
    _collisionables.push_back(collisionable);
}

void Engine::World::OnCreateObject()
{
}

void Engine::World::OnSetup()
{
}

void Engine::World::OnPreUpdate(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::World::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::World::UpdateObjects(float deltaMetaTime, float deltaGameTime) const
{
    std::ranges::for_each(_objects, [deltaMetaTime, deltaGameTime](const std::shared_ptr<Object::Base>& object)
    {
        object->Update(deltaMetaTime, deltaGameTime);
    });
}

void Engine::World::UpdateCollision() const
{
    std::vector<std::shared_ptr<Component::Collider::Base>> colliders;
    for (const auto collisionable : _collisionables)
    {
        auto tempColliders = collisionable->GetColliders();
        std::ranges::for_each(tempColliders, [](const std::shared_ptr<Component::Collider::Base>& collider)
        {
            collider->Reset();
        });
        colliders.reserve(colliders.size() + tempColliders.size());
        std::ranges::move(tempColliders, std::back_inserter(colliders));
    }

    for (auto lhsIter = colliders.begin(); lhsIter != colliders.end(); ++lhsIter)
    {
        for (auto rhsIter = std::next(lhsIter); rhsIter != colliders.end(); ++rhsIter)
        {
            const auto source = *lhsIter;
            const auto target = *rhsIter;
            if (source->GetOwner().lock() == target->GetOwner().lock()) continue;
            if (source->GetType() == Component::Collider::Base::Type::NoCollision || target->GetType() ==
                Component::Collider::Base::Type::NoCollision)
                continue;
            Math::Collision::Manifold manifold = {};
            if (!std::visit([&manifold](auto&& sourceShape, auto&& targetShape)
            { return Math::Collision::Collision()(sourceShape, targetShape, &manifold);
				}, source->GetShape(), target->GetShape()))
				continue;
			if (source->GetType() == Component::Collider::Base::Type::Block &&
                target->GetType() == Component::Collider::Base::Type::Block)
            {
                source->InsertBlockState(target, manifold);
                target->InsertBlockState(source, manifold);
            }
            else
            {
                source->InsertOverlapState(target, manifold);
                target->InsertOverlapState(source, manifold);
            }
        }
    }

    for (const auto& base : colliders)
    {
        base->ProcessBlock();
        base->ProcessOverlap();
    }
}

void Engine::World::OnPreFinalize()
{
}

void Engine::World::OnPostFinalize()
{
}

void Engine::World::CheckDestroyedObject()
{
    std::erase_if(_objects, [](const std::shared_ptr<Object::Base>& object)
    {
        if (object->GetWaitDestroy())
        {
            object->Finalize();
            return true;
        }
        return false;
    });
}

void Engine::World::CheckReleasedCollisionable()
{
    std::erase_if(_collisionables, [](const std::shared_ptr<Collisionable>& collisionable)
    {
        if (collisionable->GetWillRelease())
        {
            collisionable->Release();
            return true;
        }
        return false;
    });
}
