#include "TransformComponent.hpp"

TransformComponent::TransformComponent(): Component() {
    // printf("Sprite Transform Address %p\n", (void*)this);
    posx = 0.0;
    posy = 0.0;
    velx = 0.0;
    vely = 0.0;
}

TransformComponent::~TransformComponent() {}

std::pair<double, double> TransformComponent::GetPosition() {
    return (std::pair<double, double>(posx, posy));
}
std::pair<double, double> TransformComponent::GetVelocity() {
    return (std::pair<double, double>(velx, vely));
}

void TransformComponent::SetPosition(double x, double y) {
    posx = x;
    posy = y;
}
void TransformComponent::SetVelocity(double x, double y) {
    velx = x;
    vely = y;
}

void TransformComponent::SetVelocityX(double x) {
    velx = x;
}

void TransformComponent::SetVelocityY(double y) {
    vely = y;
}

void TransformComponent::SetWidth(int w) {
    width = w;
}

void TransformComponent::SetHeight(int h) {
    height = h;
}

void TransformComponent::Update() {}

void TransformComponent::Render(SDL_Renderer* renderer) {}

std::pair<int, int> TransformComponent::GetDimensions() {
    return std::pair<int, int>(width, height);
}
