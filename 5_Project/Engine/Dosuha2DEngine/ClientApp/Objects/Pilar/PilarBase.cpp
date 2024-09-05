#include "pch.h"
#include "PilarBase.h"

Client::Object::PilarBase::PilarBase(Engine::Math::Vector2 _location)
{
	location = _location;
	AddTag(L"Bouncing");
	AddTag(L"Wall");
	// AddTag(L"Pilar");
}

const Engine::Math::Rect& Client::Object::PilarBase::GetBound() const
{
	return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::PilarBase::GetColliders() const
{
	if (isPointPilar)
		return { _colliderHorizontal , _opacityColliderH};
	else
		return { _colliderHorizontal,_colliderVertical , _opacityColliderH , _opacityColliderV };
}

void Client::Object::PilarBase::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_pilarBitmap = CreateComponent < Engine::Component::AlphaBitmap>(_bitmapPath);
	_pilarBitmap->SetParentScene(_rootScene);

	_colliderHorizontal = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Block);
	_colliderHorizontal->SetParentScene(_rootScene);
	_colliderVertical = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Block);
	_colliderVertical->SetParentScene(_rootScene);
	
	_opacityColliderH = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Overlap);
	_opacityColliderH->SetParentScene(_rootScene);
	_opacityColliderV = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Overlap);
	_opacityColliderV->SetParentScene(_rootScene);

	_shadowHorizontal = CreateComponent<Engine::Component::Shadow>(Engine::Component::ShadowType::Box);
	_shadowHorizontal->SetParentScene(_rootScene);

	if (!isPointPilar)
	{
		_shadowVertical = CreateComponent<Engine::Component::Shadow>(Engine::Component::ShadowType::Box);
		_shadowVertical->SetParentScene(_rootScene);
	}

}

void Client::Object::PilarBase::OnSetup()
{
	overlapCnt = 0;
	_pilarBitmap->SetOpacity(1.0f);
	_rootScene.lock()->SetScale({0.8f,0.8f});
	_rootScene.lock()->SetLocation(location);
	_boundComponent->SetSize(_pilarBitmap->GetSize());
	_colliderHorizontal->BindOnBlock([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			OnBlock(other, manifold);
		});

	_colliderVertical->BindOnBlock([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			OnBlock(other, manifold);
		});


	//_boundComponent->DrawBound();
	//_colliderHorizontal->DrawCollider();
	//_colliderVertical->DrawCollider();	
	//_opacityColliderH->DrawCollider();
	//_opacityColliderV->DrawCollider();

}

