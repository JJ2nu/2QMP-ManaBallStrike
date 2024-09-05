#pragma once

namespace Client::Component
{
	class EventBindAnimation;
}
namespace Client::Object
{
	class Torch : public Engine::Object::Base
	{
	public:
		Torch(Engine::Math::Vector2 location);
		Torch(Engine::Math::Vector2 location, bool light);
		const Engine::Math::Rect& GetBound() const override;

	protected:
		void OnCreateComponent() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
		void OnSetup() override;

	private:
		std::shared_ptr<Engine::Component::Bound> _boundComponent;
		std::shared_ptr<Client::Component::EventBindAnimation> _torchAnimation;
		std::shared_ptr<Engine::Component::Spotlight> _torchLight;


		Engine::Math::Vector2 location;
		int _glowStep = 0;
		float eps = 0.2f;
		float focus = 37.f;

		bool islight = true;
	};
}

