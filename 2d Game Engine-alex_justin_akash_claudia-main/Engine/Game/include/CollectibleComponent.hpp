#ifndef COLLECTIBLE_COMPONENT_HPP
#define COLLECTIBLE_COMPONENT_HPP

#include "Component.hpp"

/*!
 A component to mark an object as a collectible.
 */
class CollectibleComponent: public Component {
    public:
        /*!
        *  Default constructor.
        */
        CollectibleComponent(int type);

        /*!
            Destructor.
        */
        ~CollectibleComponent();

        /*!
            Empty method. This component does not need to be updated.
        */
        virtual void Update();

        /*!
            Empty method. This component does not need to be rendered.
        */
        virtual void Render(SDL_Renderer* ren);

        /*!
            Gets the type of this game object.
        */
        int GetType();

    private:
        // The type of object.
        int type;
};

#endif
