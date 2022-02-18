#include "CollisionComponent.hpp"
#include "TransformComponent.hpp"
#include "TileMap.hpp"
#include "stdlib.h"

CollisionComponent::CollisionComponent(TransformComponent* transform, TileMap* tilemap) {
    this->transform = transform;
    this->tilemap = tilemap;
    if (tilemap == nullptr) {
        printf("tilemap is NULL\n");
    }
    tilemap->PrintMap();
}

CollisionComponent::~CollisionComponent() {}

void CollisionComponent::Update() {}

void CollisionComponent::Render(SDL_Renderer* renderer) {}

bool CollisionComponent::UpdateCollisions() {
    bool win = false;
    if (tilemap == nullptr) {
        printf("Tilemap is not initialized\n");
    }
    int rows = tilemap->GetNumRows();
    int cols = tilemap->GetNumCols();

    // Should work, could be made more efficient
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (tilemap->GetTileType(row, col) != -1) {
                int type = tilemap->GetTileType(row, col);
                if (collide(tilemap->GetTileRect(row, col), type)) {
                    win = true;
                }
            }
        }
    }
    return win;
}

double CollisionComponent::check_top(SDL_Rect tile, double posx, double posy, int width, int height) {
    if (posy + height > tile.y) {
        // transform->SetPosition(posx, tile.y - height - 2);
        transform->SetVelocityY(0);
        //SDL_Log("Top Coll");
        return tile.y - height;
    }
    return posy;
}

double CollisionComponent::check_bottom(SDL_Rect tile, double posx, double posy, int width, int height) {
    if (posy < tile.y + tile.h) {
        // transform->SetPosition(posx, tile.y + tile.h + 2);
        transform->SetVelocityY(0.05);
        return tile.y + tile.h;
    }
    return posy;
}

double CollisionComponent::check_left(SDL_Rect tile, double posx, double posy, int width, int height) {
    if (posx + (double)width >= (double)tile.x) {
        // printf("Collision with left of tile\n");
        // transform->SetPosition((double)tile.x - (double)width - 2, posy);
        transform->SetVelocityX(0);
        return tile.x - width;
    }
    return posx;
}

double CollisionComponent::check_right(SDL_Rect tile, double posx, double posy, int width, int height) {
    if (posx <= (double)tile.x + (double)tile.w) {
        // printf("Collision with right of tile\n");
        // transform->SetPosition((double)tile.x + (double)tile.w + 2, posy);
        transform->SetVelocityX(0);
        return tile.x + tile.w;
    }
    return posx;
}

bool CollisionComponent::collide(SDL_Rect tile, int type) {
    std::pair<double, double> pos(transform->GetPosition());
    std::pair<int, int> dim(transform->GetDimensions());
    double posx = pos.first;
    double posy = pos.second;
    int width = dim.first;
    int height = dim.second;
    double newx = posx;
    double newy = posy;
    bool to_return = false;
    // printf("1: posx: %f, posy: %f, tile.x: %i, tile.y %i\n", posx, posy, tile.x, tile.y);
    if (posy + height >= tile.y && posy <= tile.y + tile.h ||
            posx < tile.x + tile.w && posx + width > tile.x) { // Within the top-bottom boundary
        // printf("1: posx: %f, posy: %f, tile.x: %i, tile.y %i\n", posx, posy, tile.x, tile.y);

        int tx_midpoint = tile.x + (tile.w / 2);
        int gx_midpoint = posx + (width / 2);

        int ty_midpoint = tile.y + (tile.h / 2);
        int gy_midpoint = posy + (height / 2);

        if (gx_midpoint < tx_midpoint) { // Left of midpoint
            if (gy_midpoint < ty_midpoint) {
                // Upper left
                if (abs(tx_midpoint - gx_midpoint) < abs(ty_midpoint - gy_midpoint)) {
                    // Top
                    newy = check_top(tile, posx, posy, width, height);
                }
                else {
                    // Left
                    newx = check_left(tile, posx, posy, width, height);
                }
            }
            else {
                // Lower left
                if (abs(tx_midpoint - gx_midpoint) < abs(gy_midpoint - ty_midpoint)) {
                    // Bottom
                    newy = check_bottom(tile, posx, posy, width, height);
                }
                else {
                    // Left
                    newx = check_left(tile, posx, posy, width, height);
                }
            }
        }
        else { // Right of midpoint
            if (gy_midpoint < ty_midpoint) {
                // Upper right
                if (abs(gx_midpoint - tx_midpoint) < abs(ty_midpoint - gy_midpoint)) {
                    // Top
                    newy = check_top(tile, posx, posy, width, height);
                }
                else {
                    // Right
                    newx = check_right(tile, posx, posy, width, height);
                }
            }
            else {
                // Lower right
                if (abs(gx_midpoint - tx_midpoint) < abs(gy_midpoint - ty_midpoint)) {
                    // Bottom
                    newy = check_bottom(tile, posx, posy, width, height);
                }
                else {
                    // Right
                    newx = check_right(tile, posx, posy, width, height);
                }
            }
        }
    }
    
    if ((posx != newx || posy != newy) && type == 7) {
        to_return = true;
    }

    transform->SetPosition(newx, newy);

    return to_return;
}
