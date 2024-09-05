#include "pch.h"
#include "MainStage.h"
#include "../../Objects/Title/Title.h"
#include "../../Objects/CutScene/CutScene.h"
#include "../../Objects/Ornament/Gate/Gate.h"
#include "../../Objects/KeyInformation/KeyInformation.h"

Client::World::MainStage::MainStage()
    : BackgroundMusic(L"Resources/Sounds/BGM_001.wav")
{
}

void Client::World::MainStage::OnCreateObject()
{
    CreateObject<Object::KeyInformation>();
    Stage::OnCreateObject();
    _title = CreateObject<Object::Title>();
    Load();
}

void Client::World::MainStage::OnSetup()
{
    Stage::OnSetup();
    _title->BindOnDamaged([this]
    {
        _gate->OpenGate();
    });
    Play();
}

void Client::World::MainStage::OnPostFinalize()
{
    Stage::OnPostFinalize();
    Release();
}
