#pragma once


namespace Client::Component
{

	class EventBindAnimation : public Engine::Component::Animation
	{
	public:
		explicit EventBindAnimation(std::wstring path, std::wstring motion);
		void Update(float deltaMetaTime, float deltaGameTime) override;

		void BindMotionBeginEvent(const std::wstring& name, const std::function<void()>& event);
		void BindMotionEndEvent(const std::wstring& name, const std::function<void()>& event);
		void BindFrameEvent(const std::wstring& motionName, const size_t frameIndex, const std::function<void()>& event);
		void BindLastFrameEvent(const std::wstring& motionName, const std::function<void()>& event);
	};
}

