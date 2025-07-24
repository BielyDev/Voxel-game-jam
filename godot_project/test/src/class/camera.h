#pragma once
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <algorithm>


class Camera : public godot::Camera3D{
    GDCLASS(Camera, godot::Camera3D);

    public:
        float sensi = 3.5;

        void _ready() override;
        void _input(const godot::Ref<godot::InputEvent>& _event);

        double degtorad(const double _value);
    protected:
        static void _bind_methods(){};
};
