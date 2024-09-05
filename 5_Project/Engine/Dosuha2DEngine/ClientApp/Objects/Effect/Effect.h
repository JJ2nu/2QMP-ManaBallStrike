#pragma once

namespace Client::Component
{
	class EventBindAnimation;
	class CollisionEffect;
	class TrailEffect;
}
namespace Client::Object
{
	class ImpactEffect : public Engine::Object::Base
	{
	public:
		ImpactEffect(Engine::Math::Vector2 location, Engine::Math::Vector2 rotation, std::wstring motion);
		void SetFlashLight();
		[[nodiscard]] const Engine::Math::Rect& GetBound() const override;
	protected:
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime);
		void OnCreateComponent() override;
		void OnSetup() override;

	private:
		std::shared_ptr<Engine::Component::Bound> _boundComponent;
		std::shared_ptr<Client::Component::CollisionEffect> _effect;
		std::shared_ptr<Engine::Component::Spotlight> _light;
		Engine::Math::Vector2 location;
		Engine::Math::Vector2 rotation;
		std::wstring motionname;
	};


	class Tail : public Engine::Object::Base
	{
	public:
		Tail(Engine::Math::Vector2 location, Engine::Math::Vector2 rotation, std::wstring motion);

		[[nodiscard]] const Engine::Math::Rect& GetBound() const override;
	protected:
		void OnCreateComponent() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
		void OnSetup() override;

	private:
		std::shared_ptr<Engine::Component::Bound> _boundComponent;
		std::shared_ptr<Client::Component::EventBindAnimation> _effect;
		Engine::Math::Vector2 location;
		Engine::Math::Vector2 rotation;
		std::wstring motionname;
	};

	class RushIndicator : public Engine::Object::Base
	{
	public:
		RushIndicator(Engine::Math::Vector2 location, Engine::Math::Vector2 rotation, std::wstring path);

		[[nodiscard]] const Engine::Math::Rect& GetBound() const override;
		void UpdateTargetLocation(Engine::Math::Vector2 location);
	protected:
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime);
		void OnCreateComponent() override;
		void OnSetup() override;

	private:
		std::shared_ptr<Engine::Component::Bound> _boundComponent;
		std::shared_ptr<Engine::Component::FadeBitmap> _rushIndicatorBitmap;
		Engine::Math::Vector2 location;
		Engine::Math::Vector2 targetlocation;
		Engine::Math::Vector2 rotation;
		float bitmapLength;
		float ratio;
		float degree;
		float rushDelayTimer = 0.f;

		std::wstring bitmapPath;
	};
}

