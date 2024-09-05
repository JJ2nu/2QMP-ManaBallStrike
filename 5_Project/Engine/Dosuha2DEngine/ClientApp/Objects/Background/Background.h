#pragma once

namespace Client::Component
{
	class BackgroundBitmap;
}

namespace Client::Object
{
	class Background : public Engine::Object::Base, public Engine::Collisionable
	{
	public:
		Background();
		[[nodiscard]] const Engine::Math::Rect& GetBound() const override;

		std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

	protected:
		void OnCreateComponent() override;
		void OnSetup() override;

		std::shared_ptr<Engine::Component::Bound> _boundComponent;
		std::shared_ptr<Client::Component::BackgroundBitmap> _bitmapComponent;

	private:
		std::shared_ptr<Engine::Component::Collider::Box> _boxCollider;
	};
}
