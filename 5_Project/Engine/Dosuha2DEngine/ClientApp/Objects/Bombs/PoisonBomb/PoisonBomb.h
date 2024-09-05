#pragma once
#include "../Base/BombBase.h"

namespace Client::Object
{
	class PoisonBomb : public BombBase
	{
	public:
		PoisonBomb(const Engine::Math::Vector2& location);

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

	private:
		float _damageOnEnemy;
		float _damageOnPlayer;
	};
}
