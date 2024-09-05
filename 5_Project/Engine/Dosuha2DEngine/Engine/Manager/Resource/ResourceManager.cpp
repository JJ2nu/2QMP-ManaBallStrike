#include "pch.h"
#include "ResourceManager.h"

void Engine::Manager::Resource::Initialize(const Microsoft::WRL::ComPtr<::Render::ISystem>& renderSystem,
                                           const Dosuha::Pointer<::Animation::ISystem>& animationSystem)
{
    GetInstance()->_renderSystem = renderSystem;
    GetInstance()->_animationSystem = animationSystem;

    Microsoft::WRL::ComPtr<::Render::ILoader> bitmapLoader;
    GetInstance()->_renderSystem->CreateLoader(&bitmapLoader);
    Dosuha::Pointer<::Animation::ILoader> animationLoader;
    GetInstance()->_animationSystem->CreateLoader(&animationLoader);
    GetInstance()->_loader = std::make_shared<MasterLoader>(bitmapLoader, animationLoader);
}

void Engine::Manager::Resource::Finalize()
{
    GetInstance()->_loader = nullptr;
    GetInstance()->_renderSystem = nullptr;
    GetInstance()->_animationSystem = nullptr;
}

std::shared_ptr<Engine::Manager::Resource::MasterLoader> Engine::Manager::Resource::GetLoader() noexcept
{
    return GetInstance()->_loader;
}

Engine::Manager::Resource::BitmapLoader::BitmapLoader(const Microsoft::WRL::ComPtr<::Render::ILoader>& loader)
    : _loader(loader)
{
}

void Engine::Manager::Resource::BitmapLoader::CreateBitmap(const std::wstring& path,
                                                           Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<
                                                               ID2D1Bitmap>> bitmap)
{
    if (!_bitmaps.contains(path))
    {
        Microsoft::WRL::ComPtr<ID2D1Bitmap> tempBitmap;
        _loader->CreateBitmap(path, &tempBitmap);
        _bitmaps[path] = tempBitmap;
    }
    *static_cast<Microsoft::WRL::ComPtr<ID2D1Bitmap>*>(bitmap) = _bitmaps[path];
}

Engine::Manager::Resource::AnimationLoader::AnimationLoader(const Dosuha::Pointer<Animation::ILoader>& loader)
    : _loader(loader)
{
}

void Engine::Manager::Resource::AnimationLoader::CreateAnimation(const std::wstring& path,
                                                                 Dosuha::PointerReference<Dosuha::Pointer<
                                                                     Animation::IAsset>> asset)
{
    _loader->CreateAsset(path, asset);
    // TODO Share Asset;
    //if (!_assets.contains(path))
    //{
    //    Dosuha::Pointer<Animation::IAsset> tempAsset;
    //    _loader->CreateAsset(path, &tempAsset);
    //    _assets[path] = tempAsset;
    //}
    //*static_cast<Dosuha::Pointer<::Animation::IAsset>*>(asset) = _assets[path];
}


Engine::Manager::Resource::MasterLoader::MasterLoader(const Microsoft::WRL::ComPtr<::Render::ILoader>& loader,
                                                      const Dosuha::Pointer<Animation::ILoader>& animationLoader)
    : _bitmapLoader(loader), _animationLoader(animationLoader)
{
}


void Engine::Manager::Resource::MasterLoader::CreateBitmap
(const std::wstring& path, const Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID2D1Bitmap>> bitmap)
{
    _bitmapLoader.CreateBitmap(path, bitmap);
}

void Engine::Manager::Resource::MasterLoader::CreateAnimation
(const std::wstring& path, const Dosuha::PointerReference<Dosuha::Pointer<Animation::IAsset>> asset)
{
    _animationLoader.CreateAnimation(path, asset);
}
