#ifndef COLLISION_COMPONENT_HPP
#define COLLISION_COMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "TileMap.hpp"

/*!
 * Allows collision with a tilemap
 */
class CollisionComponent : public Component {
    public:
        /*!
         * Constructs a CollisionComponent to allow the given transform to collide with the given tilemap
         * @param transform
         * @param tilemap
         */
        CollisionComponent(TransformComponent* transform, TileMap* tilemap);

        /*!
         * Nothing to destruct
         */
        ~CollisionComponent();

        /*!
         * Updates the collision of the transform with any tiles in the tilemap that it might collide with
         */
        bool UpdateCollisions();

        /*!
         * Collisions are handled in other functions
         * This does nothing.
         */
        void Update();

        /*!
         * Nothing to render.
         */
        void Render(SDL_Renderer* renderer);

    private:
        /*!
         * The transform that will have collisions applied to it
         */
        TransformComponent* transform;

        /*!
         * The tilemap with which the transform will collide
         */
        TileMap* tilemap = NULL;

        /*!
         * Checks if a collision has occured between the transform and the given bounding box.
         * Updates the velocity and position of the transform accordingly.
         * @param tile the bounding box of the tile to check against
         * @return Not currently used
         */
        bool collide(SDL_Rect tile, int type);

        /*!
         * Helper for use in internal logic.
         */
        double check_top(SDL_Rect tile, double posx, double posy, int width, int height);
        /*!
         * Helper for use in internal logic.
         */
        double check_bottom(SDL_Rect tile, double posx, double posy, int width, int height);
        /*!
         * Helper for use in internal logic.
         */
        double check_left(SDL_Rect tile, double posx, double posy, int width, int height);
        /*!
         * Helper for use in internal logic.
         */
        double check_right(SDL_Rect tile, double posx, double posy, int width, int height);
};

#endif
