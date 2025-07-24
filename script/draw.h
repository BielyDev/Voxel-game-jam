#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <any>
#include <algorithm>
#include <valarray>

#include "chunk.h"
#include "world.h"
#include "block.h"
#include "models.h"
#include "voxel.h"

class Draw{

    public:
        struct MyFace{
            bool is_draw = false;
            std::vector<uint8_t> direction;
        };

        static Models::ModelMap draw_chunk(Chunk &chunk, World *world){

            int _block_count = 0;
            Models::ModelMap mesh;

            std::vector<Voxel::Vector3i> normal_dir;
            std::vector<Voxel::Vector3> vertex_dir;
            std::vector<Voxel::Vector2> uv_dir;
            std::vector<uint32_t> index_dir;

            mesh.vertices.reserve(2000);
            mesh.normal.reserve(2000);
            mesh.indices.reserve(3000);
            mesh.uv.reserve(2000);

            for (std::pair<const Voxel::Vector3i, Block>& block_pair : chunk.block_array){
                Block block = block_pair.second;

                if (block.id != Block::AIR){
                    MyFace my_face = is_render_block(world, block);

                    if (my_face.is_draw){
                        normal_dir.clear(); vertex_dir.clear();
                        index_dir.clear(); uv_dir.clear();

                        for (const uint8_t& direction : my_face.direction){
                            insert_vertex( mesh.vertices, mesh.indices, block.model.vertices, block.model.indices, direction, block.position);

                            insert_uv( uv_dir, block.model.uv, direction);
                            insert_normal( normal_dir, block.model.normal, direction);
                        };

                        mesh.normal.insert(mesh.normal.end(),normal_dir.begin(),normal_dir.end());
                        mesh.uv.insert(mesh.uv.end(),uv_dir.begin(),uv_dir.end());

                        _block_count ++;
                    };
                };
            };

            return mesh;
        };

        static MyFace is_render_block(World *_world, Block &block) {
            MyFace my_face;

            for (uint32_t index_direction : block.model.directions) {
                Voxel::Vector3i new_dir = Voxel::DIRECTION[index_direction];
                Voxel::Vector3i pos = new_dir + block.position;

                if (_world->air_block.find(pos) != _world->air_block.end()) {
                    my_face.is_draw = true;
                    my_face.direction.push_back(index_direction);
                };
            };

            return my_face;
        };


        static void insert_vertex(std::vector<Voxel::Vector3>& vertex_arr, std::vector<uint32_t>& index_arr, const std::vector<Voxel::Vector3>& vertices, const std::vector<uint32_t>& indices, const uint8_t& direction, const Voxel::Vector3i& position){
            std::vector<Voxel::Vector3>::const_iterator it_start = vertices.begin() + (direction * 4);
            std::vector<Voxel::Vector3>::const_iterator it_end = vertices.begin() + ((direction + 1) * 4);


            for (uint32_t i : indices){
                index_arr.push_back(i + vertex_arr.size());
            };

            for (std::vector<Voxel::Vector3>::const_iterator it_now = it_start; it_now != it_end; it_now++){
                vertex_arr.push_back((*it_now) + position);
            };
        };
        static void insert_uv(std::vector<Voxel::Vector2>& uv_arr, const std::vector<Voxel::Vector2> &uv_list, const uint8_t& direction){
            std::vector<Voxel::Vector2>::const_iterator it_start = uv_list.begin() + (direction * 4);
            std::vector<Voxel::Vector2>::const_iterator it_end = uv_list.begin() + ((direction + 1) * 4);

            for (std::vector<Voxel::Vector2>::const_iterator it_now = it_start; it_now != it_end; it_now++){
                uv_arr.push_back(*it_now);
            };
        };
        static void insert_normal(std::vector<Voxel::Vector3i>& normal_arr,const std::vector<Voxel::Vector3i> &normal, const uint8_t& direction){
            std::vector<Voxel::Vector3i>::const_iterator it_start = normal.begin() + (direction * 4);
            std::vector<Voxel::Vector3i>::const_iterator it_end = normal.begin() + ((direction + 1) * 4);

            for (std::vector<Voxel::Vector3i>::const_iterator it_now = it_start; it_now != it_end; it_now++){
                normal_arr.push_back(*it_now);
            };
        };
    };
