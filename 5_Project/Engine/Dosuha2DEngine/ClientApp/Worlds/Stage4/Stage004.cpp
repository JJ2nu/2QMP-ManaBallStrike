#include "pch.h"
#include "Stage004.h"
#include "../../Objects/Enemies/Boss/Boss.h"
#include "../../Objects/Background/BossBackground.h"

Client::World::Stage004::Stage004()
	: BackgroundMusic(L"Resources/Sounds/BGM_003.wav")
{
}

void Client::World::Stage004::OnPostFinalize()
{
	BattleStage::OnPostFinalize();
	Release();
}

void Client::World::Stage004::OnCreateObject()
{
	_stageData = Manager::StageLoader::GetStageData(4);
	BattleStage::OnCreateObject();
	_background = CreateObject<Object::BossBackground>();
	_boss = CreateObject<Object::Boss>(Engine::Math::Vector2{0, -100});
	Load();
}

void Client::World::Stage004::OnSetup()
{
	BattleStage::OnSetup();
	Play();
}
