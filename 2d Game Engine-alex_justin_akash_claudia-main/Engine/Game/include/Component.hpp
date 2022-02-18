#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SDL2/SDL.h>
#include <utility>

/*!
    An abstract class that represents any Component that a GameObject may have.
*/
class Component {
    public:
        /*!
            Default constructor. Should never be called directly.
        */
        Component();

        /*!
            Pure virtual Destructor.
        */
        virtual ~Component() = 0;

        /*!
            Pure virtual Update Method. Performs any updates needed to this component each frame.
        */
        virtual void Update() = 0;

        /*!
            Pure virtual Render Method.
            Renderer is the game's renderer.
            Renders the Component if there is a visual component.
        */
        virtual void Render(SDL_Renderer* renderer) = 0;
};

#endif
