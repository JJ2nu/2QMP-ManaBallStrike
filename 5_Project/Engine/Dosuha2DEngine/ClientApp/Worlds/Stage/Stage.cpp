#include "pch.h"
#include "Stage.h"
#include "../../Objects/Player/ControlPlayer.h"
#include "../../Objects/Background/Background.h"
#include "../../Objects/Walls/Walls.h"
#include "../../Objects/Ornament/Torch/Torch.h"
#include "../../Objects/Ornament/Gate/Gate.h"

void Client::World::Stage::OnCreateObject()
{
	_background = CreateObject<Object::Background>();
	_gate = CreateObject<Object::Gate>(Engine::Math::Vector2{ 0, -425 });
	CreateObject<Object::Torch>(Engine::Math::Vector2{ -300, -460 });
	CreateObject<Object::Torch>(Engine::Math::Vector2{ 300, -460 });
	_player = CreateObject<Object::ControlPlayer>(300);
	CreateObject<Object::LeftWall>();
	CreateObject<Object::TopWall>();
	CreateObject<Object::RightWall>();
	CreateObject<Object::BottomWall>();
}

void Client::World::Stage::OnSetup()
{
	
	_gate->BindOnExit([this]
		{
			if (_onStageClear != nullptr) _onStageClear();
		});

}

void Client::World::Stage::BindOnStageClear(Event event)
{
	_onStageClear = std::move(event);
}

void Client::World::Stage::BindPlayerDeath(Event event) const
{
	_player->BindOnDeath(std::move(event));
}
