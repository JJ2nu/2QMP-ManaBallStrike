#include "pch.h"
#include "Stage001.h"
#include "../../Objects/Pilar/PilarBase.h"

Client::World::Stage001::Stage001()
	: BackgroundMusic(L"Resources/Sounds/BGM_002_noroofing.wav"), _changeBgm(false)
{
}

void Client::World::Stage001::OnSetup()
{
	BattleStage::OnSetup();
	Play();
}

void Client::World::Stage001::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
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

void Client::World::Stage001::OnPostFinalize()
{
	BattleStage::OnPostFinalize();
	Release();
}

void Client::World::Stage001::OnCreateObject()
{
	_stageData = Manager::StageLoader::GetStageData(1);
	BattleStage::OnCreateObject();
	Load(false);
}
