#include "CollectibleComponent.hpp"

CollectibleComponent::CollectibleComponent(int type) {
    this->type = type;
}

CollectibleComponent::~CollectibleComponent() {}

void CollectibleComponent::Update() {}

void CollectibleComponent::Render(SDL_Renderer* ren) {}

int CollectibleComponent::GetType() {
    return type;
}
