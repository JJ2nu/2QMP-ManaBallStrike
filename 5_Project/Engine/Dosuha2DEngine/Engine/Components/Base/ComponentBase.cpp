#include "pch.h"
#include "ComponentBase.h"

Engine::Component::Base::Base()
{
}

void Engine::Component::Base::Initialize(Manager::Resource::Loader loader)
{
}

void Engine::Component::Base::FixedUpdate(float interval)
{
}

void Engine::Component::Base::Update(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::Component::Base::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::Component::Base::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
}

void Engine::Component::Base::Finalize()
{
}

void Engine::Component::Base::SetOwner(const std::weak_ptr<Object::Base>& owner)
{
    _owner = owner;
}

std::weak_ptr<Engine::Object::Base> Engine::Component::Base::GetOwner() const
{
    return _owner;
}
