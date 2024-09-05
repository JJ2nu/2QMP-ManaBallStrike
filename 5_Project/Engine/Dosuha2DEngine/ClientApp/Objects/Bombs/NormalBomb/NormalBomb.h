#pragma once
#include "../Base/BombBase.h"

namespace Client::Object
{
	class NormalBomb : public BombBase
	{
	public:
		NormalBomb(const Engine::Math::Vector2& location);

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

	private:
		float _damageOnPlayer;
		float _damageOnEnemy;
	};
}
