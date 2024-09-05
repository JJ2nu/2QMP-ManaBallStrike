#include "pch.h"
#include "TestWorld.h"

#include "../../Objects/Player/ControlPlayer.h"
#include "../../Objects/Background/Background.h"

Client::World::TestWorld::TestWorld()
{
}

void Client::World::TestWorld::OnCreateObject()
{
    CreateObject<Object::Background>();
    // CreateObject<Object::Player>();
}
