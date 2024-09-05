#include "pch.h"
#include "Shader.h"

Render::Shader::Shader(const Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>& renderTarget, const Microsoft::WRL::ComPtr<ID2D1Factory>& D2DFactory)
	: _refCount(1), _renderTarget(renderTarget), _D2DFactory(D2DFactory)
{
	ThrowResultErrorIf<Exception::ResultException>()
		(_renderTarget->QueryInterface(IID_PPV_ARGS(&_deviceContext)),
			L"Failed to convert renderTarget to deviceContext");

	ThrowResultErrorIf<Exception::ResultException>()(
		_deviceContext.Get()->CreateSolidColorBrush(D2D1_COLOR_F{0,0,0,1},&_testbrush),
		L"Failed to _deviceContext.Get()->CreateSolidColorBrush");

	
	ThrowResultErrorIf<Exception::ResultException>()(
	_deviceContext.Get()->CreateLayer(NULL, &pLayer),
			L"Failed to _deviceContext.Get()->CreateLayer(NULL, &pLayer)");


	layerParams.contentBounds = D2D1::InfiniteRect();
	layerParams.opacity = 1.f;
	layerParams.layerOptions = D2D1_LAYER_OPTIONS1_IGNORE_ALPHA;

	_D2DFactory->CreatePathGeometry(&_fullScreen);
	Microsoft::WRL::ComPtr<ID2D1GeometrySink> geometrySink;
	_fullScreen->Open(&geometrySink);
	geometrySink->BeginFigure(D2D1::Point2F(50, 50), D2D1_FIGURE_BEGIN_FILLED);
	geometrySink->EndFigure(D2D1_FIGURE_END_OPEN); // OPEN���� �����ϸ� ���� ����
	geometrySink->Close();

	_activeLightCount = 0;
}
HRESULT Render::Shader::QueryInterface(const IID& riid, void** ppvObject)
{
	if (riid == IID_IUnknown) (*ppvObject) = static_cast<IUnknown*>(this);
	else if (riid == IID_IShader) *ppvObject = static_cast<IShader*>(this);
	else
	{
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}
ULONG Render::Shader::AddRef()
{
	return InterlockedIncrement(&_refCount);
}
ULONG Render::Shader::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_refCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}
void Render::Shader::ChainEffects()
{
	if (_activeLightCount==0)return;
	else if ( _activeLightCount == 1)
	{
		_overlays[0]->SetInput(0, _background.Get());
		int i = 0;
		while (!_lightflag[i])
		{
			i++;
		}
		_overlays[0]->SetInputEffect(1, _lights[i].Get());
	}
	else
	{
		std::vector<int> curLightCount;

		int i = 0;
		while (!_lightflag[i])
		{
			i++;
		}
		_overlays[0]->SetInputEffect(0, _lights[i].Get());
		i++;
		while (!_lightflag[i])
		{
			i++;
		}
		_overlays[0]->SetInputEffect(1, _lights[i].Get());
		i++;
			for (int j = 1; j < _activeLightCount-1; j++)
			{
				while (!_lightflag[i])
				{
					i++;
				}
				_overlays[j]->SetInputEffect(0, _overlays[j - 1].Get());
				_overlays[j]->SetInputEffect(1, _lights[i].Get());
				i++;
			}
			_overlays[_activeLightCount - 1]->SetInput(0, _background.Get());
			_overlays[_activeLightCount - 1]->SetInputEffect(1, _overlays[_activeLightCount - 2].Get());
		
	}
}
void Render::Shader::Shade()
{
	for (int i = 0; i < _lightProperty.size(); i++)
	{
		D2D1_POINT_2F curLightPos;
		curLightPos = _cameraTransform.TransformPoint(_lightProperty[i].location);
		if(_lightflag[i])
			ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, D2D1::Vector3F(_lightProperty[i].location.x + ScreenWidth/2, _lightProperty[i].location.y + ScreenHeight / 2, _lightProperty[i].height)), L"Failed to update light effect prop - lightposition");
		else
			ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, D2D1::Vector3F(_lightProperty[i].location.x + ScreenWidth/2, _lightProperty[i].location.y + ScreenHeight / 2,0)), L"Failed to update light effect prop - lightposition");
		ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, D2D1::Vector3F(_lightProperty[i].location.x + ScreenWidth / 2, _lightProperty[i].location.y + ScreenHeight / 2, 0)), L"Failed to update light effect prop - POINTS");
		ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_FOCUS, _lightProperty[i].focus), L"Failed to update light effect prop - focus");
		ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_LIMITING_CONE_ANGLE, _lightProperty[i].angle), L"Failed to update light effect prop - angle");
		ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_SURFACE_SCALE, _lightProperty[i].sufScale), L"Failed to update light effect prop - sufScale");
		ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_CONSTANT, _lightProperty[i].constant), L"Failed to update light effect prop - constant");
		ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_EXPONENT, _lightProperty[i].exponent), L"Failed to update light effect prop - exponent");
		ThrowResultErrorIf<Exception::ResultException>()(_lights[i]->SetValue(D2D1_SPOTSPECULAR_PROP_COLOR, D2D1::Vector3F(_lightProperty[i].color.r, _lightProperty[i].color.g, _lightProperty[i].color.b)), L"Failed to update light effect prop - color");
	}
	_deviceContext->SetTransform(_cameraTransform);
	_deviceContext.Get()->DrawImage(_background.Get(), { -ScreenWidth / 2,-ScreenHeight / 2 });
	if (_lights.empty())return;
	CastShadow();
	ChainEffects();
	layerParams.geometricMask = _finalShadow.Get(); // Ŭ������ ������
	layerParams.maskTransform = D2D1::Matrix3x2F::Identity(); // ��ȯ ����
	_deviceContext->SetTransform(_cameraTransform);
	_deviceContext.Get()->PushLayer(layerParams, pLayer.Get());
	if(_activeLightCount!=0)
		_deviceContext.Get()->DrawImage(_overlays[_activeLightCount - 1].Get(),{ -ScreenWidth/2, -ScreenHeight / 2 });
	else
		_deviceContext.Get()->DrawImage(_background.Get(), { -ScreenWidth / 2,-ScreenHeight / 2 });

	_deviceContext.Get()->PopLayer();

}
Microsoft::WRL::ComPtr<ID2D1PathGeometry> Render::Shader::CastShadowPerLight(LightProperty lightsource)
{
	Microsoft::WRL::ComPtr<ID2D1PathGeometry> resultshadow;
	ThrowResultErrorIf<Exception::ResultException>()(
		_D2DFactory->CreatePathGeometry(&resultshadow)
		, L"Failed to _D2DFactory->CreatePathGeometry(&resultshadow) ");

	_shadows.clear();
	if (_object.empty())
	{
		resultshadow = _fullScreen;
	}
	for (auto& object : _object)
	{
		if (object.left == 0 && object.top == 0 && object.right == 0 && object.bottom == 0) continue;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry> pShadowGeometry = GetRectShadow(lightsource.location, object);
		if (!pShadowGeometry.Get())
			pShadowGeometry = _fullScreen;
		_shadows.push_back(pShadowGeometry);
	}
	Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink;

	if (_shadows.empty())resultshadow = _fullScreen;
	else if (_shadows.size() == 1)
	{
		resultshadow = _shadows[0];
	}
	else
	{
		resultshadow = IntersectGeometry( _shadows[0], _shadows[1]);
		if (_shadows.size() >= 2)
		{
			for (int i = 2; i < _shadows.size(); i++)
			{

				resultshadow = IntersectGeometry(resultshadow, _shadows[i]);
			/*	if (!resultshadow || !_shadows[i])
					resultshadow = _fullScreen;
				else
				{
					resultshadow = IntersectGeometry( _shadows[0], _shadows[1]);
				}*/
			}
		}
	}
	return resultshadow.Get();
}

