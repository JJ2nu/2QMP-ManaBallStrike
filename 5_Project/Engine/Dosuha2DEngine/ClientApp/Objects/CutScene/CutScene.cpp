#include "pch.h"
#include "CutScene.h"

Client::Object::CutScene::CutScene(size_t idx, std::wstring path, bool isLastCut)
{
	_idx = idx;
	_path = path;
    _isLastCut = isLastCut;
}

const Engine::Math::Rect& Client::Object::CutScene::GetBound() const
{
	return _boundComponent->GetBound();
}

void Client::Object::CutScene::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _bitmapComponent = CreateComponent<Engine::Component::FadeBitmap>(_path);
    _bitmapComponent->SetParentScene(_rootScene);
}

void Client::Object::CutScene::OnSetup()
{
    _rootScene.lock()->SetLocation({ 0,-80 });
    _rootScene.lock()->SetScale({ 0.83f,0.83f });
    _boundComponent->SetSize({ 100,100 });
    _bitmapComponent->IsRenderable = false;
}
void Client::Object::CutScene::FadeIn()
{
    _bitmapComponent->FadeIn();
}

void Client::Object::CutScene::FadeOut()
{
    _bitmapComponent->FadeOut();
}

