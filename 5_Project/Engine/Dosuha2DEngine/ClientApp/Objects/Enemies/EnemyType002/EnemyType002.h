#pragma once
#include "../Base/EnemyBase.h"

namespace Client::Component
{

}

namespace Client::Object
{
	class RushIndicator;
	class EnemyType002 : public EnemyBase
	{
	public:
		EnemyType002(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene);

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

		void Rush(float deltaGameTime);

		void TakeDamage(float Damage) override;

		void OnPostFinalize() override;
		 
	private:
		bool _isRushing;
		bool _rushAnimation;
		float _rushCharge;
		float _rushCoolTime;
		float _rushSpeedRatio;
		float _elapsedTime;
		float _adjustedValue;
		float _t;

		std::shared_ptr<Client::Object::RushIndicator> _rushIndicator;

		Engine::Math::Vector2 _rushTargetPosition;
		std::unique_ptr<::Audio::ISound> _onEnemy2HitSfx;

	};
}