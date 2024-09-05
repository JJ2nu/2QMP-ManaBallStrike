#include "pch.h"
#include "System.h"

#include "Canvas/Main/MainCanvas.h"
#include "../Worlds/Worlds.h"

Client::System::System()
	: Engine::System(L"Client", {1600, 900})
{
	_mainCanvas = std::make_shared<Canvas::Main>(Engine::Math::Vector2{1600, 900});
	CreateStages();
	_world = _mainStage;
	_canvas = _mainCanvas;
	_deathLogic = [this]
	{
		_mainCanvas->ShowGameOver();
	};
}

void Client::System::BindDeathThisStage() const
{
	_mainStage->BindPlayerDeath(_deathLogic);
}

void Client::System::CreateStages()
{
	_mainStage = std::make_shared<World::MainStage>();
	_stage001 = std::make_shared<World::Stage001>();
	_stage002 = std::make_shared<World::Stage002>();
	_stage003 = std::make_shared<World::Stage003>();
	_stage004 = std::make_shared<World::Stage004>();
	_cutScene1 = std::make_shared<World::CutSceneStage1>();
	_cutScene2 = std::make_shared<World::CutSceneStage2>();
	_EndingCredit = std::make_shared<World::EndingCredit>();

	_mainStage->BindOnStageClear([this]
	{
		_mainCanvas->BindOnFadeInEnd([this]
		{
			_mainCanvas->HideHUD();

			_world->Finalize();

			Engine::Manager::Input::SetMappingContext(cutSceneContext);
			Manager::Data::ResetHealthPoint();
			Manager::Data::ResetManaBallCount();
			const auto CutScene = std::make_shared<World::CutSceneStage1>();
			_world = CutScene;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
			CutScene->BindRequestOpenUI([this]
			{
				_mainCanvas->HideUpgrade();
				_mainCanvas->HideSettings();
				_mainCanvas->HideHUD();
			});
			CutScene->BindOnStageClear([this]
			{
				Engine::Manager::Input::SetMappingContext(playerContext);
				_mainCanvas->BindOnFadeInEnd([this]
				{
					//Engine::Manager::Input::CreateMappingContext(L"CutScene")->GetAction(L"CutScene")->ClearListener();
					_world->Finalize();
					_world = _stage001;
					Engine::Manager::Observer<int>::ClearRegisters(L"MonsterCount");
					Manager::Data::ResetHealthPoint();
					Manager::Data::ResetManaBallCount();
					_world->Initialize(Engine::Manager::Resource::GetLoader());
					_stage001->BindPlayerDeath(_deathLogic);
					_mainCanvas->FadeOut();
					_mainCanvas->ShowHUD();
				});
				_mainCanvas->FadeIn();
			});

			_mainCanvas->FadeOut();
		});
		_mainCanvas->FadeIn();
	});
	_stage001->BindOnStageClear([this]
	{
		_mainCanvas->BindOnFadeInEnd([this]
		{
			_world->Finalize();
			Manager::Data::ResetHealthPoint();
			Manager::Data::ResetManaBallCount();
			const auto loading = std::make_shared<World::LoadingStage>();
			_world = loading;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
			loading->BindOnExit([this]
			{
				_mainCanvas->BindOnFadeInEnd([this]
				{
					_world->Finalize();
					Engine::Manager::Input::SetMappingContext(playerContext);
					Engine::Manager::Observer<int>::ClearRegisters(L"MonsterCount");
					Manager::Data::ResetHealthPoint();
					Manager::Data::ResetManaBallCount();
					_world = _stage002;
					_world->Initialize(Engine::Manager::Resource::GetLoader());
					_stage002->BindPlayerDeath(_deathLogic);

					_mainCanvas->FadeOut();
				});
				_mainCanvas->FadeIn();
			});
			loading->BindRequestOpenUI([this]
			{
				_mainCanvas->ResetUpgrade();
				_mainCanvas->ShowUpgrade();
				_mainCanvas->HideHUD();
			});
			_mainCanvas->BindOnUpgradeComplete([loading]
			{
				loading->StopLoop();
			});
			_mainCanvas->FadeOut();
		});
		_mainCanvas->FadeIn();
	});
	_stage002->BindOnStageClear([this]
	{
		_mainCanvas->BindOnFadeInEnd([this]
		{
			_world->Finalize();
			Manager::Data::ResetHealthPoint();
			Manager::Data::ResetManaBallCount();
			const auto loading = std::make_shared<World::LoadingStage>();
			_world = loading;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
			loading->BindOnExit([this]
			{
			});

			loading->BindOnExit([this]
			{
				_mainCanvas->BindOnFadeInEnd([this]
				{
					_world->Finalize();
					Engine::Manager::Input::SetMappingContext(playerContext);
					Engine::Manager::Observer<int>::ClearRegisters(L"MonsterCount");
					Manager::Data::ResetHealthPoint();
					Manager::Data::ResetManaBallCount();
					_world = _stage003;
					_world->Initialize(Engine::Manager::Resource::GetLoader());
					_stage003->BindPlayerDeath(_deathLogic);

					_mainCanvas->FadeOut();
				});
				_mainCanvas->FadeIn();
			});
			loading->BindRequestOpenUI([this]
			{
				_mainCanvas->ResetUpgrade();
				_mainCanvas->ShowUpgrade();
				_mainCanvas->HideHUD();
			});
			_mainCanvas->BindOnUpgradeComplete([loading]
			{
				loading->StopLoop();
			});
			_mainCanvas->FadeOut();
		});
		_mainCanvas->FadeIn();
	});
	_stage003->BindOnStageClear([this]
	{
		_mainCanvas->BindOnFadeInEnd([this]
		{
			_world->Finalize();
			Manager::Data::ResetHealthPoint();
			Manager::Data::ResetManaBallCount();
			const auto loading = std::make_shared<World::LoadingStage>();
			_world = loading;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
			loading->BindOnExit([this]
			{
			});

			loading->BindOnExit([this]
			{
				_mainCanvas->BindOnFadeInEnd([this]
				{
					_world->Finalize();
					Engine::Manager::Input::SetMappingContext(playerContext);
					Engine::Manager::Observer<int>::ClearRegisters(L"MonsterCount");
					Manager::Data::ResetHealthPoint();
					Manager::Data::ResetManaBallCount();
					_world = _stage004;
					_world->Initialize(Engine::Manager::Resource::GetLoader());
					_stage004->BindPlayerDeath(_deathLogic);
					_mainCanvas->FadeOut();
				});
				_mainCanvas->FadeIn();
			});
			loading->BindRequestOpenUI([this]
			{
				_mainCanvas->ResetUpgrade();
				_mainCanvas->ShowUpgrade();
				_mainCanvas->HideHUD();
			});
			_mainCanvas->BindOnUpgradeComplete([loading]
			{
				loading->StopLoop();
			});
			_mainCanvas->FadeOut();
		});
		_mainCanvas->FadeIn();
	});
	_stage004->BindOnStageClear([this]
	{
		_mainCanvas->BindOnFadeInEnd([this]
		{
			_mainCanvas->HideHUD();

			_world->Finalize();
			Engine::Manager::Input::SetMappingContext(cutSceneContext);

			Manager::Data::ResetHealthPoint();
			Manager::Data::ResetManaBallCount();
			const auto CutScene = std::make_shared<World::CutSceneStage2>();

			_world = CutScene;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
			CutScene->BindRequestOpenUI([this]
			{
				_mainCanvas->HideUpgrade();
				_mainCanvas->HideSettings();
				_mainCanvas->HideHUD();
			});
			CutScene->BindOnStageClear([this]
			{
				_mainCanvas->BindOnFadeInEnd([this]
				{
					_world->Finalize();
					Engine::Manager::Input::SetMappingContext(playerContext);
					_world = _EndingCredit;
					Engine::Manager::Observer<int>::ClearRegisters(L"MonsterCount");
					_world->Initialize(Engine::Manager::Resource::GetLoader());
					_mainCanvas->FadeOut();
					_mainCanvas->HideHUD();
				});
				_mainCanvas->FadeIn();
			});

			_mainCanvas->FadeOut();
		});
		_mainCanvas->FadeIn();
	});
}

