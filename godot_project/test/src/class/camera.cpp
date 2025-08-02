#include "camera.h"

void Camera::_ready(){
    godot::Input::get_singleton()->set_mouse_mode(godot::Input::MOUSE_MODE_CAPTURED);
};

void Camera::_input(const godot::Ref<godot::InputEvent>& _event){
	if (_event == cast_to<godot::InputEventMouseMotion>(*_event)){
        godot::Ref<godot::InputEventMouseMotion> mouse_motion = cast_to<godot::InputEventMouseMotion>(*_event);
        godot::Vector2 mouse_relative = mouse_motion->get_relative();

        set_rotation_degrees(get_rotation_degrees() + godot::Vector3(degtorad(-mouse_relative.y * sensi),godot::Math::deg_to_rad(-mouse_relative.x * sensi),0));
        set_rotation_degrees(godot::Vector3((std::clamp(float_t(get_rotation_degrees().x), -90.0f, 90.0f)), get_rotation_degrees().y, get_rotation_degrees().z));
    };
};

double Camera::degtorad(const double _value){
    return _value * (M_PI / 180);
};
