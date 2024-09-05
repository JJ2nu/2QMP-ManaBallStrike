#include "pch.h"
#include "TestObject.h"

const Engine::Math::Rect& Client::Object::TestObject::GetBound() const
{
    return _boundComponent->GetBound();
}

void Client::Object::TestObject::OnCreateComponent()
{
    const auto box = CreateComponent<Engine::Component::Shape::Box>(Engine::Math::Vector2{1, 1},
                                                                    D2D1::ColorF(D2D1::ColorF::Red));
    SetRootScene(box);
    _boundComponent = CreateComponent<Engine::Component::Bound>(Engine::Math::Vector2{1, 1});
    _boundComponent->SetParentScene(_rootScene);
    _animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Mummy.png",
                                                                        L"Resources/Animation/Mummy/Mummy.csv");
}

void Client::Object::TestObject::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    if (Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::A)->GetValue())
        _animationComponent->SetMotion(L"Attack");
    if (Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::S)->GetValue())
        _animationComponent->SetMotion(L"Idle");
    if (Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::D)->GetValue())
        _animationComponent->SetMotion(L"Walk");
    if (Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::F)->GetValue())
        _animationComponent->SetMotion(L"Death");
    if (Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::G)->GetValue())
        _animationComponent->SetMotion(L"Hurt");
}