void Client::System::OnPreInitialize()
{
	Manager::Config::Initialize(L"Config.ini");
	Manager::StageLoader::Initialize();
	Manager::Data::Initialize();
	DeclareInput();
}

void Client::System::OnPostInitialize()
{
	_mainCanvas->BindOnQuit([this] { _isRun = false; });
	_mainCanvas->BindOnRestart([this]
	{
		_mainCanvas->BindOnFadeInEnd([this]
		{
			_world->Finalize();
			CreateStages();
			_world = _mainStage;
			Manager::Data::Reset();
			_world->Initialize(Engine::Manager::Resource::GetLoader());
			_mainCanvas->HideSettings();
			_mainCanvas->HideGameOver();
			_mainCanvas->FadeOut();
		});
		_mainCanvas->FadeIn();
	});
	KeyInitialize();
}

void Client::System::KeyInitialize()
{
	Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Main")->AddListener(
		Input::TriggerState::Triggered, [this](const Input::Value& value)
		{
			_world->Finalize();
			CreateStages();
			_world = _mainStage;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
		});

	Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Stage1")->AddListener(
		Input::TriggerState::Triggered, [this](const Input::Value& value)
		{
			_world->Finalize();
			CreateStages();
			_world = _stage001;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
		});

	Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Stage2")->AddListener(
		Input::TriggerState::Triggered, [this](const Input::Value& value)
		{
			_world->Finalize();
			CreateStages();
			_world = _stage002;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
		});

	Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Stage3")->AddListener(
		Input::TriggerState::Triggered, [this](const Input::Value& value)
		{
			_world->Finalize();
			CreateStages();
			_world = _stage003;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
		});

	Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Stage4")->AddListener(
		Input::TriggerState::Triggered, [this](const Input::Value& value)
		{
			_world->Finalize();
			CreateStages();
			_world = _stage004;
			_world->Initialize(Engine::Manager::Resource::GetLoader());
		});
}


