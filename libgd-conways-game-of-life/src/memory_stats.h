#ifndef MEMORYSTATS_H
#define MEMORYSTATS_H

#include <godot_cpp/classes/label.hpp>


using namespace godot;

class MemoryStats : public Label {
    GDCLASS(MemoryStats, Label);

protected:
    static void _bind_methods();
    
public:

    void _process(double delta) override;
};

#endif // MEMORYSTATS_H
