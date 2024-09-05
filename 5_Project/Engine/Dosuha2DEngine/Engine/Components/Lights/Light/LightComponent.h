#pragma once

namespace Engine::Component
{

	enum LightProp
	{
		lightpos,
		pointat,
		focus,
		angle,
		sufScale,
		constant,
		exponent,
		color
	};
	class Spotlight :
		public Base
	{
	public:
		explicit Spotlight(const std::shared_ptr<Scene>& location, D2D1::ColorF color, bool IsFlash = false);
		void Update(float deltaMetaTime, float deltaGameTime) override;
		void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
		void SetProperty(LightProp property, float value);
		void SetProperty(LightProp property, D2D1::ColorF value);
		void SwitchOn();
		void SwitchOff();
		void DeleteLight();
		void Finalize();
		bool IsFlash = false;

	protected:
		std::shared_ptr<Scene> _locationScene;


		int lightIndex;

		D2D1::ColorF color = D2D1::ColorF(D2D1::ColorF::WhiteSmoke);
		float focus = 37;
		float angle = 360.0f;
		float sufScale = 40.0f;
		float constant = 1.1f;
		float exponent = 95.0f;
		float height = 800.0f;

		float flashTimer = 0.f;
		float Duration = 0.5f;
		


		// Scene을(를) 통해 
	};
}

