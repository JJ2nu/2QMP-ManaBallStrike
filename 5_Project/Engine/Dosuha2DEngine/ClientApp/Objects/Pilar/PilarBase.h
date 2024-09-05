#pragma once
namespace Client::Object
{
    class PilarBase : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        PilarBase(Engine::Math::Vector2 _location);
        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;

        void OnBlock(std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold);
        void OnPostUpdate(float d1, float d2) override;

	protected:
		std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::AlphaBitmap> _pilarBitmap;

        std::shared_ptr<Engine::Component::Collider::Box> _colliderVertical;
        std::shared_ptr<Engine::Component::Collider::Box> _colliderHorizontal;
        
        std::shared_ptr<Engine::Component::Collider::Box> _opacityColliderH;
        std::shared_ptr<Engine::Component::Collider::Box> _opacityColliderV;

        size_t overlapCnt = 0;


        std::shared_ptr<Engine::Component::Shadow> _shadowVertical;
        std::shared_ptr<Engine::Component::Shadow> _shadowHorizontal;

        bool once = true;
        bool isPointPilar = false;
        Engine::Math::Vector2 location;

        std::wstring _bitmapPath;
    };

    class PointPilar : public PilarBase
    {
    public:
        PointPilar(Engine::Math::Vector2 _location );


    protected:
        void OnSetup() override;
    };


    class RightTopCornerPilarHorizontal : public PilarBase
    {
    public:
        RightTopCornerPilarHorizontal(Engine::Math::Vector2 _location);


    protected:
        void OnSetup() override;
    };

    class RightTopCornerPilarVertical : public PilarBase
    {
    public:
        RightTopCornerPilarVertical(Engine::Math::Vector2 _location);


    protected:
        void OnSetup() override;
    };

    class LeftTopCornerPilarHorizontal : public PilarBase
    {
    public:
        LeftTopCornerPilarHorizontal(Engine::Math::Vector2 _location);


    protected:
        void OnSetup() override;
    };

    class LeftTopCornerPilarVertical : public PilarBase
    {
    public:
        LeftTopCornerPilarVertical(Engine::Math::Vector2 _location);


    protected:
        void OnSetup() override;
    };

    class RightBottomCornerPilar : public PilarBase
    {
    public:
        RightBottomCornerPilar(Engine::Math::Vector2 _location );


    protected:
        void OnSetup() override;
    };

    class LeftBottomCornerPilar : public PilarBase
    {
    public:
        LeftBottomCornerPilar(Engine::Math::Vector2 _location );


    protected:
        void OnSetup() override;
    };





}