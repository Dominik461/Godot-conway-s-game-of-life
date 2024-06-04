#ifndef CELL_H
#define CELL_H

#include <godot_cpp/classes/button.hpp>

using namespace godot;

class Cell : public Button {
    GDCLASS(Cell, Button);

protected:
    static void _bind_methods();

public:
    bool is_alive = false;

    void _ready();
    void _on_pressed();
    void update_visuals();

    void set_alive(bool p_alive);
    bool get_alive() const;
};

#endif // CELL_H
