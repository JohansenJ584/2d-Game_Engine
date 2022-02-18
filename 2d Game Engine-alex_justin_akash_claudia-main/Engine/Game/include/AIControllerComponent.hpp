#ifndef AI_CONTROLLER_COMPONENT_HPP
#define AI_CONTROLLER_COMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
 A component to give a game object artificial intelligence.
 */
class AIControllerComponent : public Component {
    public:
        /*!
        *  Default constructor. The transform keeps track of position.
        */
        AIControllerComponent(TransformComponent* transform);

        /*!
        *  Constructor that takes in a transform and a radius.
        *  Radius is the distance enemies will walk from their current position.
        *  Type is the kind of enemy this component represents.
        */
        AIControllerComponent(TransformComponent* transform, int radius, int type);

        /*!
            Destructor.
        */
        ~AIControllerComponent();

        /*!
            Performs AI operations, like determining the direction the enemy should move,
        */
        virtual void Update();

        /*!
            Empty method. This component does not need to be rendered.
        */
        virtual void Render(SDL_Renderer* renderer);

        /*!
            Gets the type of this game object.
        */
        int GetType();

        /*!
            Gets the start position of this game object.
        */
        std::pair<double, double> GetStartPosition();

        /*!
            Gets the radius of this game object.
        */
        int GetRadius();

    private:
         // Points to the transform of the game object this component is attached to.
         TransformComponent* transform;

         // Used to calculate the minX and maxX
         int radius;

         // The minimum and maximum distance that this game object may travel.
         int minX, maxX;

         // The speed of this game object.
         int speed = 1;

         // Determines if this game object is moving left or right.
         bool movingRight;

         // The type of enemy.
         int type;
};

#endif
