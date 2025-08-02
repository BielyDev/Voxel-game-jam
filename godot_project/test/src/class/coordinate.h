#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object_id.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

class Coordinate : public godot::Label {
    GDCLASS(Coordinate, godot::Label)

public:
    godot::ObjectID node_selected_id;
    uint8_t num_real = 2;

    void _process(float delta);

    void set_node(godot::Node3D* node) {
        if (node) {node_selected_id = node->get_instance_id();}
        else {node_selected_id = godot::ObjectID();}
    }
    godot::Node3D* get_node() const {
        godot::Object* obj = godot::ObjectDB::get_instance(node_selected_id);
        return godot::Object::cast_to<godot::Node3D>(obj);
    }
    void set_num_real(uint8_t _value) {
        num_real = _value;
    }
    uint8_t get_num_real() const {
        return num_real;
    }

protected:
    static void _bind_methods(){
        godot::ClassDB::bind_method(godot::D_METHOD("set_node", "node"), &Coordinate::set_node);
        godot::ClassDB::bind_method(godot::D_METHOD("get_node"), &Coordinate::get_node);
        godot::ClassDB::bind_method(godot::D_METHOD("set_num_real", "num_real"), &Coordinate::set_num_real);
        godot::ClassDB::bind_method(godot::D_METHOD("get_num_real"), &Coordinate::get_num_real);

        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT,"node",godot::PROPERTY_HINT_NODE_TYPE,"Node3D"),"set_node","get_node");
        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT,"num_real"),"set_num_real","get_num_real");
    };
};
