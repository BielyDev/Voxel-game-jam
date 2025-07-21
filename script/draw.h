#pragma once


#include <iostream>
#include <vector>
#include <any>
#include <algorithm>

#include "chunk.h"
#include "world.h"
#include "block.h"
#include "models.h"

class Draw{

    public:
        static Models::ModelMap draw_chunk(Chunk chunk, World *world){

            int _block_count = 0;
            Models::ModelMap mm;


            for (std::pair block_pair : chunk.block_array){
                Block block = block_pair.second;

                if (is_render_block(world, block.position) == true){

                    std::vector<Voxel::Vector3> arr_v = append_vec_array(block.model.vertices, block.position);
                    std::vector<int> arr_i = append_int_array(block.model.indices, _block_count * block.model.vertices.size());

                    _block_count ++;

                    mm.vertices.insert(
                        mm.vertices.end(),
                        arr_v.begin(),
                        arr_v.end()
                    );
                    mm.indices.insert(
                        mm.indices.end(),
                        arr_i.begin(),
                        arr_i.end()
                    );
                    mm.uv.insert(
                        mm.uv.end(),
                        block.model.uv.begin(),
                        block.model.uv.end()
                    );
                };
            };

            return mm;
        };
        static bool is_render_block(World *_world, Voxel::Vector3i _position){
            for(Voxel::Vector3i dir : BlockScope::DIRECTION){
                //vou deixar essa var criada pra nunca mais esquecer da onde vem o interador.
                Voxel::Vector3i pos = dir + _position;

                if (_world->all_block.find(pos) == _world->all_block.end()){return true;};
            };

            return false;
        };



        static std::vector<Voxel::Vector3> append_vec_array(std::vector<Voxel::Vector3> _vector_list, Voxel::Vector3i _vector3) {
            std::vector<Voxel::Vector3> _arr;

            for (Voxel::Vector3 vec : _vector_list){
                _arr.push_back(vec + Voxel::Vector3(_vector3));
            };

            return _arr;
        };
        static std::vector<int> append_int_array(std::vector<int> _int_list, int _add) {
            std::vector<int> _arr;

            for (int number : _int_list){
                _arr.push_back(number + _add);
            };

            return _arr;
        };
};