void Client::System::DeclareInput()
{
	playerContext = Engine::Manager::Input::CreateMappingContext(L"Player");

	const auto moveAction = playerContext->CreateAction(L"Move");
	moveAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis, Input::Modifier::Negative>
		(Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::W));
	moveAction->BindKey<Input::Trigger::Down, Input::Modifier::Negative>
		(Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::A));
	moveAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis>
		(Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::S));
	moveAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::D));
	moveAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Thumb::LeftX));
	moveAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis, Input::Modifier::Negative>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Thumb::LeftY));
	moveAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis, Input::Modifier::Negative>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::DpadUp));
	moveAction->BindKey<Input::Trigger::Down, Input::Modifier::Negative>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::DpadLeft));
	moveAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::DpadDown));
	moveAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::DpadRight));

	const auto timingBarAction = playerContext->CreateAction(L"TimingBar");
	timingBarAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Button::Right));
	timingBarAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Trigger::Left));

	const auto serveAction = playerContext->CreateAction(L"Serve");
	serveAction->BindKey<Input::Trigger::ChordAction>
		(timingBarAction, Engine::Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Button::Left));
	serveAction->BindKey<Input::Trigger::ChordAction>
	(timingBarAction,
	 Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::RightShoulder));
	serveAction->BindKey<Input::Trigger::ChordAction>
		(timingBarAction, Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::Y));
	serveAction->BindKey<Input::Trigger::ChordAction>
		(timingBarAction, Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::X));
	serveAction->BindKey<Input::Trigger::ChordAction>
		(timingBarAction, Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::A));
	serveAction->BindKey<Input::Trigger::ChordAction>
		(timingBarAction, Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::B));

	const auto dashAction = playerContext->CreateAction(L"Dash");
	dashAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::Space));
	dashAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::LeftThumb));
	dashAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::RightThumb));
	dashAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::LeftShoulder));

	const auto settingAction = playerContext->CreateAction(L"Settings");
	settingAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::Escape));
	settingAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::Start));
	settingAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::Back));

	const auto controllerAimAction = playerContext->CreateAction(L"ControllerAim");
	controllerAimAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Thumb::RightX));
	controllerAimAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis, Input::Modifier::Negative>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Thumb::RightY));
	controllerAimAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis, Input::Modifier::Negative>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::Y));
	controllerAimAction->BindKey<Input::Trigger::Down, Input::Modifier::Negative>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::X));
	controllerAimAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::A));
	controllerAimAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::B));

	const auto mouseAimAction = playerContext->CreateAction(L"MouseAim");
	mouseAimAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Axis::X));
	mouseAimAction->BindKey<Input::Trigger::Down, Input::Modifier::SwizzleAxis>
		(Engine::Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Axis::Y));
	
	const auto switchingAction = playerContext->CreateAction(L"Switching");
	switchingAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Button::Middle));

	const auto swingAction = playerContext->CreateAction(L"Swing");
	swingAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Button::Left));
	swingAction->BindKey<Input::Trigger::Down>
		(Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::RightShoulder));
	swingAction->BindKey<Input::Trigger::ChordAction>
	(controllerAimAction,
	 Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::Y));
	swingAction->BindKey<Input::Trigger::ChordAction>
	(controllerAimAction,
	 Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::X));
	swingAction->BindKey<Input::Trigger::ChordAction>
	(controllerAimAction,
	 Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::A));
	swingAction->BindKey<Input::Trigger::ChordAction>
	(controllerAimAction,
	 Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::B));

	playerContext->CreateAction(L"Main")->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::F1));
	playerContext->CreateAction(L"Stage1")->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::F2));
	playerContext->CreateAction(L"Stage2")->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::F3));
	playerContext->CreateAction(L"Stage3")->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::F4));
	playerContext->CreateAction(L"Stage4")->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::F5));
	playerContext->CreateAction(L"OpenGate")->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::F6));


	cutSceneContext = Engine::Manager::Input::CreateMappingContext(L"CutScene");
	const auto cutsceneAction = cutSceneContext->CreateAction(L"CutScene");
	cutsceneAction->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Button::Left));
	cutsceneAction->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetKeyboard().GetComponent(Input::Device::IKeyboard::Key::Space));
	cutsceneAction->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::RightShoulder));
	cutsceneAction->BindKey<Input::Trigger::Down>(
		Engine::Manager::Input::GetController().GetComponent(Input::Device::IController::Button::A));

	Engine::Manager::Input::SetMappingContext(playerContext);
}
