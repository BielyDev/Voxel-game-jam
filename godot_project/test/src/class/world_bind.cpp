#include "world_bind.h"
#include <future>

std::future<void> result;

void WorldBind::_ready(){
    generation.new_noise(std::rand(), FastNoiseLite::NoiseType_Perlin,FastNoiseLite::FractalType_FBm, 0.01,5);
    chunk_list = generation.generation_world(world, Voxel::Vector3i());



    for (std::pair<const Voxel::Vector3i, Chunk> &chunk : chunk_list){
        instance_chunk(chunk.second);
        //result = std::async(std::launch::async, WorldBind::instance_chunk, chunk.second, this);
    };

    emit_signal("world_ready");
    godot::UtilityFunctions::print((int64_t)chunk_list.size(), " chunks no mundo!");
    godot::UtilityFunctions::print((int64_t)world->all_block.size(), " blocos solidos no mundo!");

};


void WorldBind::instance_chunk(Chunk &chunk){
    Models::ModelMap chunk_mesh = Draw::draw_chunk(chunk, world);

    if (chunk_mesh.vertices.size() > 5){
        godot::MeshInstance3D *new_mesh = memnew(godot::MeshInstance3D);
        godot::StaticBody3D *new_static = memnew(godot::StaticBody3D);
        godot::CollisionShape3D *new_collision = memnew(godot::CollisionShape3D);

        godot::ConcavePolygonShape3D *new_concave = memnew(godot::ConcavePolygonShape3D);
        godot::ArrayMesh *array_mesh = memnew(godot::ArrayMesh);

        call_deferred("add_child",new_mesh);
        new_mesh->call_deferred("add_child",new_static);
        new_static->call_deferred("add_child",new_collision);


        godot::Array surface_godot = godot::Array();

        surface_godot.resize(godot::Mesh::ARRAY_MAX);
        surface_godot[godot::Mesh::ARRAY_VERTEX] = convert_arr_vector(chunk_mesh.vertices);
        surface_godot[godot::Mesh::ARRAY_NORMAL] = convert_arr_vectori(chunk_mesh.normal);
        surface_godot[godot::Mesh::ARRAY_TEX_UV] = convert_arr_vector2(chunk_mesh.uv);
        surface_godot[godot::Mesh::ARRAY_INDEX] = convert_arr_u_int(chunk_mesh.indices);

        array_mesh->add_surface_from_arrays(
            godot::Mesh::PRIMITIVE_TRIANGLES,
            surface_godot
        );

        godot::PackedVector3Array faces;
        for (uint32_t new_index : chunk_mesh.indices){
            faces.push_back(godot::Array(surface_godot[godot::Mesh::ARRAY_VERTEX])[new_index]);
        };

        new_concave->set_faces(faces);
        new_mesh->set_mesh(array_mesh);
        new_collision->set_shape(new_concave);
        new_mesh->set_material_overlay(material);
     };
};
