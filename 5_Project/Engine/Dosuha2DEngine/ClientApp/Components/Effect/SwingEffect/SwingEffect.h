#pragma once
namespace Client::Component
{
	class EventBindAnimation;
}
namespace Client::Component
{
	class SwingEffect : public EventBindAnimation
	{
	public:
		explicit SwingEffect(std::wstring path, std::wstring motion);

		void Update(float deltaMetaTime, float deltaGameTime);
		float GetDegree() const;

		void SetDirection(const Engine::Math::Vector2& direction);

	private:
		Engine::Math::Vector2 _direction;
	};
}

