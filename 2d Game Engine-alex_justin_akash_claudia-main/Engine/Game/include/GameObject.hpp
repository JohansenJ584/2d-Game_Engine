#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SDL2/SDL.h>

#include <vector>
#include <algorithm>

#include "Component.hpp"
#include "ControllerComponent.hpp"
#include "TileMap.hpp"

/*!
 A game object.
 */
class GameObject {
    public:
        /*!
        Constructor.
        */
        GameObject();

        /*!
         Destructor.
         */
        ~GameObject();

        /*!
            Gives inputs to any components of this game object that require input.
        */
        void Input(SDL_Event e);

        /*!
            Updates any components of this game object that require updating.
        */
        bool Update();

        /*!
            Renders any components of this game object that requires rendering.
        */
        void Render(SDL_Renderer* renderer);

        /*!
        Adds a component to this game object.
        */
        void AddComponent(Component* c);

        /*!
        Removes a component from this game object.
        */
        void RemoveComponent();

        // private: JUST FOR TESTING FOR NOW
        // Points to all the components of this game object.
        std::vector<Component*> m_components;
};

#endif
