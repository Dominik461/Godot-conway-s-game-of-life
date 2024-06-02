
#ifndef GAME_OF_LIFE_CLASS_H
#define GAME_OF_LIFE_CLASS_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;

class GameOfLife : public Node2D
{
    GDCLASS(GameOfLife, Node2D);

protected:

    static void _bind_methods();

public:

    GameOfLife();
    ~GameOfLife();

};

#endif 