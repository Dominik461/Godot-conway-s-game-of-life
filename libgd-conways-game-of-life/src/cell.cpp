#include "cell.h"

void Cell::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_pressed"), &Cell::_on_pressed);
    ClassDB::bind_method(D_METHOD("set_alive", "alive"), &Cell::set_alive);
    ClassDB::bind_method(D_METHOD("get_alive"), &Cell::get_alive);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_alive"), "set_alive", "get_alive");
}

void Cell::_ready() {
    connect("pressed", Callable(this, "_on_pressed"));
    update_visuals();
}

void Cell::_on_pressed() {
    is_alive = !is_alive;
    update_visuals();
}

void Cell::update_visuals() {
    set_modulate(is_alive ? Color(0, 255, 0) : Color(255, 0, 0));
}

void Cell::set_alive(bool p_alive) {
    is_alive = p_alive;
    update_visuals();
}

bool Cell::get_alive() const {
    return is_alive;
}