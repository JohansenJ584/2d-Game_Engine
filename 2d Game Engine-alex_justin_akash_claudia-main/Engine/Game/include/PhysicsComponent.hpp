#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
 * Handles position, velocity, and gravity.
 */
class PhysicsComponent : public Component {
    public:
        /*!
         * Constructs a physics component to act of the given transform component.
         * By default, gravity will affect it.
         */
        PhysicsComponent(TransformComponent* transform);

        /*!
         * Pass false to disable gravity acting on the transform.
         */
        PhysicsComponent(TransformComponent* transform, bool do_gravity);

        /*!
         * Destructor is empty, has no resources to free.
         */
        ~PhysicsComponent();

        /*!
         * Applies the physics to the transform.
         * Updates position based on velocity, and velocity based on gravity (if enabled).
         */
        void Update();

        /*!
         * Nothing to render.
         */
        void Render(SDL_Renderer* renderer);

    private:
        /*!
         * The transform component on which the physics will act.
         */
        TransformComponent* transform;

        /*!
         * Whether gravity should be applied to the transform.
         */
        bool do_gravity;
};
#endif
