#include <iostream>

class C_Behaviour 
{
public:
    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void PhysicsUpdate() = 0;
};

void C_Behaviour::Start() {}
void C_Behaviour::Update(float deltaTime) {}
void C_Behaviour::PhysicsUpdate() {}