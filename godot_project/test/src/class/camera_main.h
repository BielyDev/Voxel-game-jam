#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/collision_object3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>


class CameraMain : public godot::Camera3D {
	GDCLASS(CameraMain, Camera3D);

public:
	struct ViewSettings {
		const float MAX_DISTANCE = 25.0;
		const float MIN_DISTANCE = 1.0;

		float sensibility = 0.5;
		float distance = 3.0;
	};
	struct Pivot {
		bool update = true;
		godot::Vector3 position = godot::Vector3();
		godot::Vector3 rotation_degrees = godot::Vector3();
	};
	struct UiViewport {
		godot::CollisionObject3D *body_collision_mouse = nullptr;

		godot::Vector3 mouse_position = godot::Vector3();
		godot::Vector3 mouse_position_snap = godot::Vector3();
		godot::Vector3 adjustment = godot::Vector3(0.5, 0.0, 0.5);

		float snap = 1.0;
	};
	struct Ray {
		godot::RayCast3D *RayMouse;
		godot::RayCast3D *RayCollision;
	};

	Pivot pivot;
	ViewSettings view_settings;
	UiViewport ui;
	Ray ray;

	void _ready() override;
	void _input(const godot::Ref<godot::InputEvent> &_event);
	void _physics_process(float _delta);

	void init_position();
	void init_raycast();
	void update_pivot(float _delta, bool _is_lerp);
	void pivot_rotation(const godot::Ref<godot::InputEventMouseMotion> &_mouse_motion);
	void drag_move(const godot::Ref<godot::InputEventMouseMotion> &_mouse_motion);
	void zoom(const godot::Ref<godot::InputEventMouseButton> &_mouse_button);
	void first_controller(const godot::Ref<godot::InputEvent> &_event);
	void camera_movement();
	void camera_look(const godot::Ref<godot::InputEventMouseMotion> &_mouse_motion);

	void update_ray_collision();
	godot::Vector3 get_mouse_3d();
	godot::Vector3 get_mouse_collision_3d();

	void set_rotation_degrees_x(float x){
		godot::Vector3 rotation_deg = get_rotation_degrees();
		rotation_deg.x = x;
		set_rotation_degrees(rotation_deg);
	};
	void set_rotation_degrees_y(float y){
		godot::Vector3 rotation_deg = get_rotation_degrees();
		rotation_deg.y = y;
		set_rotation_degrees(rotation_deg);
	};
	void set_rotation_degrees_z(float z){
		godot::Vector3 rotation_deg = get_rotation_degrees();
		rotation_deg.z = z;
		set_rotation_degrees(rotation_deg);
	};

	void set_mouse_position(godot::Vector3 _value) {
		ui.mouse_position = _value;
	};
	godot::Vector3 get_mouse_position() {
		return ui.mouse_position;
	};
	void set_mouse_position_snap(godot::Vector3 _value) {
		ui.mouse_position_snap = _value.snapped(godot::Vector3(ui.snap, ui.snap, ui.snap));
	};
	godot::Vector3 get_mouse_position_snap() {
		return ui.mouse_position_snap;
	};
	godot::CollisionObject3D* get_body_collision_mouse() {
		return ui.body_collision_mouse;
	};
	float get_snap() {
		return ui.snap;
	};

protected:
	static void _bind_methods() {
		godot::ClassDB::bind_method(godot::D_METHOD("get_mouse_position"), &CameraMain::get_mouse_position);
		godot::ClassDB::bind_method(godot::D_METHOD("set_mouse_position", "mouse_position"), &CameraMain::set_mouse_position);
		godot::ClassDB::bind_method(godot::D_METHOD("get_mouse_position_snap"), &CameraMain::get_mouse_position_snap);
		godot::ClassDB::bind_method(godot::D_METHOD("set_mouse_position_snap", "mouse_position_snap"), &CameraMain::set_mouse_position_snap);
		godot::ClassDB::bind_method(godot::D_METHOD("get_body_collision_mouse"), &CameraMain::get_body_collision_mouse);
		godot::ClassDB::bind_method(godot::D_METHOD("get_snap"), &CameraMain::get_snap);


		ADD_PROPERTY(
				godot::PropertyInfo(
						godot::Variant::VECTOR3,
						"mouse_position",
						godot::PROPERTY_HINT_NONE,
						"",
						godot::PROPERTY_USAGE_STORAGE),
				"set_mouse_position",
				"get_mouse_position");
		ADD_PROPERTY(
				godot::PropertyInfo(
						godot::Variant::VECTOR3,
						"mouse_position_snap",
						godot::PROPERTY_HINT_NONE,
						"",
						godot::PROPERTY_USAGE_STORAGE),
				"set_mouse_position_snap",
				"get_mouse_position_snap");
	};
};
