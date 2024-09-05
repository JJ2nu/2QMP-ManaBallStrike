#include "pch.h"
#include "BattleStage.h"
#include "../../Objects/Player/ControlPlayer.h"
#include "../../Objects/Ornament/Gate/Gate.h"
#include "../../Objects/EnemySpawner/Spawner/Spawner.h"
#include "../../Objects/Enemies/Enemies.h"

Client::World::BattleStage::BattleStage()
	: _stageData{}, _wasWaveDone(false), _leftTopWaveDone(false), _rightTopWaveDone(false), _leftBottomWaveDone(false),
	  _rightBottomWaveDone(false)
{
}

void Client::World::BattleStage::OnCreateObject()
{
	Stage::OnCreateObject();
	_leftTop = CreateObject<Object::Spawner>(_stageData.leftTop, Engine::Math::Vector2{-430.f, -400.f},
	                                         false);
	_rightTop = CreateObject<Object::Spawner>(_stageData.rightTop, Engine::Math::Vector2{427.f, -400.f},
	                                          false);
	_leftBottom = CreateObject<Object::Spawner>(_stageData.leftBottom,
	                                            Engine::Math::Vector2{-430.f, 400.f},
	                                            true);
	_rightBottom = CreateObject<Object::Spawner>(_stageData.rightBottom,
	                                             Engine::Math::Vector2{427.f, 400.f},
	                                             true);
	Manager::Data::SetMonsterCount(_stageData.GetTotalMonsterCount());
}

void Client::World::BattleStage::OnSetup()
{
	Stage::OnSetup();
	_leftTop->SetTargetScene(_player->GetRootScene().lock());
	_rightTop->SetTargetScene(_player->GetRootScene().lock());
	_leftBottom->SetTargetScene(_player->GetRootScene().lock());
	_rightBottom->SetTargetScene(_player->GetRootScene().lock());
	if (_boss != nullptr) _boss->SetTargetScene(_player->GetRootScene().lock());

	_leftTop->BindOnWaveEnd([this] { _leftTopWaveDone = true; });
	_rightTop->BindOnWaveEnd([this] { _rightTopWaveDone = true; });
	_leftBottom->BindOnWaveEnd([this] { _leftBottomWaveDone = true; });
	_rightBottom->BindOnWaveEnd([this] { _rightBottomWaveDone = true; });

	_monsterCountRegister = Engine::Manager::Observer<int>::Register(L"MonsterCount", [this](const int value)
	{
		if (value == 0) _gate->OpenGate();
	});
}

void Client::World::BattleStage::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	Stage::OnPostUpdate(deltaMetaTime, deltaGameTime);
	UpdateWave();
}

void Client::World::BattleStage::OnPreFinalize()
{
	Engine::Manager::Observer<int>::RemoveRegister(L"MonsterCount", _monsterCountRegister);
	Stage::OnPreFinalize();
}

void Client::World::BattleStage::UpdateWave() 
{
	if (_leftTopWaveDone && _rightTopWaveDone && _leftBottomWaveDone && _rightBottomWaveDone)
	{
		if (!_leftTop->IsFinished())
		{
			_leftTop->NextWave();
			_leftTopWaveDone = false;
		}
		if (!_rightTop->IsFinished())
		{
			_rightTop->NextWave();
			_rightTopWaveDone = false;
		}
		if (!_leftBottom->IsFinished())
		{
			_leftBottom->NextWave();
			_leftBottomWaveDone = false;
		}
		if (!_rightBottom->IsFinished())
		{
			_rightBottom->NextWave();
			_rightBottomWaveDone = false;
		}
	}
}
