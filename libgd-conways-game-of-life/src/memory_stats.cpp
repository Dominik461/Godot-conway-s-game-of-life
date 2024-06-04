#include "memory_stats.h"
#include <godot_cpp/classes/performance.hpp>

void MemoryStats::_bind_methods() {
}

void MemoryStats::_process(double delta) {
    double memUsage = Performance::get_singleton()->get_monitor(Performance::MEMORY_STATIC) / 3072;
    set_text("Static Mem Usage: \n" + String::num(memUsage));
}