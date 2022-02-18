#include "GameObject.hpp"
#include "TileMap.hpp"
#include "CollisionComponent.hpp"

GameObject::GameObject() {}

GameObject::~GameObject() {
    m_components.clear();
}

void GameObject::Input(SDL_Event e) {
    for (std::vector<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
        ControllerComponent* cc = dynamic_cast<ControllerComponent*>(*it);
        if (cc) {
            cc->Input(e);
        }
    }
}

bool GameObject::Update() {
    // We need to grab the collision component and call Collide() after the rest of the components are updated because collisions have to be processed after movement has been done
    CollisionComponent* cc = nullptr;
    for (std::vector<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
        (*it)->Update();
        if (!cc) {
            cc = dynamic_cast<CollisionComponent*>(*it);
        }
    }
    if (cc) {
        // cc->tilemap->PrintMap();
        if(cc->UpdateCollisions()) {
            return true;
        }
    }
    return false;
}

void GameObject::Render(SDL_Renderer* renderer) {
    for (std::vector<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
        (*it)->Render(renderer);
    }
}

void GameObject::AddComponent(Component* c) {
    m_components.push_back(c);
}

void GameObject::RemoveComponent() {
    m_components.pop_back();
}

/*
void GameObject::RemoveComponent(Component c) {
    std::vector<Component>::iterator ind = GetComponentIterator(c);
    m_components.erase(ind);
}

int GameObject::GetComponentIndex(Component c) {
    int ind = -1;
    int i = 0;
    for(std::vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it, ++i) {
        if(*it == c) {
            ind = i;
        }
    }
    return ind;
}

std::vector<Component>::iterator GameObject::GetComponentIterator(Component c) {
    return std::find(m_components.begin(), m_components.end(), c);
}
*/
