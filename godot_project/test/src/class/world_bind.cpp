#include "world_bind.h"


void WorldBind::_ready(){
    generation.new_noise(std::rand(), FastNoiseLite::NoiseType_Perlin);
    chunk_list = generation.generation_world(world, Voxel::Vector3i());

    for (std::pair chunk : chunk_list){
        godot::UtilityFunctions::print(instance_chunk(chunk.second)," vertices, indices");
    };

    godot::UtilityFunctions::print("e ",world->all_block.size()," blocos solidos no mundo!");
};

godot::String WorldBind::instance_chunk(Chunk chunk){

    godot::MeshInstance3D *new_mesh = memnew(godot::MeshInstance3D);
    godot::ArrayMesh *array_mesh = memnew(godot::ArrayMesh);

    add_child(new_mesh);

    Models::ModelMap mm = Draw::draw_chunk(chunk, world);
    godot::Array surface_godot = godot::Array();

    surface_godot.resize(godot::Mesh::ARRAY_MAX);
    surface_godot[godot::Mesh::ARRAY_VERTEX] = convert_arr_vector(mm.vertices);
    surface_godot[godot::Mesh::ARRAY_NORMAL] = convert_arr_vectori(mm.normal);
    surface_godot[godot::Mesh::ARRAY_TEX_UV] = convert_arr_vector2(mm.uv);
    surface_godot[godot::Mesh::ARRAY_INDEX] = convert_arr_int(mm.indices);

    array_mesh->add_surface_from_arrays(
        godot::Mesh::PRIMITIVE_TRIANGLES,
        surface_godot
    );

    new_mesh->set_mesh(array_mesh);
    new_mesh->set_material_overlay(material);

    return godot::UtilityFunctions::str(godot::Array(surface_godot[godot::Mesh::ARRAY_VERTEX]).size()," - ", godot::Array(surface_godot[godot::Mesh::ARRAY_INDEX]).size());
};
