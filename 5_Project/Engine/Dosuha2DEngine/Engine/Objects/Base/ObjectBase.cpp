#include "pch.h"
#include "ObjectBase.h"
#include "../../Components/Base/ComponentBase.h"
#include "../../Scene/Scene.h"

void Engine::Object::Base::Initialize(Manager::Resource::Loader loader)
{
    OnCreateComponent();
    std::ranges::for_each(_components, [loader](const std::shared_ptr<Component::Base>& component)
    {
        component->Initialize(loader);
    });
    OnSetup();
}

void Engine::Object::Base::FixedUpdate(float interval)
{
    std::ranges::for_each(_components, [interval](const std::shared_ptr<Component::Base>& component)
    {
        component->FixedUpdate(interval);
    });
}

void Engine::Object::Base::Update(float deltaMetaTime, float deltaGameTime)
{
    OnPreUpdate(deltaMetaTime, deltaGameTime);
    std::ranges::for_each(_components, [deltaMetaTime, deltaGameTime](const std::shared_ptr<Component::Base>& component)
    {
        component->Update(deltaMetaTime, deltaGameTime);
    });
    OnPostUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::Object::Base::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
    std::ranges::for_each(_components, [deltaMetaTime, deltaGameTime](const std::shared_ptr<Component::Base>& component)
    {
        component->LazyUpdate(deltaMetaTime, deltaGameTime);
    });
}

void Engine::Object::Base::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix)
{
    std::ranges::for_each(_components, [renderer, cameraMatrix](const std::shared_ptr<Component::Base>& component)
    {
            if (component->IsRenderable)
            {
                component->Render(renderer, cameraMatrix);
            }
    });
}

void Engine::Object::Base::Finalize()
{
    OnPreFinalize();
    std::ranges::for_each(_components, [](const std::shared_ptr<Component::Base>& component)
    {
        component->Finalize();
    });
    OnPostFinalize();
}


bool Engine::Object::Base::FindTag(const std::wstring_view tagName) const
{
    return std::ranges::any_of(_tags, [tagName](const Tag& tag)
    {
        return tag.GetName() == tagName;
    });
}

std::optional<Engine::Tag> Engine::Object::Base::GetTag(std::wstring_view tagName) const
{
    const auto iter = std::ranges::find_if(_tags, [tagName](const Tag& tag)
    {
        return tag.GetName() == tagName;
    });
    if (iter == _tags.end()) return std::nullopt;
    return *iter;
}

void Engine::Object::Base::Destroy()
{
    _willDestroy = true;
}

bool Engine::Object::Base::GetWaitDestroy() const
{
    return _willDestroy;
}

Engine::Object::Base::Base()
    : _willDestroy(false)
{
}

void Engine::Object::Base::OnCreateComponent()
{
}

void Engine::Object::Base::OnSetup()
{
}

void Engine::Object::Base::OnPreUpdate(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::Object::Base::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::Object::Base::OnPreFinalize()
{
}

void Engine::Object::Base::OnPostFinalize()
{
}

void Engine::Object::Base::AddTag(const Tag& tag)
{
    _tags.insert(tag);
}

void Engine::Object::Base::AddTag(std::wstring_view name)
{
    _tags.emplace(name);
}

void Engine::Object::Base::AddTag(std::wstring_view name, float value)
{
    _tags.emplace(name, value);
}

void Engine::Object::Base::SetOwner(const std::weak_ptr<World>& owner)
{
    _owner = owner;
}

void Engine::Object::Base::SetRootScene(const std::weak_ptr<Scene>& rootScene)
{
    _rootScene = rootScene;
}

Engine::Math::Vector2 Engine::Object::Base::GetLocation() const
{
    return _rootScene.lock()->GetLocation();
}

void Engine::Object::Base::AddComponent(const std::shared_ptr<Component::Base>& component)
{
    component->SetOwner(weak_from_this());
    _components.push_back(component);
}

std::weak_ptr<Engine::Scene> Engine::Object::Base::GetRootScene() const
{
    return _rootScene;
}

std::weak_ptr<Engine::World> Engine::Object::Base::GetOwner() const
{
    return _owner;
}

float Engine::Object::Base::GetRenderOrder() const
{
    return _renderOrder;
}
