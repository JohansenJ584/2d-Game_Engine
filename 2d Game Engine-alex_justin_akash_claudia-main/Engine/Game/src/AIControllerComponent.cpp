#include "AIControllerComponent.hpp"

AIControllerComponent::AIControllerComponent(TransformComponent* transform) {
    this->transform = transform;
}

AIControllerComponent::AIControllerComponent(TransformComponent* transform, int radius, int type) : AIControllerComponent(transform) {
    std::pair<double, double> cur_pos = this->transform->GetPosition();
    this->radius = radius;
    this->minX = cur_pos.first - radius;
    this->maxX = cur_pos.first + radius;
    this->movingRight = true;
    this->type = type;
    // printf("Created Enemy AI. Pos: (%d, %d) Max: %d, Min:%d\n", cur_pos.first, cur_pos.second, maxX, minX);
}

AIControllerComponent::~AIControllerComponent() {
    transform = nullptr;
}

void AIControllerComponent::Update() {
    std::pair<double, double> cur_pos = transform->GetPosition();
    if (movingRight) {
        if (cur_pos.first + speed > maxX) {
            movingRight = false;
            transform->SetVelocityX(-1 * speed);
        }
        else {
            transform->SetVelocityX(speed);
        }
    }
    else {
        // Character is moving left
        if (cur_pos.first - speed < minX) {
            movingRight = true;
            transform->SetVelocityX(speed);
        }
        else {
            transform->SetVelocityX(-1 * speed);
        }
    }
}

void AIControllerComponent::Render(SDL_Renderer* renderer) {}

int AIControllerComponent::GetType() {
    return type;
}

std::pair<double, double> AIControllerComponent::GetStartPosition() {
    std::pair<double, double> start = transform->GetPosition();
    start.first = minX + radius;
    return start;
}

int AIControllerComponent::GetRadius() {
    return radius;
}
