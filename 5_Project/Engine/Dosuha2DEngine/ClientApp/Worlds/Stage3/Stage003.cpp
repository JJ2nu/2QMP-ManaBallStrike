#include "pch.h"
#include "Stage003.h"
#include "../../Objects/Pilar/PilarBase.h"
#include "../../Objects/Bombs/Bombs.h"

Client::World::Stage003::Stage003()
	: BackgroundMusic(L"Resources/Sounds/BGM_003.wav")
{
}

void Client::World::Stage003::OnSetup()
{
	BattleStage::OnSetup();
	Play();
}

void Client::World::Stage003::OnPostFinalize()
{
	BattleStage::OnPostFinalize();
	Release();
}

void Client::World::Stage003::OnCreateObject()
{
	_stageData = Manager::StageLoader::GetStageData(3);
    BattleStage::OnCreateObject();
    CreateObject<Object::RightTopCornerPilarVertical>(Engine::Math::Vector2{400, -100});
    CreateObject<Object::RightTopCornerPilarHorizontal>(Engine::Math::Vector2{400, -100});
    CreateObject<Object::LeftTopCornerPilarVertical>(Engine::Math::Vector2{-400, -100});
    CreateObject<Object::LeftTopCornerPilarHorizontal>(Engine::Math::Vector2{-400, -100});
    CreateObject<Object::PointPilar>(Engine::Math::Vector2{0, 50});
    CreateObject<Object::LeftBottomCornerPilar>(Engine::Math::Vector2(-400, 300));
    CreateObject<Object::RightBottomCornerPilar>(Engine::Math::Vector2(400, 300));
    CreateObject<Object::NormalBomb>(Engine::Math::Vector2{ 550, -250 });
    CreateObject<Object::PoisonBomb>(Engine::Math::Vector2{ -550, 250 });
	Load();
}
