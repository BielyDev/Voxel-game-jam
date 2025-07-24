#pragma once

#include <unordered_map>
#include <future>
#include <memory>

#include "fast_noise.h"
#include "block.h"
#include "chunk.h"
#include "world.h"

class Generation{
    public:
        const Voxel::Vector3i WORLD_SIZE = Voxel::Vector3i(15,1,15);
        const Voxel::Vector3i CHUNK_SIZE = Voxel::Vector3i(8,32,8);

        std::unique_ptr<FastNoiseLite> noise = std::make_unique<FastNoiseLite>();
        std::unique_ptr<FastNoiseLite> cave = std::make_unique<FastNoiseLite>();

        const void new_noise(int64_t _seed, FastNoiseLite::NoiseType _noise_type, FastNoiseLite::FractalType _fractal_type = FastNoiseLite::FractalType_FBm, float _frequency = 0.02, int _octaves = 5,float _gain = 0.5){
            noise->SetSeed(_seed);
            noise->SetNoiseType(_noise_type);
            noise->SetFractalType(_fractal_type);
            noise->SetFrequency(_frequency);
            noise->SetFractalOctaves(_octaves);
            noise->SetFractalGain(_gain);

            cave->SetSeed(_seed + 1);
            cave->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
            cave->SetFractalType(_fractal_type);
            cave->SetFrequency(0.5);
            cave->SetFractalOctaves(_octaves);
            cave->SetFractalGain(_gain);
        };

        std::unordered_map<Voxel::Vector3i, Chunk> generation_world(World *_world, Voxel::Vector3i _position){
            Voxel::Vector3i real_position;
            real_position = _position - _position.div(2);

            return gen_large_chunk(_world, real_position, WORLD_SIZE, CHUNK_SIZE);
        };

        const std::unordered_map<Voxel::Vector3i, Chunk> gen_large_chunk(World *_world, const Voxel::Vector3i &_position, const Voxel::Vector3i &_amount, const Voxel::Vector3i &_chunk_size){
            std::unordered_map<Voxel::Vector3i, Chunk> chunk_list;
            Voxel::Vector3i _amount_div = _amount.div(2);
            std::unordered_map<Voxel::Vector3i, std::future<Chunk>> result;

            for (uint16_t x = 0; x < _amount.x; x++){
            for (uint16_t y = 0; y < _amount.y; y++){
            for (uint16_t z = 0; z < _amount.z; z++){
                Voxel::Vector3i _chunk_position = (_position + (Voxel::Vector3i(x,y,z).sub_xz(_amount_div) * _chunk_size));

                //result[_chunk_position] = std::async(std::launch::async, gen_chunk, _world, _chunk_position, _chunk_size, noise.get(), cave.get());
                chunk_list[_chunk_position] = gen_chunk( _world, _chunk_position, _chunk_size, noise.get(), cave.get());
            }}};

            //for (auto &i : result){
            //    chunk_list[i.first] = i.second.get();
            //}

            return chunk_list;
        };

        static Chunk gen_chunk(World *_world, const Voxel::Vector3i &_position, const Voxel::Vector3i &_size, FastNoiseLite *noise, FastNoiseLite *cave){
            Chunk new_chunk;

            new_chunk.position = _position;
            Voxel::Vector3i _size_div = _size.div(2);

            for (uint32_t x = 0; x < _size.x; x++){
            for (uint32_t y = 0; y < _size.y; y++){
            for (uint32_t z = 0; z < _size.z; z++){
                Block new_block = BlockTemplate::Air();
                Voxel::Vector3i block_position = _position + (Voxel::Vector3i(x,y,z).sub_xz(_size_div));

                float value = noise->GetNoise(float(block_position.x), float(block_position.y), float(block_position.z));
                float cave_value = cave->GetNoise(float(block_position.x), float(block_position.y), float(block_position.z));

                uint32_t height = (value * _size.y) + _position.y;

                if (block_position.y == 0){
                    new_block = BlockTemplate::Bedrock();

                    }else{
                        if (y < height){
                            new_block = BlockTemplate::Grass();
                        } else if (y < height - 2)
                        {
                            new_block = BlockTemplate::Dirt();
                        } else if (y < height - 3)
                        {
                            new_block = BlockTemplate::Stone();
                        }
                    }
                new_block.position = block_position;
                new_chunk.block_array[new_block.position] = new_block;

                if (new_block.id != BlockScope::AIR){
                    _world->all_block.insert(block_position);
                } else {
                    _world->air_block.insert(block_position);
                };

            }}};

            _world->all_chunk.insert(new_chunk.position);
            return new_chunk;
        };
};
