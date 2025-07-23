#include "world_bind.h"

void WorldBind::_ready(){
    generation.new_noise(std::rand(), FastNoiseLite::NoiseType_Value,FastNoiseLite::FractalType_FBm,0.03,5,0.5);
    chunk_list = generation.generation_world(world, Voxel::Vector3i());

    for (std::pair<const Voxel::Vector3i, Chunk> &chunk : chunk_list){
        instance_chunk(chunk.second);
    };

    godot::UtilityFunctions::print(world->all_block.size()," blocos solidos no mundo!");
};

void WorldBind::instance_chunk(Chunk chunk){

    godot::MeshInstance3D *new_mesh = memnew(godot::MeshInstance3D);
    godot::ArrayMesh *array_mesh = memnew(godot::ArrayMesh);
    add_child(new_mesh);

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

    new_mesh->set_mesh(array_mesh);
    new_mesh->set_material_overlay(material);
};
