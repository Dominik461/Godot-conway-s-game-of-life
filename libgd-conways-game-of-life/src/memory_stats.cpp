#include "memory_stats.h"
#include <godot_cpp/classes/performance.hpp>
#include <godot_cpp/classes/engine.hpp> 

void MemoryStats::_bind_methods() {
}

void MemoryStats::_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint()) return;
        set_text("Static Mem Usage: \n" + String::num(Performance::get_singleton()->get_monitor(Performance::MEMORY_STATIC) * (pow(10, -6))) + " MB");
}