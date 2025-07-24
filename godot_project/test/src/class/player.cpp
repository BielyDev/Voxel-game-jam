#include "player.h"


void Player::_ready(){
    init_connection();
    init_shape();
    init_camera();
    init_raycast();
};

void Player::_world_ready(){
    set_floor();
};


void Player::_physics_process(float _delta){
    movement();
    apply_accelerated();
    gravity();
    jump();

    move_and_slide();
};


void Player::init_connection(){
    godot::Object* world_obj = godot::ObjectDB::get_instance(world_selected_id);

    WorldBind* world_bind = godot::Object::cast_to<WorldBind>(world_obj);
    if (world_bind != nullptr){
        std::cout << "opa" << std::endl;
        world_bind->connect("world_ready", callable_mp( this, &Player::_world_ready));
    };
};

void Player::init_shape(){
    Collision = memnew(godot::CollisionShape3D);
    Shape = memnew(godot::BoxShape3D);

    add_child(Collision);

    Collision->set_shape(Shape);
    Shape->set_size(godot::Vector3(0.75,head_height,0.75));
};

void Player::init_camera(){
    Cam = memnew(Camera);

    add_child(Cam);
    Cam->set_position(godot::Vector3(0,head_height/2,0));
};

void Player::init_raycast(){
    RayVision = memnew(godot::RayCast3D);
    RayFloor = memnew(godot::RayCast3D);

    Cam->add_child(RayVision);
    add_child(RayFloor);

    RayVision->set_target_position(godot::Vector3(0,0,-10));
    RayFloor->set_target_position(godot::Vector3(0,-500,0));
    RayFloor->set_position(godot::Vector3(0,250,0));
};

void Player::movement(){
    motion.x = 0;
    motion.z = 0;

    godot::Vector3 basis = Cam->get_global_basis().get_column(0).normalized();

	motion.z += godot::Input::get_singleton()->get_axis("front","back") * (basis.x) * speed;
	motion.x += -godot::Input::get_singleton()->get_axis("front","back") * (basis.z) * speed;
	motion.z += godot::Input::get_singleton()->get_axis("left","right") * (basis.z) * speed;
	motion.x += godot::Input::get_singleton()->get_axis("left","right") * (basis.x) * speed;
};


void Player::gravity(){
    set_velocity(godot::Vector3(get_velocity().x , get_velocity().y -GRAVITY_FORCE, get_velocity().z));

    if (get_velocity().y < -GRAVITY_MAX){
        set_velocity(godot::Vector3(get_velocity().x, -GRAVITY_MAX, get_velocity().z));
    };
};

void Player::jump(){
	if (is_on_floor() and godot::Input::get_singleton()->is_action_just_pressed("jump")){
		set_velocity(godot::Vector3(get_velocity().x, JUMP, get_velocity().z));
    };
};

void Player::selector(){

};

void Player::set_floor(){
    set_global_position(godot::Vector3(get_global_position().x, RayFloor->get_collision_point().y + head_height, get_global_position().z));
};


void Player::add_velocity(godot::Vector3 _add){
    set_velocity(get_velocity() + _add);
};

void Player::apply_accelerated(){
    godot::Vector3 lerp = get_velocity().lerp(motion, accelerated);
    lerp.y = get_velocity().y;
    set_velocity(lerp);
};
