#ifndef CONTROLLER_COMPONENT_HPP
#define CONTROLLER_COMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
 A component to give a game object controls.
 */
class ControllerComponent : public Component {
    public:
        /*!
        Constructor.
        */
        ControllerComponent(TransformComponent* transform);

        /*!
         Destructor.
         */
        ~ControllerComponent();

        /*!
         Does nothing.
         */
        virtual void Update();

        /*!
         Does nothing.
         */
        virtual void Render(SDL_Renderer* renderer);

        /*!
         Checks for input and updates accordingly.
         */
        void Input(SDL_Event e);

    private:
        // Points to the transform of the game object this component is attached to.
        TransformComponent* transform;

        // Stores the buttons that are pressed by the player.
        bool buttons[3];

        // The speed of the game object this component is attached to.
        int speed = 5;
};

#endif
