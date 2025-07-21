#pragma once

#include <unordered_map>

#include "fast_noise.h"
#include "block.h"
#include "chunk.h"
#include "world.h"

class Generation{
    public:
        const Voxel::Vector3i WORLD_SIZE = Voxel::Vector3i(8,1,8);
        const Voxel::Vector3i CHUNK_SIZE = Voxel::Vector3i(8,16,8);

        FastNoiseLite noise;

        void new_noise(int64_t _seed, FastNoiseLite::NoiseType _noise_type){
            noise.SetSeed(2);
            noise.SetNoiseType(_noise_type);
            //noise.SetFrequency(0.1);
        };

        std::unordered_map<Voxel::Vector3i, Chunk> generation_world(World *_world, Voxel::Vector3i _position){
            Voxel::Vector3i real_position;
            real_position = _position - _position.div(2);

            return gen_large_chunk(_world, real_position, WORLD_SIZE, CHUNK_SIZE);
        };

        std::unordered_map<Voxel::Vector3i, Chunk> gen_large_chunk(World *_world, Voxel::Vector3i _position, Voxel::Vector3i _amount, Voxel::Vector3i _chunk_size){
            std::unordered_map<Voxel::Vector3i, Chunk> chunk_list;
            Voxel::Vector3i _amount_div = _amount.div(2);

            for (int32_t x = 0; x < _amount.x; x++){
            for (int32_t y = 0; y < _amount.y; y++){
            for (int32_t z = 0; z < _amount.z; z++){
                Voxel::Vector3i _chunk_position = (_position + (_amount_div - Voxel::Vector3i(x,y,z)) * _chunk_size);

                chunk_list[_chunk_position] = gen_chunk(_world, _chunk_position, _chunk_size);
            }}};

            return chunk_list;
        };

        Chunk gen_chunk(World *_world, Voxel::Vector3i _position, Voxel::Vector3i _size){
            Chunk new_chunk;

            new_chunk.position = _position;
            Voxel::Vector3i _size_div = _size.div(2);

            for (int32_t x = 0; x < _size.x; x++){
            for (int32_t y = 0; y < _size.y; y++){
            for (int32_t z = 0; z < _size.z; z++){
                Block new_block = BlockTemplate::Air();
                Voxel::Vector3i block_position = _position + (_size_div - Voxel::Vector3i(x,y,z));

                float value = noise.GetNoise(float(block_position.x), float(block_position.y), float(block_position.z));
                int32_t height = int32_t(value * _size.y);

                if (y == 0){
                    new_block = BlockTemplate::Grass();
                } else{
                    if (height < y){
                        new_block = BlockTemplate::Grass();
                    };
                };
                new_block.position = block_position;
                new_chunk.block_array[new_block.position] = new_block;

                if (new_block.id != BlockScope::AIR){
                    _world->all_block.insert(new_block.position);
                };

            }}};

            return new_chunk;
        };
};
