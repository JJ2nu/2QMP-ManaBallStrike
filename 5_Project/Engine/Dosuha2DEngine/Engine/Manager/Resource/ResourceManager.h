#pragma once

namespace Engine::Manager
{
    class Resource : Base<Resource>
    {
        friend const std::shared_ptr<Resource>& Manager::Base<Resource>::GetInstance();

        class BitmapLoader;
        class AnimationLoader;

    public:
        class MasterLoader;
        using Loader = std::shared_ptr<MasterLoader>;

        static void Initialize(const Microsoft::WRL::ComPtr<::Render::ISystem>& renderSystem,
                               const Dosuha::Pointer<::Animation::ISystem>& animationSystem);
        static void Finalize();

        static std::shared_ptr<MasterLoader> GetLoader() noexcept;

    private:
        Microsoft::WRL::ComPtr<::Render::ISystem> _renderSystem;
        Dosuha::Pointer<::Animation::ISystem> _animationSystem;

        std::shared_ptr<MasterLoader> _loader;

        class BitmapLoader
        {
        public:
            explicit BitmapLoader(const Microsoft::WRL::ComPtr<::Render::ILoader>& loader);

            void CreateBitmap(const std::wstring& path,
                              Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID2D1Bitmap>> bitmap);

        private:
            Microsoft::WRL::ComPtr<::Render::ILoader> _loader;
            std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap>> _bitmaps;
        };

        class AnimationLoader
        {
        public:
            explicit AnimationLoader(const  Dosuha::Pointer<::Animation::ILoader>& loader);

            void CreateAnimation(const std::wstring& path, Dosuha::PointerReference<Dosuha::Pointer<::Animation::IAsset>> asset);

        private:
            Dosuha::Pointer<::Animation::ILoader> _loader;
            // std::unordered_map<std::wstring, Dosuha::Pointer<::Animation::IAsset>> _assets; // TODO Share Asset
        };

    public:
        class MasterLoader
        {
        public:
            MasterLoader(const Microsoft::WRL::ComPtr<::Render::ILoader>& loader,
                         const Dosuha::Pointer<::Animation::ILoader>& animationLoader);

            void CreateBitmap(const std::wstring& path,
                              Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID2D1Bitmap>> bitmap);
            
            void CreateAnimation(const std::wstring& path, Dosuha::PointerReference<Dosuha::Pointer<::Animation::IAsset>> asset);

        private:
            BitmapLoader _bitmapLoader;
            AnimationLoader _animationLoader;
        };
    };
}
