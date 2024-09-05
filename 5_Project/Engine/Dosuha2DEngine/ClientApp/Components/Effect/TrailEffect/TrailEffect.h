#pragma once
namespace Client::Component
{
	class EventBindAnimation;
}
namespace Client::Component
{
	class TrailEffect : public EventBindAnimation
	{
	public:
		explicit TrailEffect(std::wstring path, std::wstring motion);

	private:

	};
}

