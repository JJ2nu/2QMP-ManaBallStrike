#include "pch.h"
#include "ShadeComponent.h"
Engine::Component::Shadow::Shadow(ShadowType _shadowType)
	: Rect(Math::Vector2::Zero()), Base(), _shadebox(Math::Rect::Zero()), _isRender(false) , _shadowType(_shadowType)
{
	_isFixed = true;
	_isAdded = false;
}
Engine::Component::Shadow::Shadow(const Math::Vector2& size, ShadowType _shadowType)
	: Rect(size), Base(), _shadebox(Math::Rect::Zero()), _isRender(false), _shadowType(_shadowType)
{
	_isFixed = true;
	_isAdded = false;
}

void Engine::Component::Shadow::Update(float deltaMetaTime, float deltaGameTime)
{
	UpdateTransform();
	UpdateShadeBox();
	if(!_isFixed && _isAdded )	
		Engine::Manager::Render::GetShader()->UpdateObjectPosition(ObjectIndex,GetBound());
}

void Engine::Component::Shadow::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
	if (_isRender)
	{
		renderer->SetTransform(cameraMatrix);
		renderer->DrawRectangle(_shadebox, D2D1::ColorF(D2D1::ColorF::Green));
	}
}

void Engine::Component::Shadow::SetSize(const Math::Vector2& size)
{
	_size = size;
}

void Engine::Component::Shadow::AddShadow()
{
	if (!_isAdded)
	{
		ObjectIndex = Engine::Manager::Render::GetShader()->AddObject(GetBound());
		_isAdded = true;
	}

}

void Engine::Component::Shadow::SetFixed(bool isFixed)
{
	_isFixed = isFixed;
}

void Engine::Component::Shadow::Finalize()
{
	Engine::Manager::Render::GetShader()->DeleteObject(ObjectIndex);
}

void Engine::Component::Shadow::DrawShadowBox(bool isRender)
{
	_isRender = isRender;
}

const Engine::Math::Rect& Engine::Component::Shadow::GetBound()
{
	return _shadebox;
}

void Engine::Component::Shadow::UpdateShadeBox()
{
	const D2D1::Matrix3x2F transform = _centerTransform * _worldTransform;
	Math::Vector2 min{ 0, 0 };
	Math::Vector2 max = _size;
	min = transform.TransformPoint(min);
	max = transform.TransformPoint(max);
	_shadebox = Math::Rect{ min.x, min.y, max.x, max.y };
}
