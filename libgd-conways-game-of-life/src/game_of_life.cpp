#include "game_of_life.h"
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/timer.hpp>

void GameOfLife::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_cell_pressed", "x", "y"), &GameOfLife::_on_cell_pressed);
    ClassDB::bind_method(D_METHOD("_on_start_pressed"), &GameOfLife::_on_start_pressed);  
    ClassDB::bind_method(D_METHOD("_on_reset_pressed"), &GameOfLife::_on_reset_pressed);
    ClassDB::bind_method(D_METHOD("_on_tick_timeout"), &GameOfLife::_on_tick_timeout);
}

void GameOfLife::_ready() {

    Timer* timer = get_node<Timer>("TickTimer");
    timer->stop();

    grid_size = Vector2i(20, 20);
    cell_size = Vector2i(20, 20);

    GridContainer *grid_container = Object::cast_to<GridContainer>(get_node<GridContainer>("GridContainer"));

    grid_container->set_columns(grid_size.x);
    grid_container->set_custom_minimum_size(grid_size * cell_size);

    for (int y = 0; y < grid_size.y; ++y) {
        Array row;
        for (int x = 0; x < grid_size.x; ++x) {
            Cell *cell = memnew(Cell);
            cell->set_custom_minimum_size(cell_size);
            cell->set_size(cell_size);
            grid_container->add_child(cell);
            row.append(cell);
        }
        cells.append(row);
    }

    Button *start_button = Object::cast_to<Button>(get_node<Button>("StartButton"));
    start_button->connect("pressed", Callable(this, "_on_start_pressed"));

    Button *reset_button = Object::cast_to<Button>(get_node<Button>("ResetButton"));
    reset_button->connect("pressed", Callable(this, "_on_reset_pressed"));

    timer->connect("timeout", Callable(this, "_on_tick_timeout"));
    timer->set_wait_time(tickRate);

}

void GameOfLife::_on_start_pressed() {
    Timer* timer = get_node<Timer>("TickTimer");
    timer->start();
}

void GameOfLife::_on_reset_pressed() {
    Timer* timer = get_node<Timer>("TickTimer");
    timer->stop();
    for (int y = 0; y < grid_size.y; ++y) {
        for (int x = 0; x < grid_size.x; ++x) {
            Cell* cell = Object::cast_to<Cell>(&cells[y][x]);
            cell->is_alive = false;
            cell->update_visuals(); 
        }
    }

}

void GameOfLife::_on_tick_timeout() {

    Array new_states;
    for (int y = 0; y < grid_size.y; ++y) {
        Array new_row;
        for (int x = 0; x < grid_size.x; ++x) {
            int alive_neighbors = count_alive_neighbors(x, y);
            Cell *cell = Object::cast_to<Cell>(&cells[y][x]);
            if (cell->get_alive()) {
                if (alive_neighbors < 2 || alive_neighbors > 3) {
                    new_row.append(false);
                } else {
                    new_row.append(true);
                }
            } else {
                if (alive_neighbors == 3) {
                    new_row.append(true);
                } else {
                    new_row.append(false);
                }
            }
        }
        new_states.append(new_row);
    }

    for (int y = 0; y < grid_size.y; ++y) {
        for (int x = 0; x < grid_size.x; ++x) {
            Cell *cell = Object::cast_to<Cell>(&cells[y][x]);
            cell->set_alive(&new_states[y][x]);
            cell->update_visuals();
        }
    }

}