#pragma once
#include "../Base/EnemyBase.h"

namespace Client::Object
{
	class RushIndicator;
	class Boss : public EnemyBase
	{
	public:
		Boss(const Engine::Math::Vector2& location);

		void SetTargetScene(std::shared_ptr<Engine::Scene> targetScene);
		void OnHit(float damage, const Engine::Math::Vector2& direction) override;

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
		void OnPostFinalize()override;
		void TakeDamage(float Damage) override;
		void PatternAttack(int pattern, float deltaGameTime, const Engine::Math::Vector2& distance);
		void Shoot(float deltaGameTime, const Engine::Math::Vector2& distance);
		void CircularShoot(float deltaGameTime, const Engine::Math::Vector2& distance);
		void Rush(float deltaGameTime);
		void PhaseTwo();
		void PhaseThree();
		int ChoosePattern();

	private:
		std::unique_ptr<::Audio::ISound> _onBossHitSfx;
		std::unique_ptr<::Audio::ISound> _onCircularShootSfx;
		std::unique_ptr<::Audio::ISound> _onShootSfx;
		std::unique_ptr<::Audio::ISound> _onAttackSfx;
		std::shared_ptr<Client::Object::RushIndicator> _rushIndicator;
		Engine::Math::Vector2 _rushTargetPosition;
		Engine::Math::Vector2 _lockedTarget;

		std::vector<std::pair<int, float>> _patternProbabilities;

		float _rushChargeTime;
		float _patternTime;
		bool _isRushing;
		bool _isShooting;
		bool _isTargetLocked;
		int _shootingNum;
		float _shootingTime;
		float _attackCoolTime;
		float _angleOffset;
		float _circularAngleOffset;
		float _t;
		int _phase;
		float _adjustValue;
		float _phaseHp;
		bool _isInvulnerable;
		float _invulnerableTimer;
		bool _shootingSound;
		float _soundDelay;
	};
}
