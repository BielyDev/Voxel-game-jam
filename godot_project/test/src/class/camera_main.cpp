#include "camera_main.h"


void CameraMain::_ready() {
	init_position();
	init_raycast();
};

void CameraMain::_input(const godot::Ref<godot::InputEvent> &_event) {
	if (_event == cast_to<godot::InputEventMouseMotion>(*_event)) {
		godot::Ref<godot::InputEventMouseMotion> mouse_motion = cast_to<godot::InputEventMouseMotion>(*_event);

		ui.mouse_position = get_mouse_3d() + ui.adjustment;
		ui.mouse_position_snap = get_mouse_3d().snapped(godot::Vector3(ui.snap, ui.snap, ui.snap)) + ui.adjustment;

		update_ray_collision();
		first_controller(mouse_motion);

		if (godot::Input::get_singleton()->is_key_pressed(godot::KEY_SHIFT)) {
			drag_move(mouse_motion);
		} else {
			pivot_rotation(mouse_motion);
		};
	};

	if (_event == cast_to<godot::InputEventMouseButton>(*_event)) {
		godot::Ref<godot::InputEventMouseButton> mouse_button = cast_to<godot::InputEventMouseButton>(*_event);
		zoom(mouse_button);
	};

	first_controller(_event);
};

void CameraMain::_physics_process(float _delta){
	camera_movement();
	update_pivot(_delta, true);
};


void CameraMain::init_position() {
	set_position(godot::Vector3(0.0, 2.0, 2.0));
	pivot.rotation_degrees.x = 35.0;
	update_pivot(0.0, false);
};

void CameraMain::init_raycast(){
	ray.RayMouse = memnew(godot::RayCast3D);
	ray.RayCollision = memnew(godot::RayCast3D);

	ray.RayMouse->set_collide_with_areas(true);
	ray.RayMouse->set_collide_with_bodies(false);
	ray.RayCollision->set_collide_with_areas(true);
	ray.RayCollision->set_collide_with_bodies(false);

	ray.RayMouse->set_target_position(godot::Vector3(0, 0, -50000));
	ray.RayCollision->set_target_position(godot::Vector3(0, 0, -50000));

	ray.RayCollision->set_collision_mask_value(1, false);
	ray.RayCollision->set_collision_mask_value(8, true);

	add_child(ray.RayMouse);
	add_child(ray.RayCollision);
};

void CameraMain::update_pivot(float _delta, bool _is_lerp) {
	if (pivot.update == false){return;}

	float angle_y = godot::Math::deg_to_rad(pivot.rotation_degrees.y);
	float angle_x = godot::Math::deg_to_rad(pivot.rotation_degrees.x);

	godot::Vector3 offset = godot::Vector3(
			godot::Math::sin(angle_y) * godot::Math::cos(angle_x) * view_settings.distance,
			godot::Math::sin(angle_x) * view_settings.distance,
			godot::Math::cos(angle_y) * godot::Math::cos(angle_x) * view_settings.distance
		);

	if(_is_lerp){
		set_position(get_position().lerp(pivot.position + offset, 0.2));
	} else {
		set_position(pivot.position + offset);
	};

	set_rotation_degrees_y(pivot.rotation_degrees.y);
	set_rotation_degrees_x(-pivot.rotation_degrees.x);
};

void CameraMain::pivot_rotation(const godot::Ref<godot::InputEventMouseMotion> &_mouse_motion) {
	godot::Vector2 mouse_relative = (_mouse_motion->get_relative() * view_settings.sensibility) * 0.5;

	if (godot::Input::get_singleton()->is_mouse_button_pressed(godot::MOUSE_BUTTON_MIDDLE)) {
		pivot.rotation_degrees.y += -mouse_relative.x;
		pivot.rotation_degrees.x += mouse_relative.y;
		pivot.rotation_degrees.x = godot::Math::clamp(pivot.rotation_degrees.x, real_t(-90.0), real_t(90.0));

		update_pivot(0, false);
	};
};

void CameraMain::drag_move(const godot::Ref<godot::InputEventMouseMotion> &_mouse_motion) {
	if (godot::Input::get_singleton()->is_mouse_button_pressed(godot::MOUSE_BUTTON_MIDDLE)) {
		godot::Vector2 mouse_relative = (_mouse_motion->get_relative() * view_settings.sensibility);

		godot::Vector3 right = get_basis().get_column(0);
		godot::Vector3 up = get_basis().get_column(1);

		godot::Vector3 movement = (-right * mouse_relative.x + up * mouse_relative.y) * 0.01;

		pivot.position += (movement) * (abs(view_settings.distance) * 0.3);
	};
};

