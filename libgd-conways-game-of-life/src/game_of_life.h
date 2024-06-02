
#ifndef GAME_OF_LIFE_CLASS_H
#define GAME_OF_LIFE_CLASS_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include "cell.h"

using namespace godot;

class GameOfLife : public Node2D {
    GDCLASS(GameOfLife, Node2D);

private:
    Vector2i grid_size;
    Vector2i cell_size;
    Array cells;
    float tickRate = 1.0f;


protected:
    static void _bind_methods();

public:
    void _ready();

    void _on_start_pressed();
    void _on_reset_pressed();
    void _on_tick_timeout();

    int count_alive_neighbors(int x, int y);
};

#endif 