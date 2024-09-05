#pragma once
namespace Client::Component
{
	class EventBindAnimation;
}
namespace Client::Component
{
	class CollisionEffect : public EventBindAnimation
	{
	public:
		explicit CollisionEffect(std::wstring path, std::wstring motion);

		void Update(float deltaMetaTime, float deltaGameTime);
		float GetDegree();
		void SetCollisionPoint(const Engine::Math::Vector2& point);
		void SetCollisionDegree(const Engine::Math::Vector2& rotation);

	private:
		Engine::Math::Vector2 CollisionPoint;
		Engine::Math::Vector2 CollisionDegree;
	};
}
