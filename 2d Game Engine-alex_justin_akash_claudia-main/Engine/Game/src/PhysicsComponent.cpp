#include "PhysicsComponent.hpp"
#include "TransformComponent.hpp"

PhysicsComponent::PhysicsComponent(TransformComponent* transform) {
    this->transform = transform;
    this->do_gravity = true;
}

PhysicsComponent::PhysicsComponent(TransformComponent* transform, bool do_gravity) : PhysicsComponent(transform) {
        this->do_gravity = do_gravity;
}

PhysicsComponent::~PhysicsComponent() {}

void PhysicsComponent::Update() {
    std::pair<double, double> vel = transform->GetVelocity();
    if (do_gravity && vel.second < 8.00) {
        vel.second += .2;
        transform->SetVelocityY(vel.second);
    }
    std::pair<double, double> pos = transform->GetPosition();
    pos.first += vel.first;
    pos.second += vel.second;
    transform->SetPosition(pos.first, pos.second);
}

void PhysicsComponent::Render(SDL_Renderer* renderer) {}
