#pragma once
#include "../Base/EnemyBase.h"

namespace Client::Object
{
	class EnemyType001 : public EnemyBase
	{
	public:
		EnemyType001(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene);

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
		void OnPostFinalize()override;
		void TakeDamage(float Damage) override;


	private:
		std::unique_ptr<::Audio::ISound> _onEnemy1HitSfx;
	};
}
