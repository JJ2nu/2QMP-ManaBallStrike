#pragma once
#include "../Base/EnemyBase.h"

namespace Client::Object
{
	class EnemyType003 : public EnemyBase
	{
	public:
		EnemyType003(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene);

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

		void Shoot();

		void TakeDamage(float Damage) override;

		void OnPostFinalize() override;

	private:
		float _chargeTime;
		float _shootingCoolTime;
		bool _isShot;
		bool _isAwayDirection;
		std::unique_ptr<::Audio::ISound> _onEnemy3HitSfx;
		std::unique_ptr<::Audio::ISound> _onEnemy3FireSfx;

	};
}