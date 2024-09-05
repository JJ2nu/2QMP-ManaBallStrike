#pragma once
namespace Client::Component
{
	class EventBindAnimation;
}

namespace Client::Object
{
	class Gate : public Engine::Object::Base, public Engine::Collisionable
	{
	public:
		using Event = std::function<void()>;

		explicit Gate(Engine::Math::Vector2 location);
		void OpenGate() const;
		void BindOnExit(Event event);
		Event _onExit;

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;
		void OnPostUpdate(float deltaMetaTime, float metaGameTime) override;
		void OnPostFinalize() override;
		const Engine::Math::Rect& GetBound() const override;

	private:
		Engine::Math::Vector2 _location;
		std::shared_ptr<Engine::Component::Bound> _boundComponent;
		std::shared_ptr<Component::EventBindAnimation> _doorAnimation;
		std::shared_ptr<Engine::Component::Bitmap> _doorOverlap;
		std::shared_ptr<Engine::Component::Collider::Box> _doorCollider;
		std::shared_ptr<Engine::Component::Collider::Box> _doorExitCollider;
		std::shared_ptr<Engine::Component::HidableAnimation> _arrow;
		std::unique_ptr<::Audio::ISound> _doorOpenSfx;


		std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;
	};
}

