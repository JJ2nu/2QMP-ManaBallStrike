#include "pch.h"
#include "CutSceneStage.h"
#include "../../Objects/Title/Title.h"
#include "../../Objects/CutScene/CutScene.h"
#include "../../Objects/Ornament/Gate/Gate.h"
#include "../../Objects/KeyInformation/KeyInformation.h"
#include "../../Objects/Background/EndingBackground.h"
#include "../../Objects/EndingCreditScroller/EndingCreditScroller.h"



void Client::World::CutSceneStage1::OnCreateObject()
{
	Engine::Manager::Render::GetShader()->SetBackground(nullptr);

	_cutScene1 = CreateObject<Object::CutScene>(1, L"Resources/Sprites/CutScene/scene_002.png", false);
	_cutScene2 = CreateObject<Object::CutScene>(2, L"Resources/Sprites/CutScene/scene_003.png", false);
	_cutScene3 = CreateObject<Object::CutScene>(3, L"Resources/Sprites/CutScene/scene_004.png", false);
	_cutScene4 = CreateObject<Object::CutScene>(4, L"Resources/Sprites/CutScene/scene_005.png", true);
	Load();
}

void Client::World::CutSceneStage1::OnPostUpdate(float d1, float d2)
{
	_cutScene1->SetRender(false);
	_cutScene2->SetRender(false);
	_cutScene3->SetRender(false);
	_cutScene4->SetRender(false);

	if (_cutSceneIdx == 0)
		_cutScene1->SetRender(true);
	if (_cutSceneIdx == 1)
		_cutScene2->SetRender(true);
	if (_cutSceneIdx == 2)
		_cutScene3->SetRender(true);
	if (_cutSceneIdx == 3)
		_cutScene4->SetRender(true);



}

void Client::World::CutSceneStage1::OnSetup()
{
	const auto sceneMotion = Engine::Manager::Input::CreateMappingContext(L"CutScene")->GetAction(L"CutScene");
	sceneMotion->AddListener(Input::TriggerState::Started, [this](const Input::Value& value) {
		if (_cutSceneIdx < 4)
			_cutSceneIdx++;
		else
			_onStageClear();
		});
	if(_requestOpenUI!=nullptr) _requestOpenUI();
	Play();
}
void Client::World::CutSceneStage1::OnPreFinalize()
{
	Engine::Manager::Input::CreateMappingContext(L"CutScene")->GetAction(L"CutScene")->ClearListener();
}


Client::World::CutSceneStage1::CutSceneStage1()
	: BackgroundMusic(L"Resources/Sounds/BGM_004.wav")
{
}

void Client::World::CutSceneStage1::OnPostFinalize()
{
	World::OnPostFinalize();
	Release();
}

void Client::World::CutSceneStage1::BindRequestOpenUI(const Event& event)
{
	_requestOpenUI = event;
}

void Client::World::CutSceneStage1::BindOnStageClear(Event event)
{
	_onStageClear = std::move(event);

}



//===============================================================================================================================




void Client::World::CutSceneStage2::OnCreateObject()
{
	Engine::Manager::Render::GetShader()->SetBackground(nullptr);
	_cutScene1 = CreateObject<Object::CutScene>(0, L"Resources/Sprites/CutScene/scene_019.png", false);
	_cutScene2 = CreateObject<Object::CutScene>(1, L"Resources/Sprites/CutScene/scene_020.png", false);
	_cutScene3 = CreateObject<Object::CutScene>(2, L"Resources/Sprites/CutScene/scene_021.png", false);
	_cutScene4 = CreateObject<Object::CutScene>(3, L"Resources/Sprites/CutScene/scene_022.png", false);
	_cutScene5 = CreateObject<Object::CutScene>(4, L"Resources/Sprites/CutScene/scene_023.png", false);
	_cutScene6 = CreateObject<Object::CutScene>(5, L"Resources/Sprites/CutScene/scene_024.png", true);
	Load();
}

void Client::World::CutSceneStage2::OnPostUpdate(float d1, float d2)
{
	_cutScene1->SetRender(false);
	_cutScene2->SetRender(false);
	_cutScene3->SetRender(false);
	_cutScene4->SetRender(false);
	_cutScene5->SetRender(false);
	_cutScene6->SetRender(false);

	if (_cutSceneIdx == 0)
		_cutScene1->SetRender(true);
	if (_cutSceneIdx == 1)
		_cutScene2->SetRender(true);
	if (_cutSceneIdx == 2)
		_cutScene3->SetRender(true);
	if (_cutSceneIdx == 3)
		_cutScene4->SetRender(true);
	if (_cutSceneIdx == 4)
		_cutScene5->SetRender(true);
	if (_cutSceneIdx == 5)
		_cutScene6->SetRender(true);

}

void Client::World::CutSceneStage2::OnSetup()
{
	const auto sceneMotion = Engine::Manager::Input::CreateMappingContext(L"CutScene")->GetAction(L"CutScene");
	sceneMotion->AddListener(Input::TriggerState::Started, [this](const Input::Value& value) {
		if (_cutSceneIdx < 6)
			_cutSceneIdx++;
		else
			_onStageClear();

		});
	if (_requestOpenUI != nullptr) _requestOpenUI();
	Play();
}

Client::World::CutSceneStage2::CutSceneStage2()
	: BackgroundMusic(L"Resources/Sounds/BGM_005.wav")
{
}

void Client::World::CutSceneStage2::OnPostFinalize()
{
	World::OnPostFinalize();
	Release();
}

void Client::World::CutSceneStage2::BindRequestOpenUI(const Event& event)
{
	_requestOpenUI = event;

}

void Client::World::CutSceneStage2::BindOnStageClear(Event event)
{
	_onStageClear = std::move(event);

}

void Client::World::CutSceneStage2::OnPreFinalize()
{
	Engine::Manager::Input::CreateMappingContext(L"CutScene")->GetAction(L"CutScene")->ClearListener();

}

//========================================================================================================

Client::World::EndingCredit::EndingCredit()
	: BackgroundMusic(L"Resources/Sounds/BGM_005.wav")
{
}

void Client::World::EndingCredit::OnPostFinalize()
{
	World::OnPostFinalize();
	Release();
}

void Client::World::EndingCredit::BindRequestOpenUI(const Event& event)
{
}

void Client::World::EndingCredit::BindOnStageClear(Event event)
{
}

void Client::World::EndingCredit::OnCreateObject()
{
	_background = CreateObject<Client::Object::EndingBackground>();
	_endingCredit = CreateObject<Client::Object::EndingCreditScroller>();
	Load();
}

void Client::World::EndingCredit::OnPostUpdate(float d1, float d2)
{
}

void Client::World::EndingCredit::OnSetup()
{
	Play();
}
