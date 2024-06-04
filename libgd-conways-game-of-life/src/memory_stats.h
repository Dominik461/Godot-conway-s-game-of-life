#ifndef MEMORYSTATS_H
#define MEMORYSTATS_H

#include <godot_cpp/classes/node2d.hpp>


using namespace godot;

class MemoryStats : public Node2D {
    GDCLASS(MemoryStats, Node2D);

protected:
    static void _bind_methods();
    
public:

    void _process(double delta) override;
};

#endif // MEMORYSTATS_H
