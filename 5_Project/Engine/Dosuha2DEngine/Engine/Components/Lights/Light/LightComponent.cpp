#include "pch.h"
#include "LightComponent.h"

Engine::Component::Spotlight::Spotlight(const std::shared_ptr<Scene>& location, D2D1::ColorF color, bool _IsFlash) : color(color) , _locationScene(location) , IsFlash(_IsFlash)
{
	if (IsFlash) focus = 8;
	lightIndex = Engine::Manager::Render::GetShader()->AddLight(_locationScene.get()->GetLocation(),
		height, focus, angle, sufScale, constant, exponent, color);

}


void Engine::Component::Spotlight::Update(float deltaMetaTime, float deltaGameTime)
{
	Engine::Manager::Render::GetShader()->UpdateLightPosition(lightIndex, _locationScene.get()->GetLocation());
	flashTimer -= deltaMetaTime;
	if (IsFlash)
	{
		if (focus > -6)
		{
			focus -= .5f;
			
			//float temp = Engine::Math::Helper::Lerp()( focus, -100, flashTimer /Duration );
			
			SetProperty(Engine::Component::LightProp::focus, focus);
		}
		else
		{
			DeleteLight();

		}
	}
}

void Engine::Component::Spotlight::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
}

void Engine::Component::Spotlight::SetProperty(LightProp property, float value)
{
	Engine::Manager::Render::GetShader()->UpdateLightProperty(lightIndex, property, value);
}

void Engine::Component::Spotlight::SetProperty(LightProp property, D2D1::ColorF value)
{
	Engine::Manager::Render::GetShader()->UpdateLightProperty(lightIndex, property, value);
}

void Engine::Component::Spotlight::SwitchOn()
{
	Engine::Manager::Render::GetShader()->UpdateLightflag(lightIndex, true);
}

void Engine::Component::Spotlight::SwitchOff()
{
	Engine::Manager::Render::GetShader()->UpdateLightflag(lightIndex, false);
}

void Engine::Component::Spotlight::DeleteLight()
{
	Engine::Manager::Render::GetShader()->DeleteLight(lightIndex);

}

void Engine::Component::Spotlight::Finalize()
{
	DeleteLight();
}


