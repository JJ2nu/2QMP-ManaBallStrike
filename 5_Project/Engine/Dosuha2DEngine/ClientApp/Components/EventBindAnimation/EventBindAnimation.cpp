#include "pch.h"
#include "EventBindAnimation.h"

Client::Component::EventBindAnimation::EventBindAnimation(std::wstring path, std::wstring motion)
	:Animation(path,motion)
{
}

void Client::Component::EventBindAnimation::Update(float deltaMetaTime, float deltaGameTime)
{
	Animation::Update(deltaMetaTime, deltaGameTime);
}

void Client::Component::EventBindAnimation::BindMotionBeginEvent(const std::wstring& name, const std::function<void()>& event)
{
	_animationAsset->BindMotionBeginEvent(name, event);
}

void Client::Component::EventBindAnimation::BindMotionEndEvent(const std::wstring& name, const std::function<void()>& event)
{
	_animationAsset->BindMotionEndEvent(name, event);
}

void Client::Component::EventBindAnimation::BindFrameEvent(const std::wstring& motionName, const size_t frameIndex, const std::function<void()>& event)
{
	_animationAsset->BindFrameEvent(motionName, frameIndex, event);
}

void Client::Component::EventBindAnimation::BindLastFrameEvent(const std::wstring& motionName, const std::function<void()>& event)
{
	_animationAsset->BindLastFrameEvent(motionName, event);
}
