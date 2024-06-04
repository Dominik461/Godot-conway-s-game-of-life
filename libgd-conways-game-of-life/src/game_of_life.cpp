#include "game_of_life.h"
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/option_button.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include "godot_cpp/classes/engine.hpp"

void GameOfLife::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_start_pressed"), &GameOfLife::_on_start_pressed);  
    ClassDB::bind_method(D_METHOD("_on_reset_pressed"), &GameOfLife::_on_reset_pressed);
    ClassDB::bind_method(D_METHOD("_on_tick_timeout"), &GameOfLife::_on_tick_timeout);
    ClassDB::bind_method(D_METHOD("_on_pattern_selected", "index"), &GameOfLife::_on_pattern_selected);

}

void GameOfLife::_ready() {
    
    if (Engine::get_singleton()->is_editor_hint()) return;

    Timer* timer = get_node<Timer>("../TickTimer");
    timer->stop();

    grid_size = Vector2i(70, 42);
    cell_size = Vector2i(15, 15);

    GridContainer *grid_container = Object::cast_to<GridContainer>(get_node<GridContainer>("../GridContainer"));

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

    Button *start_button = Object::cast_to<Button>(get_node<Button>("../StartButton"));
    start_button->connect("pressed", Callable(this, "_on_start_pressed"));

    Button *reset_button = Object::cast_to<Button>(get_node<Button>("../ResetButton"));
    reset_button->connect("pressed", Callable(this, "_on_reset_pressed"));

    OptionButton *pattern_button = Object::cast_to<OptionButton>(get_node<OptionButton>("../PatternOptionButton"));
    pattern_button->connect("item_selected", Callable(this, "_on_pattern_selected"));
    
    //if(pattern_button != nullptr)
    //{
    //    pattern_button->add_item("Clear");
    //    pattern_button->add_item("Pattern 1");
    //    pattern_button->add_item("Pattern 2"); 
    //}


    timer->connect("timeout", Callable(this, "_on_tick_timeout"));
    timer->set_wait_time(tickRate);

}

void GameOfLife::_on_start_pressed() {
    Timer* timer = get_node<Timer>("../TickTimer");
    timer->start();
}

void GameOfLife::_on_reset_pressed() {
    Timer* timer = get_node<Timer>("../TickTimer");
    timer->stop();
    for (int y = 0; y < grid_size.y; ++y) {
        for (int x = 0; x < grid_size.x; ++x) {
            Array& row = (Array) cells[y];
            Cell *cell = Object::cast_to<Cell>(row[x]);
            cell->is_alive = false;
            cell->update_visuals(); 
        }
    }

}

void GameOfLife::_on_pattern_selected(int index) {
    clear_grid();
    switch (index) {
        case 0:  // Clear
            break;
        case 1:  // Pattern 1
            set_pattern1();
            break;
        case 2:  // Pattern 2
            set_pattern2();
            break;
    }
}

void GameOfLife::clear_grid() {
    for (int y = 0; y < grid_size.y; ++y) {
        for (int x = 0; x < grid_size.x; ++x) {
            Array& row = (Array) cells[y];
            Cell *cell = Object::cast_to<Cell>(row[x]);
            cell->is_alive = false;
            cell->update_visuals(); 
        }
    }
}

void GameOfLife::set_pattern1() {
    // Define your pattern 1 here
    std::vector<std::vector<int>> pattern = {
		{0, 0, 1, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1}
    };
    set_pattern(pattern, 32, 20);  // Place pattern at (5, 5)
}

void GameOfLife::set_pattern2() {
    // Define your pattern 2 here
    std::vector<std::vector<int>> pattern = {
		{0, 1, 1, 0, 0, 1, 1, 0},
		{1, 0, 0, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{0, 1, 0, 0, 0, 0, 1, 0},
		{0, 0, 1, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0}
    };
    set_pattern(pattern, 32, 20);  // Place pattern at (10, 10)
}

void GameOfLife::set_pattern(const std::vector<std::vector<int>>& pattern, int offset_x, int offset_y) {
    for (size_t y = 0; y < pattern.size(); ++y) {
        for (size_t x = 0; x < pattern[y].size(); ++x) {
            if (y + offset_y < grid_size.y && x + offset_x < grid_size.x) {
                Array& row = (Array) cells[y+offset_y];
                Cell *cell = Object::cast_to<Cell>(row[x+offset_x]);
                if (cell) {
                    cell->set_alive(pattern[y][x] == 1);
                }
            }
        }
    }
}

int GameOfLife::count_alive_neighbors(int x, int y) {
    
    int alive_neighbors = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < grid_size.x && ny >= 0 && ny < grid_size.y) {
                    Array& row = (Array) cells[ny];
                    Cell *neighbor = Object::cast_to<Cell>(row[nx]);
                    
                    if (neighbor->get_alive()) {
                        alive_neighbors++;
                    }
                }
            }
        }
        return alive_neighbors;
    
}

void GameOfLife::_on_tick_timeout() {
    
    if (Engine::get_singleton()->is_editor_hint()) return;

    int64_t  start_time = Time::get_singleton()->get_unix_time_from_system() * 1000;
    UtilityFunctions::print(start_time);

    Array new_states;
    for (int y = 0; y < grid_size.y; ++y) {
        Array new_row;
        for (int x = 0; x < grid_size.x; ++x) {
            int alive_neighbors = count_alive_neighbors(x, y);
            Array& row = (Array) cells[y];
            Cell *cell = Object::cast_to<Cell>(row[x]);
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
            Array& row = (Array) cells[y];
            Cell *cell = Object::cast_to<Cell>(row[x]);  

            Array& newStates = (Array) new_states[y];
            bool newState = (bool) newStates[x];
            cell->set_alive(newState);
            cell->update_visuals();
        }
    }
    int64_t  end_time = Time::get_singleton()->get_unix_time_from_system() * 1000;
    Label *updateCycleLabel = Object::cast_to<Label>(get_node<Label>("../UpdateCycleLabel"));
    updateCycleLabel->set_text("Update Cycle Duration: \n" + String::num_int64(end_time - start_time) + "ms");
    UtilityFunctions::print(end_time);
    UtilityFunctions::print("GDExtension Update Cycle Duration: " + String::num_int64(end_time - start_time) + "ms");
}