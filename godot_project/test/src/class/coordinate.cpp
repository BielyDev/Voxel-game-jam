#include "coordinate.h"

void Coordinate::_process(float delta) {
    godot::Object* obj = godot::ObjectDB::get_instance(node_selected_id);
    godot::Node3D* node = godot::Object::cast_to<godot::Node3D>(obj);

    if (node != nullptr) {
        set_text(godot::UtilityFunctions::str(
            "X: ", godot::String::num(node->get_global_position().x, num_real),
            " Y: ", godot::String::num(node->get_global_position().y, num_real),
            " Z: ", godot::String::num(node->get_global_position().z, num_real),
            "\nFPS: ", uint16_t(godot::Engine::get_singleton()->get_frames_per_second())
        ));
    } else {
        set_text("Null");
    }
}