void Client::Object::PilarBase::OnBlock(std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
{
}

void Client::Object::PilarBase::OnPostUpdate(float d1, float d2)
{
	_shadowHorizontal->AddShadow();
	if(!isPointPilar)
		_shadowVertical->AddShadow();
}
//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//============

Client::Object::PointPilar::PointPilar(Engine::Math::Vector2 _location)
	:PilarBase(_location)
{
	isPointPilar = true;
	_bitmapPath = L"Resources/Sprites/Object/Pilar/object_006_1.png";
}

void Client::Object::PointPilar::OnSetup()
{
	PilarBase::OnSetup();
	_opacityColliderH->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt++;
			if (overlapCnt !=1) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_opacityColliderH->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt--;
			if (overlapCnt != 1) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_colliderHorizontal->SetSize({ 105,105 });
	_colliderHorizontal->SetLocation({ 0,40 });

	_opacityColliderH->SetSize({ 120,155 });
	_opacityColliderH->SetLocation({ 0,-70 });

	_shadowHorizontal->SetSize({ 100,100 });
	_shadowHorizontal->SetLocation({ 0,80 });

	_colliderVertical->Deactivate();
	_opacityColliderV->Deactivate();
	_renderOrder = _rootScene.lock()->GetLocation().y+20;


}
//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//============

Client::Object::LeftTopCornerPilarHorizontal::LeftTopCornerPilarHorizontal(Engine::Math::Vector2 _location)
	:PilarBase(_location)
{
         	_bitmapPath = L"Resources/Sprites/Object/Pilar/object_006_3_1.png";
	isPointPilar = false;
	AddTag(L"LeftTop");
}

void Client::Object::LeftTopCornerPilarHorizontal::OnSetup()
{
	PilarBase::OnSetup();
	_opacityColliderH->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_opacityColliderH->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_colliderHorizontal->SetSize({ 200,72 });
	_colliderHorizontal->SetLocation({ 0,-48 });

	_opacityColliderH->SetSize({ 200,72 });
	_opacityColliderH->SetLocation({ 0,-130 });

	_shadowHorizontal->SetSize({ 187,53 });
	_shadowHorizontal->SetLocation({ 0,-12 });

	_shadowVertical->SetSize({ 53,193 });
	_shadowVertical->SetLocation({ -67,58 });

	_colliderVertical->Deactivate();
	_opacityColliderV->Deactivate();
	_renderOrder = _rootScene.lock()->GetLocation().y - 40;


}
//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//============
Client::Object::LeftTopCornerPilarVertical::LeftTopCornerPilarVertical(Engine::Math::Vector2 _location)
	:PilarBase(_location)
{
	_bitmapPath = L"Resources/Sprites/Object/Pilar/object_006_3_2.png";
	isPointPilar = false;
	AddTag(L"LeftTop");
}

void Client::Object::LeftTopCornerPilarVertical::OnSetup()
{
	PilarBase::OnSetup();
	_opacityColliderH->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_opacityColliderH->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_colliderVertical->SetSize({ 72,193 });
	_colliderVertical->SetLocation({ -67,13 });

	_opacityColliderH->SetSize({ 200,72 });
	_opacityColliderH->SetLocation({ 0,-130 });

	_shadowHorizontal->SetSize({ 187,53 });
	_shadowHorizontal->SetLocation({ 0,-12 });

	_shadowVertical->SetSize({ 53,193 });
	_shadowVertical->SetLocation({ -67,58 });

	_colliderHorizontal->Deactivate();
	_opacityColliderV->Deactivate();
	_renderOrder = _rootScene.lock()->GetLocation().y - 40;


}
//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//============

Client::Object::RightTopCornerPilarHorizontal::RightTopCornerPilarHorizontal(Engine::Math::Vector2 _location)
	:PilarBase(_location)
{
	_bitmapPath = L"Resources/Sprites/Object/Pilar/object_006_2_1.png";
	isPointPilar = false;
	AddTag(L"RightTop");
}

void Client::Object::RightTopCornerPilarHorizontal::OnSetup()
{
	PilarBase::OnSetup();

	_opacityColliderH->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_opacityColliderH->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_colliderHorizontal->SetSize({ 200,72 });
	_colliderHorizontal->SetLocation({ 0,-48 });

	_opacityColliderH->SetSize({ 200,72 });
	_opacityColliderH->SetLocation({ 0,-130 });

	_shadowHorizontal->SetSize({ 187,53 });
	_shadowHorizontal->SetLocation({ 0,-12 });

	_shadowVertical->SetSize({ 53,193 });
	_shadowVertical->SetLocation({ 67,58 });

	_colliderVertical->Deactivate();
	_opacityColliderV->Deactivate();
	_renderOrder = _rootScene.lock()->GetLocation().y - 40;

}
//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//============

Client::Object::RightTopCornerPilarVertical::RightTopCornerPilarVertical(Engine::Math::Vector2 _location)
	:PilarBase(_location)
{
	_bitmapPath = L"Resources/Sprites/Object/Pilar/object_006_2_2.png";
	isPointPilar = false;
	AddTag(L"RightTop");
}

void Client::Object::RightTopCornerPilarVertical::OnSetup()
{
	PilarBase::OnSetup();
	_opacityColliderH->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_opacityColliderH->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_colliderVertical->SetSize({ 72,193 });
	_colliderVertical->SetLocation({ 67,13 });

	_opacityColliderH->SetSize({ 200,72 });
	_opacityColliderH->SetLocation({ 0,-130 });

	_shadowHorizontal->SetSize({ 187,53 });
	_shadowHorizontal->SetLocation({ 0,-12 });

	_shadowVertical->SetSize({ 53,193 });
	_shadowVertical->SetLocation({ 67,58 });

	_colliderHorizontal->Deactivate();
	_opacityColliderV->Deactivate();
	_renderOrder = _rootScene.lock()->GetLocation().y - 40;
}
//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//============

Client::Object::LeftBottomCornerPilar::LeftBottomCornerPilar(Engine::Math::Vector2 _location)
	:PilarBase(_location)
{
	_bitmapPath = L"Resources/Sprites/Object/Pilar/object_006_4.png"; 
	isPointPilar = false;
}

void Client::Object::LeftBottomCornerPilar::OnSetup()
{
	PilarBase::OnSetup();
	_opacityColliderH->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_opacityColliderH->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{

			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});


	_opacityColliderV->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);

		});

	_opacityColliderV->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{

			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_colliderHorizontal->SetSize({ 200,72 });
	_colliderHorizontal->SetLocation({ 0,80 });

	_colliderVertical->SetSize({ 72,193 });
	_colliderVertical->SetLocation({ -67,18 });

	_opacityColliderH->SetSize({ 200,72 });
	_opacityColliderH->SetLocation({ 0, 10 });

	_opacityColliderV->SetSize({ 72,92 });
	_opacityColliderV->SetLocation({ -67,-120 });



	_shadowHorizontal->SetSize({ 187,53 });
	_shadowHorizontal->SetLocation({ 0,132 });

	_shadowVertical->SetSize({ 53,193 });
	_shadowVertical->SetLocation({ -67,58 });

	_renderOrder = _rootScene.lock()->GetLocation().y + 70;

}

//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//==========//============
Client::Object::RightBottomCornerPilar::RightBottomCornerPilar(Engine::Math::Vector2 _location)
	:PilarBase(_location)
{
	_bitmapPath = L"Resources/Sprites/Object/Pilar/object_006_5.png";
	isPointPilar = false;
}

void Client::Object::RightBottomCornerPilar::OnSetup()
{
	PilarBase::OnSetup();
	_opacityColliderH->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{

			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_opacityColliderH->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});


	_opacityColliderV->BindOnBeginOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{

			overlapCnt++;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);

		});

	_opacityColliderV->BindOnEndOverlap([this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{

			overlapCnt--;
			if (overlapCnt != 2) _pilarBitmap->SetOpacity(0.6f);
			else _pilarBitmap->SetOpacity(1.f);
		});

	_colliderHorizontal->SetSize({ 200,72 });
	_colliderHorizontal->SetLocation({ 0,80 });

	_colliderVertical->SetSize({ 72,193 });
	_colliderVertical->SetLocation({ 67,18 });

	_opacityColliderH->SetSize({ 200,72 });
	_opacityColliderH->SetLocation({ 0, 10 });

	_opacityColliderV->SetSize({ 72,92 });
	_opacityColliderV->SetLocation({ 67,-120 });



	_shadowHorizontal->SetSize({ 187,53 });
	_shadowHorizontal->SetLocation({ 0,132 });

	_shadowVertical->SetSize({ 53,193 });
	_shadowVertical->SetLocation({ 67,58 });

	_renderOrder = _rootScene.lock()->GetLocation().y +70;

}