void CameraMain::zoom(const godot::Ref<godot::InputEventMouseButton> &mouse_button) {
	float slow_value = 1;

	if (mouse_button->get_button_index() == godot::MOUSE_BUTTON_WHEEL_UP) {
		view_settings.distance += -slow_value;
	} else if (mouse_button->get_button_index() == godot::MOUSE_BUTTON_WHEEL_DOWN) {
		view_settings.distance += slow_value;
	};

	view_settings.distance = godot::Math::clamp(view_settings.distance, view_settings.MIN_DISTANCE, view_settings.MAX_DISTANCE);
};


void CameraMain::first_controller(const godot::Ref<godot::InputEvent> &_event){
	if (godot::Input::get_singleton()->is_mouse_button_pressed(godot::MOUSE_BUTTON_RIGHT)){

		godot::Input::get_singleton()->set_mouse_mode(godot::Input::MOUSE_MODE_CAPTURED);

		if (_event == cast_to<godot::InputEventMouseMotion>(*_event)){
			godot::Ref<godot::InputEventMouseMotion> mouse_motion = cast_to<godot::InputEventMouseMotion>(*_event);

			camera_look(mouse_motion);
		};

	}else {
		godot::Input::get_singleton()->set_mouse_mode(godot::Input::MOUSE_MODE_VISIBLE);
	};
};

void CameraMain::camera_look(const godot::Ref<godot::InputEventMouseMotion> &_mouse_motion){
	godot::Vector3 save_pivot_position = to_local(pivot.position);

	godot::Vector2 mouse_relative = (_mouse_motion->get_relative() * view_settings.sensibility) * 0.2;

	godot::Vector3 rotation = godot::Vector3(
		get_rotation_degrees().x + -mouse_relative.y,
		get_rotation_degrees().y + -mouse_relative.x,
		0
	);
	rotation.x = godot::Math::clamp(rotation.x, real_t(-90.0), real_t(90.0));
	set_rotation_degrees(rotation);

	pivot.position = to_global(save_pivot_position);
	pivot.rotation_degrees.x = -rotation.x;
	pivot.rotation_degrees.y = rotation.y;

	update_pivot(0.0, false);
};

void CameraMain::camera_movement(){
	float x_button = godot::Input::get_singleton()->get_axis("left","right");
	float y_button = godot::Input::get_singleton()->get_axis("down","up");
	float z_button = godot::Input::get_singleton()->get_axis("back","front");

	godot::Vector3 basis_normal = get_basis().get_column(0).normalized() * 0.4;
	basis_normal.y = godot::Math::abs(get_basis().get_column(1).normalized().z) * 0.4;

	pivot.position.z += (basis_normal.x * (-z_button * view_settings.sensibility));
	pivot.position.z += (basis_normal.z * (x_button * view_settings.sensibility));
	pivot.position.x += (basis_normal.x * (x_button * view_settings.sensibility));
	pivot.position.x += (basis_normal.z * (z_button * view_settings.sensibility));
	pivot.position.y += (basis_normal.y * (-z_button * view_settings.sensibility));
	pivot.position.y += (y_button * 0.4) * view_settings.sensibility;
};


godot::Vector3 CameraMain::get_mouse_3d() {
	godot::Vector2 mouse_position = get_viewport()->get_mouse_position();
	float distance = get_position().distance_to(godot::Vector3());

	ray.RayMouse->look_at(project_position(mouse_position, distance) - ui.adjustment);
	return ray.RayMouse->get_collision_point();
};

godot::Vector3 CameraMain::get_mouse_collision_3d() {
	godot::Vector2 mouse_position = get_viewport()->get_mouse_position();
	float distance = get_position().distance_to(godot::Vector3());

	ray.RayCollision->look_at(project_position(mouse_position, distance));
	return ray.RayCollision->get_collision_point();
};

void CameraMain::update_ray_collision(){
	godot::Vector3 mouse_collision_position = get_mouse_collision_3d();

	if (ray.RayCollision->get_collider() != nullptr){

		godot::CollisionObject3D *collider = cast_to<godot::CollisionObject3D>( ray.RayCollision->get_collider());

		if (ui.body_collision_mouse != nullptr and ui.body_collision_mouse != collider){
			collider->emit_signal("mouse_exited");
		};

		ui.body_collision_mouse = collider;
		collider->emit_signal("mouse_entered");
	} else {
		if (ui.body_collision_mouse != nullptr){
			ui.body_collision_mouse->emit_signal("mouse_exited");
			ui.body_collision_mouse = nullptr;
		};

	};
};
