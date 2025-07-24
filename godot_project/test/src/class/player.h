#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>
#include <godot_cpp/variant/callable.hpp>
#include "camera.h"
#include "world_bind.h"


class Player : public godot::CharacterBody3D{
    GDCLASS(Player, godot::CharacterBody3D);

    public:
        const uint8_t SPEED_DEFAULT = 5;
        const uint8_t SPEED_RUN = 8;
        const uint8_t GRAVITY_MAX = 50;
        const uint8_t JUMP = 10;
        const float GRAVITY_FORCE = 0.4;

        float head_height = 1.7;
        float speed = SPEED_DEFAULT;
        float accelerated = 0.2;

        godot::Vector3 motion;

        godot::ObjectID world_selected_id;
        godot::RayCast3D *RayVision;
        godot::RayCast3D *RayFloor;
        godot::CollisionShape3D *Collision;
        godot::BoxShape3D *Shape;
        Camera *Cam;


        void _ready() override;
        void _physics_process(float _delta);

        void _world_ready();

        void init_connection();
        void init_camera();
        void init_raycast();
        void init_shape();

        void movement();
        void jump();
        void gravity();

        void selector();
        void set_floor();

        void add_velocity(godot::Vector3 _add);
        void apply_accelerated();


        void set_world(WorldBind* node) {
            if (node) {world_selected_id = node->get_instance_id();}
            else {world_selected_id = godot::ObjectID();}
        }
        WorldBind* get_world() const {
            godot::Object* world_obj = godot::ObjectDB::get_instance(world_selected_id);
            return godot::Object::cast_to<WorldBind>(world_obj);
        }

    protected:
        static void _bind_methods(){
            godot::ClassDB::bind_method(godot::D_METHOD("set_world", "world_bind"), &Player::set_world);
            godot::ClassDB::bind_method(godot::D_METHOD("get_world"), &Player::get_world);
            ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT,"world_bind",godot::PROPERTY_HINT_NODE_TYPE,"WorldBind"),"set_world","get_world");
        };

};
