
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
    float tickRate = 0.4f;



protected:
    static void _bind_methods();

public:
    void _ready();

    void _on_start_pressed();
    void _on_reset_pressed();
    void _on_tick_timeout();

    void _on_pattern_selected(int index);
    void clear_grid();
    void set_pattern1();
    void set_pattern2();
    void set_pattern(const std::vector<std::vector<int>>& pattern, int offset_x, int offset_y);

    int count_alive_neighbors(int x, int y);
};

#endif 