bool Render::Shader::IsBackgroundOn()
{
	return _background != nullptr;
}

bool Render::Shader::IsLightMaskOn()
{
	return _lightmask != nullptr;
}


void Render::Shader::CastShadow()
{

	std::vector<int> curLightCount;
	for (int i = 0; i < _lightflag.size(); i++)
	{
		if (_lightflag[i]) curLightCount.push_back(i);
	}
	if (_activeLightCount==0)
	{
		return;
	}
	else if (_activeLightCount == 1)
	{
			_finalShadow = CastShadowPerLight(_lightProperty[curLightCount[0]]);
	}
	else
	{
		_shadowsPerLight.clear();
		for (int i = 0; i < curLightCount.size(); i++)
		{
			
				_shadowsPerLight.push_back(CastShadowPerLight(_lightProperty[curLightCount[i]]));
		}

		for (int i = 0; i < curLightCount.size(); i++)
		{
			if (i == 0)
			{
				_finalShadow = _shadowsPerLight[i];
			}
			else
			{
				Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink;
				_finalShadow = UnionGeometry(pSink, _finalShadow, _shadowsPerLight[i]);
			}
		}
	}
}
void Render::Shader::UpdateLightPosition(int idx, D2D1_POINT_2F lightsource)
{
	_lightProperty[idx].location = lightsource;
}
void Render::Shader::UpdateLightProperty(int idx, int property, float value)
{
	if (property == 1) _lightProperty[idx].height = value;
	else if (property == 2) _lightProperty[idx].focus = value;
	else if (property == 3)_lightProperty[idx].angle = value;
	else if (property == 4)_lightProperty[idx].exponent = value;
	else if (property == 5)_lightProperty[idx].constant = value;
	else if (property == 6)_lightProperty[idx].sufScale = value;
}
void Render::Shader::UpdateLightProperty(int idx, int property, D2D1::ColorF color)
{
	_lightProperty[idx].color = color;
}
void Render::Shader::UpdateLightflag(int idx, bool lightflag)
{
	_lightflag[idx] = lightflag;
}
Microsoft::WRL::ComPtr<ID2D1PathGeometry> Render::Shader::IntersectGeometry( Microsoft::WRL::ComPtr<ID2D1PathGeometry> g1, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g2)
{
	Microsoft::WRL::ComPtr<ID2D1PathGeometry> pResultGeometry;
	ThrowResultErrorIf<Exception::ResultException>()(
		_D2DFactory->CreatePathGeometry(&pResultGeometry)
		, L"Failed to Create pathgeometry - IntersectGeometry");
	Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink;

	ThrowResultErrorIf<Exception::ResultException>()(
		pResultGeometry->Open(&pSink)
		, L"Failed to open geometrysink - IntersectGeometry");

	
	ThrowResultErrorIf<Exception::ResultException>()(

		g1.Get()->CombineWithGeometry(
			g2.Get(),
			D2D1_COMBINE_MODE_INTERSECT,
			NULL,
			NULL,
			pSink.Get()
		)
		, L"Failed to g1.Get()->CombineWithGeometry - IntersectGeometry");



	ThrowResultErrorIf<Exception::ResultException>()(
		pSink->Close()
		, L"Failed to close geometrysink - IntersectGeometry");


	return pResultGeometry;
}
Microsoft::WRL::ComPtr<ID2D1PathGeometry> Render::Shader::UnionGeometry(Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g1, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g2)
{

	Microsoft::WRL::ComPtr<ID2D1PathGeometry> pResultGeometry;
	ThrowResultErrorIf<Exception::ResultException>()(
		_D2DFactory->CreatePathGeometry(&pResultGeometry)
		, L"Failed to Create pathgeometry - UnionGeometry");

	ThrowResultErrorIf<Exception::ResultException>()(
		pResultGeometry->Open(&pSink)
		, L"Failed to open geometrysink - UnionGeometry");

	ThrowResultErrorIf<Exception::ResultException>()(

		g1.Get()->CombineWithGeometry(
			g2.Get(),
			D2D1_COMBINE_MODE_UNION,
			NULL,
			NULL,
			pSink.Get()
		)
		, L"Failed to g1.Get()->CombineWithGeometry - UnionGeometry");

	ThrowResultErrorIf<Exception::ResultException>()(
		pSink->Close()
		, L"Failed to close geometrysink - UnionGeometry");

	return pResultGeometry.Get();
}
Microsoft::WRL::ComPtr<ID2D1PathGeometry> Render::Shader::GetRectShadow(D2D1_POINT_2F lightSource, D2D1_RECT_F object)
{
	if (object.left < lightSource.x &&
		object.right > lightSource.x &&
		object.top < lightSource.y &&
		object.bottom > lightSource.y)
	{
		return nullptr;
	}
	D2D1_POINT_2F vertices[4] = {
		{ object.left, object.top },
		{ object.right, object.top },
		{ object.right, object.bottom },
		{ object.left, object.bottom }
	};
	std::vector<D2D1_POINT_2F> points;

	D2D1_POINT_2F Center = { (object.left + object.right) / 2 ,(object.top + object.bottom) / 2 };
	D2D1_VECTOR_2F Extent = { (object.right - object.left) / 2 ,(object.bottom - object.top) / 2 };
	if (Center.x - Extent.x > lightSource.x && Center.y - Extent.y <= lightSource.y && Center.y + Extent.y >= lightSource.y)
	{
		points.push_back(vertices[0]);
		points.push_back(vertices[3]);
	}
	else if (Center.x + Extent.x <= lightSource.x && Center.y - Extent.y <= lightSource.y && Center.y + Extent.y >= lightSource.y)
	{
		points.push_back(vertices[1]);
		points.push_back(vertices[2]);
	}
	else if (Center.y - Extent.y > lightSource.y && Center.x - Extent.x <= lightSource.x && Center.x + Extent.x >= lightSource.x)
	{
		points.push_back(vertices[0]);
		points.push_back(vertices[1]);
	}
	else if (Center.y + Extent.y <= lightSource.y && Center.x - Extent.x <= lightSource.x && Center.x + Extent.x >= lightSource.x)
	{
		points.push_back(vertices[2]);
		points.push_back(vertices[3]);
	}

	else if (Center.x - Extent.x > lightSource.x && Center.y - Extent.y > lightSource.y)
	{
		points.push_back(vertices[1]);
		points.push_back(vertices[0]);
		points.push_back(vertices[3]);
	}
	else if (Center.x - Extent.x > lightSource.x && Center.y + Extent.y <= lightSource.y)
	{
		points.push_back(vertices[0]);
		points.push_back(vertices[3]);
		points.push_back(vertices[2]);
	}
	else if (Center.x + Extent.x <= lightSource.x && Center.y - Extent.y > lightSource.y)
	{
		points.push_back(vertices[0]);
		points.push_back(vertices[1]);
		points.push_back(vertices[2]);
	}
	else if (Center.x + Extent.x <= lightSource.x && Center.y + Extent.y <= lightSource.y)
	{
		points.push_back(vertices[1]);
		points.push_back(vertices[2]);
		points.push_back(vertices[3]);
	}
	int size = points.size();

	for (int i = points.size() - 1; i >= 0; i--)
	{
		D2D1_POINT_2F vertex = points[i];
		float dx = vertex.x - lightSource.x;
		float dy = vertex.y - lightSource.y;
		float distance = sqrt(dx * dx + dy * dy);

		float k = 100000.0f; 
		D2D1_POINT_2F shadowEnd =
		{
			vertex.x + (dx / distance) * k,
			vertex.y + (dy / distance) * k
		};

		if (size == 3 && i == 1)continue;
		points.push_back(shadowEnd);
	}


	Microsoft::WRL::ComPtr<ID2D1PathGeometry> pPathGeometry;
	Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink;


	ThrowResultErrorIf<Exception::ResultException>()(
		_D2DFactory->CreatePathGeometry(&pPathGeometry)
		, L"Failed to Create pPathGeometry - individual shadow");

	ThrowResultErrorIf<Exception::ResultException>()(
		pPathGeometry->Open(&pSink)
		, L"Failed to open geometrysink - individual shadow");

	if (!points.empty())
	{
		pSink->BeginFigure(points[0], D2D1_FIGURE_BEGIN_FILLED);
		for (int i = 1; i < points.size(); i++) {
			pSink->AddLine(points[i]);
		}
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pSink->Close();
	}

	Microsoft::WRL::ComPtr<ID2D1PathGeometry> pResultGeometry;
	ThrowResultErrorIf<Exception::ResultException>()(
		_D2DFactory->CreatePathGeometry(&pResultGeometry)
		, L"Failed to Create PathGeometry - inverse shadow");

	ThrowResultErrorIf<Exception::ResultException>()(
		pResultGeometry->Open(&pSink)
		, L"Failed to open geometrysink - inverse shadow");


	ThrowResultErrorIf<Exception::ResultException>()(
		_fullScreen.Get()->CombineWithGeometry(
			pPathGeometry.Get(),
			D2D1_COMBINE_MODE_EXCLUDE,
			NULL,
			NULL,
			pSink.Get()
		)
		, L"Failed to exclude geometrysink - inverse shadow");

	ThrowResultErrorIf<Exception::ResultException>()(
		pSink->Close()
		, L"Failed to close geometrysink - inverse shadow");
	if (!pResultGeometry) pResultGeometry = _fullScreen;
	return pResultGeometry;
}
int Render::Shader::AddLight(D2D1_POINT_2F lightsource, float height, float focus, float angle, float sufScale, float constant, float exponent, D2D1::ColorF color)
{
	_activeLightCount ++;

	Microsoft::WRL::ComPtr<ID2D1Effect> light;
	_deviceContext->CreateEffect(CLSID_D2D1SpotSpecular, &light);

	LightProperty lightprop = { lightsource,height, focus, angle, sufScale,constant, exponent,color };
	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_FOCUS, focus), L"Failed to set light effect prop - focus");
	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_LIMITING_CONE_ANGLE, angle), L"Failed to set light effect prop - angle");
	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_SURFACE_SCALE, sufScale), L"Failed to set light effect prop - sufScale");
	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_CONSTANT, constant), L"Failed to set light effect prop - constant");
	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_COLOR, D2D1::Vector3F(color.r, color.g, color.b)), L"Failed to set light effect prop - color");
	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_SCALE_MODE, D2D1_SPOTSPECULAR_SCALE_MODE_LINEAR), L"Failed to set light effect prop - scale mode");
	D2D1_POINT_2F curLightPos = _cameraTransform.TransformPoint(lightsource);

	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, D2D1::Vector3F(curLightPos.x, curLightPos.y, height)), L"Failed to set light effect prop - lightposition");
	ThrowResultErrorIf<Exception::ResultException>()(light->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, D2D1::Vector3F(curLightPos.x, curLightPos.y, 0)), L"Failed to set light effect prop - POINTS");
	light->SetInput(0, _lightmask.Get());

	Microsoft::WRL::ComPtr<ID2D1Effect> overlay;
	ThrowResultErrorIf<Exception::ResultException>()(_deviceContext->CreateEffect(CLSID_D2D1Blend, &overlay), L"Failed to Create blend effect");
	ThrowResultErrorIf<Exception::ResultException>()(overlay->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_OVERLAY), L"Failed to set blend effect prop - blend mode");
	_overlays.push_back(overlay);

	int curIdx= -1;
	for (int i = 0; i < _lightflag.size(); i++)
	{
		if (!_lightflag[i])
		{
			curIdx = i;
			if (curIdx != -1) break;
		}
	}
	if (curIdx == -1)
	{
		_lightflag.push_back(true);
		_lights.push_back(light);
		_lightProperty.push_back(lightprop);
		return _lightProperty.size() - 1;
	}
	else
	{
		_lightflag[curIdx]=true;
		_lights[curIdx] = light;
		_lightProperty[curIdx] = lightprop;
		return curIdx;
	}


}
void Render::Shader::DeleteLight(int idx)
{
	if (_lightflag[idx])
	{
	_lightflag[idx] = false;
	_activeLightCount--;

	}
}
int Render::Shader::AddObject(D2D1_RECT_F object)
{
	int curIdx = -1;
	for (int i = 0; i < _object.size(); i++)
	{
		if (_object[i].left == -1 && _object[i].top == -1 && _object[i].right == -1 && _object[i].bottom == -1)
			curIdx = i;
		else
			continue;
	}
	if (curIdx == -1)
	{
		_object.push_back(object);
		return _object.size() - 1;
	}
	else
	{
		_object[curIdx] = object;
		return curIdx;
	}
}
void Render::Shader::DeleteObject(int idx)
{
	_object[idx].left = -1;
	_object[idx].bottom = -1;
	_object[idx].top = -1;
	_object[idx].right = -1;
}
void Render::Shader::UpdateObjectPosition(int idx, D2D1_RECT_F object)
{
	_object[idx] = object;

}
void Render::Shader::SetScreenSize(D2D1_VECTOR_2F size)
{
	
	ScreenWidth = _background->GetSize().width;
	ScreenHeight = _background->GetSize().height;
	ThrowResultErrorIf<Exception::ResultException>()(
		_D2DFactory->CreatePathGeometry(&_fullScreen)
		, L"Failed to Create pathgeometry - full screen");

	Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink;

	ThrowResultErrorIf<Exception::ResultException>()(
		_fullScreen->Open(&pSink)
		, L"Failed to open geometrysink - full screen");


	pSink->BeginFigure(D2D1::Point2F(-ScreenWidth/2, -ScreenHeight / 2), D2D1_FIGURE_BEGIN_FILLED);
	pSink->AddLine(D2D1::Point2F(ScreenWidth / 2, -ScreenHeight/2));  // ������ ��
	pSink->AddLine(D2D1::Point2F(ScreenWidth / 2, ScreenHeight / 2)); // ������ �Ʒ�
	pSink->AddLine(D2D1::Point2F(-ScreenWidth / 2, ScreenHeight / 2));    // ���� �Ʒ�
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	ThrowResultErrorIf<Exception::ResultException>()(
		pSink->Close()
		, L"Failed to close geometrysink - full screen");
}
void Render::Shader::SetBackground( Microsoft::WRL::ComPtr<ID2D1Bitmap> _background)
{
	this->_background = _background;
	//SetScreenSize({0,0});
}
void Render::Shader::SetLightMask(Microsoft::WRL::ComPtr<ID2D1Bitmap> _lightmask)
{
	this->_lightmask = _lightmask;
}
void Render::Shader::SetCameraMatrix(D2D1::Matrix3x2F cameramatrix)
{
	_cameraTransform = cameramatrix;
}