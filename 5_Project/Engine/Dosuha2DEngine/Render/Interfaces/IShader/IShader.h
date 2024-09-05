#pragma once

DEFINE_GUID(IID_IShader, 0x82a08e3b, 0xebe4, 0x49bc, 0xbd, 0xd2, 0xa4, 0x8c, 0xa2, 0x37, 0xfd, 0xb5);

namespace Render
{

    struct IShader : IUnknown
    {
        IShader() = default;
        IShader(const IShader& other) = default;
        IShader(IShader&& other) noexcept = default;
        IShader& operator=(const IShader& other) = default;
        IShader& operator=(IShader&& other) noexcept = default;
        virtual ~IShader() = default;

        virtual void SetScreenSize(D2D1_VECTOR_2F size) = 0;
        virtual int AddLight(D2D1_POINT_2F lightsource, float height = 800, float focus = 26, float angle = 150.0f, float sufScale = 40.0f, float constant = 5.0f, float exponent = 100.0f,D2D1::ColorF color = D2D1::ColorF::WhiteSmoke) = 0;
        virtual void DeleteLight(int idx) = 0;
        virtual void UpdateLightPosition(int idx, D2D1_POINT_2F lightsource) = 0;
        virtual void UpdateLightProperty(int idx, int property, float value ) = 0;
        virtual void UpdateLightProperty(int idx, int property, D2D1::ColorF color ) = 0;
        virtual void UpdateLightflag(int idx, bool lightflag ) = 0;

        virtual int AddObject(D2D1_RECT_F object) = 0;
        virtual void DeleteObject(int idx) = 0;
        virtual void UpdateObjectPosition(int idx, D2D1_RECT_F object) = 0;

        virtual Microsoft::WRL::ComPtr<ID2D1PathGeometry> IntersectGeometry( Microsoft::WRL::ComPtr<ID2D1PathGeometry> g1, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g2) = 0;
        virtual Microsoft::WRL::ComPtr<ID2D1PathGeometry> UnionGeometry(Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g1, Microsoft::WRL::ComPtr<ID2D1PathGeometry> g2) = 0;

        virtual bool IsBackgroundOn() = 0;
        virtual bool IsLightMaskOn() = 0;
        virtual void SetBackground( Microsoft::WRL::ComPtr<ID2D1Bitmap> _background) = 0;
        virtual void SetLightMask( Microsoft::WRL::ComPtr<ID2D1Bitmap> _lightmask) = 0;
		virtual void SetCameraMatrix(D2D1::Matrix3x2F cameramatrix) = 0;
        virtual Microsoft::WRL::ComPtr<ID2D1PathGeometry> GetRectShadow(D2D1_POINT_2F lightsource, D2D1_RECT_F object) = 0;
        virtual void CastShadow() = 0;
        virtual void ChainEffects() = 0;
        virtual void Shade() = 0;
    };
}

