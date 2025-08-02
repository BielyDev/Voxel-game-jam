#pragma once

#include <unordered_set>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/concave_polygon_shape3d.hpp>

#include "../../../script/generation.h"
#include "../../../script/draw.h"
#include "../../../script/voxel.h"

class WorldBind : public godot::Node3D{
    GDCLASS(WorldBind, godot::Node3D);

    public:
        World *world = new(World);
        Generation generation;
        std::unordered_map<Voxel::Vector3i, Chunk> chunk_list;
        std::unordered_map<Voxel::Vector3i, Chunk> chunk_temp_list;
        godot::Ref<godot::Material> material = godot::ResourceLoader::get_singleton()->load("res://Assets/Material/block.tres");

        void _ready() override;
        void _process(float _delta);
        void instance_chunk(Chunk &chunk);

        static godot::PackedVector3Array convert_arr_unordered(std::unordered_set<Voxel::Vector3i> _block_list){
            godot::PackedVector3Array _packet;

            for (Voxel::Vector3 block_pair : _block_list){
                _packet.push_back(godot::Vector3(block_pair.x, block_pair.y, block_pair.z));
            };

            return _packet;
        };
        static godot::PackedVector3Array convert_arr_vector(std::vector<Voxel::Vector3> _block_list){
            godot::PackedVector3Array _packet;

            for (Voxel::Vector3 block_pair : _block_list){
                _packet.push_back(godot::Vector3(block_pair.x, block_pair.y, block_pair.z));
            };

            return _packet;
        };
        static godot::PackedVector2Array convert_arr_vector2(std::vector<Voxel::Vector2> _block_list){
            godot::PackedVector2Array _packet;

            for (Voxel::Vector2 block_pair : _block_list){
                _packet.push_back(godot::Vector2(block_pair.x, block_pair.y));
            };

            return _packet;
        };
        static godot::PackedVector3Array convert_arr_vectori(std::vector<Voxel::Vector3i> _block_list){
            godot::PackedVector3Array _packet;

            for (Voxel::Vector3 block_pair : _block_list){
                _packet.push_back(godot::Vector3i(block_pair.x, block_pair.y, block_pair.z));
            };

            return _packet;
        };
        static godot::PackedInt32Array convert_arr_int(std::vector<int> _value){
            godot::PackedInt32Array _packet;

            for (int value_pair : _value){
                _packet.push_back(value_pair);
            };

            return _packet;
        };
        static godot::PackedInt32Array convert_arr_u_int(std::vector<uint32_t> _value){
            godot::PackedInt32Array _packet;

            for (int value_pair : _value){
                _packet.push_back(value_pair);
            };

            return _packet;
        };

        static godot::Vector3 convert_vector(Voxel::Vector3 _vector){
            return godot::Vector3(_vector.x, _vector.y, _vector.z);
        };


    protected:
        static void _bind_methods(){
            ADD_SIGNAL(godot::MethodInfo("world_ready"));
        };
};
