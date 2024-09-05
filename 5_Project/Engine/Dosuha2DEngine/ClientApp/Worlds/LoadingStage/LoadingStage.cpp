#include "pch.h"
#include "LoadingStage.h"
#include "Objects/Background/LoadingBackground.h"
#include "Objects/Player/AutoMovePlayer.h"
#include "Objects/Ornament/Torch/Torch.h"

Client::World::LoadingStage::LoadingStage()
    :BackgroundMusic(L"Resources/Sounds/BGM_004.wav"), _requestOpenUI(nullptr), _elapsedTime(0.f), _delay(4.f), _isOpenUI(false)
{
}

void Client::World::LoadingStage::BindRequestOpenUI(const Event& event)
{
    _requestOpenUI = event;
}

void Client::World::LoadingStage::StopLoop() const
{
    _player->LoopStop();
}

void Client::World::LoadingStage::BindOnExit(Event event) const
{
    _player->BindOnExit(std::move(event));
}

void Client::World::LoadingStage::OnCreateObject()
{
    CreateObject<Object::LoadingBackground>(0);
    _player = CreateObject<Object::AutoMovePlayer>(1590);

    const float torchGap = 530.0f;
    const float leftX = -196;
    const float startY = -1600.0f;
    const float endY = 1600.0f;

    int torchCount = 0;

    for (float y = startY; y <= endY; y += torchGap * 2)
    {
        CreateObject<Object::Torch>(Engine::Math::Vector2{ leftX, y });
        CreateObject<Object::Torch>(Engine::Math::Vector2{ -leftX, y });
        torchCount++;
    }

    Load();

}

void Client::World::LoadingStage::OnSetup()
{
    World::OnSetup();
    Play();
}

void Client::World::LoadingStage::OnPostFinalize()
{
    World::OnPostFinalize();
    Release();
}

void Client::World::LoadingStage::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    if (_isOpenUI) return;
    _elapsedTime += deltaGameTime;
    if (_elapsedTime < _delay) return;
    _requestOpenUI();
    _isOpenUI = true;
}
