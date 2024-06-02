#include "game_of_life.h"
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/array.hpp>

void MainScene::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_cell_pressed", "x", "y"), &MainScene::_on_cell_pressed);
    ClassDB::bind_method(D_METHOD("_on_start_pressed"), &MainScene::_on_start_pressed);
    ClassDB::bind_method(D_METHOD(D_METHOD("_on_reset_pressed")), &MainScene::_on_reset_pressed);
}

void MainScene::_ready() {
    grid_size = Vector2i(100, 50);
    cell_size = Vector2i(5, 5);

    GridContainer *grid_container = Object::cast_to<GridContainer>(get_node("GridContainer"));
    grid_container->set_columns(grid_size.x);
    grid_container->set_min_size(grid_size * cell_size);

    for (int y = 0; y < grid_size.y; ++y) {
        Array row;
        for (int x = 0; x < grid_size.x; ++x) {
            Cell *cell = memnew(Cell);
            cell->set_min_size(cell_size);
            cell->set_size(cell_size);
            cell->connect("pressed", Callable(this, "_on_cell_pressed"), varray(x, y));
            grid_container->add_child(cell);
            row.append(cell);
        }
        cells.append(row);
    }

    Button *start_button = Object::cast_to<Button>(get_node("StartButton"));
    start_button->connect("pressed", Callable(this, "_on_start_pressed"));

    Button *reset_button = Object::cast_to<Button>(get_node("ResetButton"));
    reset_button->connect("pressed", Callable(this, "_on_reset_pressed"));
}

void MainScene::_on_cell_pressed(int x, int y) {
    Cell *cell = Object::cast_to<Cell>(cells[y][x]);
    cell->set_alive(!cell->get_alive());
}

void MainScene::_on_start_pressed() {
    set_process(true);
}

void MainScene::_on_reset_pressed() {
    set_process(false);
    for (int y = 0; y < grid_size.y; ++y) {
        for (int x = 0; x < grid_size.x; ++x) {
            Cell *cell = Object::cast_to<Cell>(cells[y][x]);