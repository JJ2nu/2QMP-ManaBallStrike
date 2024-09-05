#pragma once
#include "../Base/EnemyBase.h"

namespace Client::Object
{
	class EnemyType004 : public EnemyBase
	{
	public:
		EnemyType004(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene);

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

		void TakeDamage(float Damage) override;

		void OnPostFinalize() override;

	private:
		std::shared_ptr<Engine::Component::Animation> _deathAnimation;

		bool _deathMotion;
		std::unique_ptr<::Audio::ISound> _onEnemy4HitSfx;



	};
}