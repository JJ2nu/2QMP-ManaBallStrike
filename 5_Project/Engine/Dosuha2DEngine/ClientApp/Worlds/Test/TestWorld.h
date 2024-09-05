#pragma once

namespace Client::World
{
    class TestWorld : public Engine::World
    {
    public:
        TestWorld();

    protected:
        void OnCreateObject() override;
    };
}
