#pragma once

namespace Render
{
    struct LightProperty
    {
        //int id;
        D2D1_POINT_2F location;
        float height = 800.0f;
        float focus;
        float angle;
        float exponent;
        float constant;
        float sufScale;
        D2D1::ColorF color;
    };

    class Shader : public IShader
    {
    public:
        explicit Shader(const Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>& renderTarget, const Microsoft::WRL::ComPtr<ID2D1Factory>& D2DFactory);
        HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
        ULONG AddRef() override;
        ULONG Release() override;

        int AddLight(D2D1_POINT_2F lightsource, float height = 800 ,float focus = 26, float angle = 150.0f, float sufScale = 40.0f , float constant= 5.0f, float exponent = 100.0f, D2D1::ColorF color = D2D1::ColorF::WhiteSmoke)override;
        void DeleteLight(int idx) override;

        void UpdateLightPosition(int idx, D2D1_POINT_2F lightsource) override;
        void UpdateLightProperty(int idx, int property, float value) override;
        void UpdateLightProperty(int idx, int property, D2D1::ColorF color) override;
        void UpdateLightflag(int idx, bool lightflag) override;

        int AddObject(D2D1_RECT_F object) override;
        void DeleteObject(int idx) override;
        void UpdateObjectPosition(int idx, D2D1_RECT_F object) override;

        void SetScreenSize(D2D1_VECTOR_2F size) override;
        Microsoft::WRL::ComPtr<ID2D1PathGeometry> IntersectGeometry( Microsoft::WRL::ComPtr<ID2D1PathGeometry> g1, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g2) override;
        Microsoft::WRL::ComPtr<ID2D1PathGeometry> UnionGeometry(Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g1, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g2) override;

        void SetBackground( Microsoft::WRL::ComPtr<ID2D1Bitmap> _background) override;
        void SetLightMask(Microsoft::WRL::ComPtr<ID2D1Bitmap> _lightmask) override;
         void SetCameraMatrix(D2D1::Matrix3x2F cameramatrix) override;

        void ChainEffects() override;
        Microsoft::WRL::ComPtr<ID2D1PathGeometry> GetRectShadow(D2D1_POINT_2F lightsource, D2D1_RECT_F object) override;
        void CastShadow() override;
        void Shade() override;

        Microsoft::WRL::ComPtr<ID2D1PathGeometry> CastShadowPerLight(LightProperty lightsource);



    private:
        ULONG _refCount;

        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> _renderTarget;
        Microsoft::WRL::ComPtr<ID2D1DeviceContext> _deviceContext;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> _testbrush;
        Microsoft::WRL::ComPtr<ID2D1Factory> _D2DFactory;
        float ScreenWidth;
        float ScreenHeight;
        //shading
        int _activeLightCount = 0;
        std::vector<Microsoft::WRL::ComPtr<ID2D1Effect>> _lights;
        std::vector<LightProperty> _lightProperty;
        std::vector<bool> _lightflag;
        std::vector<D2D1_RECT_F> _object;
        std::vector<Microsoft::WRL::ComPtr<ID2D1Effect>> _overlays;
        Microsoft::WRL::ComPtr<ID2D1Bitmap> _lightmask;
        Microsoft::WRL::ComPtr<ID2D1Bitmap> _background;
        Microsoft::WRL::ComPtr<ID2D1PathGeometry> _empty;

        std::vector<Microsoft::WRL::ComPtr<ID2D1PathGeometry>> _shadows;
        std::vector<Microsoft::WRL::ComPtr<ID2D1PathGeometry>> _shadowsPerLight;
        Microsoft::WRL::ComPtr<ID2D1PathGeometry> _finalShadow;
        Microsoft::WRL::ComPtr<ID2D1PathGeometry> _fullScreen;
        
        D2D1::Matrix3x2F _cameraTransform = D2D1::Matrix3x2F::Identity();
        int flag = 0;

        D2D1_LAYER_PARAMETERS1 layerParams = {};
        Microsoft::WRL::ComPtr <ID2D1Layer> pLayer = NULL;


		bool IsBackgroundOn() override;

		bool IsLightMaskOn() override;




       

    };
}
