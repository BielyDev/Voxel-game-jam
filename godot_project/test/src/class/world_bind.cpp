#include "world_bind.h"

void WorldBind::_ready(){
    generation.new_noise(std::rand(), FastNoiseLite::NoiseType_Perlin,FastNoiseLite::FractalType_FBm);
    chunk_list = generation.generation_world(world, Voxel::Vector3i());

    for (std::pair<const Voxel::Vector3i, Chunk> &chunk : chunk_list){
        instance_chunk(chunk.second);
    };

    godot::UtilityFunctions::print((int64_t)world->all_block.size(), " blocos solidos no mundo!");

};

#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/concave_polygon_shape3d.hpp>

void WorldBind::instance_chunk(Chunk chunk){

    godot::MeshInstance3D *new_mesh = memnew(godot::MeshInstance3D);
    godot::StaticBody3D *new_static = memnew(godot::StaticBody3D);
    godot::CollisionShape3D *new_collision = memnew(godot::CollisionShape3D);

    godot::ConcavePolygonShape3D *new_concave = memnew(godot::ConcavePolygonShape3D);
    godot::ArrayMesh *array_mesh = memnew(godot::ArrayMesh);

    add_child(new_mesh);
    new_mesh->add_child(new_static);
    new_static->add_child(new_collision);

    Models::ModelMap mesh = Draw::draw_chunk(chunk, world);
    godot::Array surface_godot = godot::Array();

    surface_godot.resize(godot::Mesh::ARRAY_MAX);
    surface_godot[godot::Mesh::ARRAY_VERTEX] = convert_arr_vector(mesh.vertices);
    surface_godot[godot::Mesh::ARRAY_NORMAL] = convert_arr_vectori(mesh.normal);
    surface_godot[godot::Mesh::ARRAY_TEX_UV] = convert_arr_vector2(mesh.uv);
    surface_godot[godot::Mesh::ARRAY_INDEX] = convert_arr_u_int(mesh.indices);

    array_mesh->add_surface_from_arrays(
        godot::Mesh::PRIMITIVE_TRIANGLES,
        surface_godot
    );

    godot::PackedVector3Array faces;
    for (uint32_t new_index : mesh.indices){
        faces.push_back(godot::Array(surface_godot[godot::Mesh::ARRAY_VERTEX])[new_index]);
    };

    new_concave->set_faces(faces);
    new_mesh->set_mesh(array_mesh);
    new_collision->set_shape(new_concave);
    new_mesh->set_material_overlay(material);
};
