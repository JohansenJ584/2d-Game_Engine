#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include "Component.hpp"

/*!
 * A component to give a game object the ability to transform.
 */
class TransformComponent : public Component {
    public:
        /*!
        * Constructor.
        */
        TransformComponent();

        /*!
        * Destructor.
        */
        ~TransformComponent();

        /*!
        * Updates the position and velocity of the game object this component is attached to.
        */
        virtual void Update();

        /*!
        * Does nothing.
        */
        virtual void Render(SDL_Renderer* renderer);

        static const int hash = 10;
        /*!
        * Gets the position of the game object this component is attached to.
        */
        std::pair<double, double> GetPosition();

        /*!
        * Gets the velocity of the game object this component is attached to.
        */
        std::pair<double, double> GetVelocity();

        /*!
        *  Gets the dimensions of the game object this component is attached to.
        */
        std::pair<int, int> GetDimensions();

        /*!
        * Sets the position of the game object this component is attached to.
        */
        void SetPosition(double x, double y);

        /*!
        * Sets the velocity of the game object this component is attached to.
        */
        void SetVelocity(double x, double y);

        /*!
        * Sets the x velocity of the game object this component is attached to.
        */
        void SetVelocityX(double x);

        /*!
        * Sets the y velocity of the game object this component is attached to.
        */
        void SetVelocityY(double y);

        /*!
        * Sets the width of the game object this component is attached to.
        */
        void SetWidth(int w);

        /*!
        * Sets the height of the game object this component is attached to.
        */
        void SetHeight(int h);

    private:
        /*!
        * Stores the position of the game object this component is attached to.
        */
        double posx, posy;

        /*!
        * Stores the velocity of the game object this component is attached to.
        */
        double velx, vely;

        /*!
        * Stores the dimensions of the game object this component is attached to.
        */
        int width, height;
};

#endif
