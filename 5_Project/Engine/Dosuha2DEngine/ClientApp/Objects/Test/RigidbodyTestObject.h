#pragma once

namespace Client::Object
{
	class RigidbodyTestObject : public Engine::Object::Base
	{
	public:
		[[nodiscard]] const Engine::Math::Rect& GetBound() const override;

	protected:
		void OnCreateComponent() override;
		void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

	private:
		std::shared_ptr<Engine::Component::Shape::Box> _boxComponent;
		std::shared_ptr<Engine::Component::Bound> _boundComponent;
		std::shared_ptr<Engine::Component::RigidBody> _rigidbodyComponent;
	};
}
