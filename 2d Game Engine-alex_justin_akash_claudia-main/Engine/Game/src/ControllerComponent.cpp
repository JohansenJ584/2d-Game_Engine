#include "ControllerComponent.hpp"
#include "AudioManager.hpp"
#include "stdlib.h"

ControllerComponent::ControllerComponent(TransformComponent* transform) : Component() {
    this->transform = transform;
    // printf("Controller Transform Address %p\n", (void*)transform);
    buttons[0] = false;
    buttons[1] = false;
    buttons[2] = false;
}

ControllerComponent::~ControllerComponent() {
    transform = nullptr;
}

void ControllerComponent::Input(SDL_Event e) {
    const Uint8* key_states = SDL_GetKeyboardState(NULL);

    if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT]) {
        transform->SetVelocityX(-1 * speed);
    }
    else if (key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT]) {
        transform->SetVelocityX(speed);
    }
    else {
        transform->SetVelocityX(0.0);
    }

    if (key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_UP] || key_states[SDL_SCANCODE_SPACE]) {
        std::pair<double, double> vel = transform->GetVelocity();
        if (vel.second == 0.0) {
            transform->SetVelocityY(-8.0);
            transform->SetPosition(transform->GetPosition().first, transform->GetPosition().second + 1);
            AudioManager::GetInstance()->Play(1);
        }
    }
}

void ControllerComponent::Update() {}

void ControllerComponent::Render(SDL_Renderer* renderer) {}
