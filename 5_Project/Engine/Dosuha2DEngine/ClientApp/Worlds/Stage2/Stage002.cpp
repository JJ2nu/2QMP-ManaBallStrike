#include "pch.h"
#include "Stage002.h"

#include "../../Objects/Pilar/PilarBase.h"
#include "../../Objects/Bombs/Bombs.h"

Client::World::Stage002::Stage002()
	: BackgroundMusic(L"Resources/Sounds/BGM_002_noroofing.wav"), _changeBgm(false)
{
}

void Client::World::Stage002::OnSetup()
{
	BattleStage::OnSetup();
	Play();
}

void Client::World::Stage002::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	BattleStage::OnPostUpdate(deltaMetaTime, deltaGameTime);
	if (!IsPlaying() && !_changeBgm)
	{
		Release();
		Load(std::filesystem::path(L"Resources/Sounds/BGM_002_roofing.wav"));
		Play();
		_changeBgm = true;
	}
}

void Client::World::Stage002::OnPostFinalize()
{
	BattleStage::OnPostFinalize();
	Release();
}

void Client::World::Stage002::OnCreateObject()
{
	_stageData = Manager::StageLoader::GetStageData(2);
	BattleStage::OnCreateObject();
	CreateObject<Object::PointPilar>(Engine::Math::Vector2{-200, 0});
	CreateObject<Object::PointPilar>(Engine::Math::Vector2{200, 0});
	CreateObject<Object::NormalBomb>(Engine::Math::Vector2{ 400, -250 });
	CreateObject<Object::PoisonBomb>(Engine::Math::Vector2{ -400, 250 });;
	Load(false);
}
