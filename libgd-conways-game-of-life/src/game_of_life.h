
#ifndef GAME_OF_LIFE_CLASS_H
#define GAME_OF_LIFE_CLASS_H

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class GameOfLife : public RefCounted
{
    GDCLASS(GameOfLife, RefCounted);

protected:

    static void _bind_methods();

public:

    GameOfLife();
    ~GameOfLife();

};

#endif 