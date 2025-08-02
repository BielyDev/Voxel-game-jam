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
        const Voxel::Vector3i WORLD_SIZE = Voxel::Vector3i(16,1,16);
        const Voxel::Vector3i CHUNK_SIZE = Voxel::Vector3i(8,32,8);
        const uint8_t RENDER_DISTANCE = 8;

        inline static std::mutex mutex;

        Voxel::Vector3 back_pos = CHUNK_SIZE;
        FastNoiseLite *noise = new(FastNoiseLite);
        FastNoiseLite *cave = new(FastNoiseLite);

        struct GenerationChunk{
            Chunk chunk;

            GenerationChunk() = default;
            GenerationChunk(Chunk _chunk, std::unordered_set<Voxel::Vector3i> _air_block, std::unordered_set<Voxel::Vector3i> _all_block) : chunk(_chunk){};
        };

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
            Voxel::Vector3i real_position = _position.snapped(CHUNK_SIZE);
            real_position.y = 0;

            std::future< std::unordered_map<Voxel::Vector3i, Chunk> > result;

            if (Voxel::Vector3(real_position).distance_to(back_pos) > RENDER_DISTANCE){
                back_pos = real_position;
                return gen_group_threads(_world, real_position, WORLD_SIZE, CHUNK_SIZE, noise, cave);
            }

            return {};
        };

        static std::unordered_map<Voxel::Vector3i, Chunk> gen_group_threads(World *_world, const Voxel::Vector3i &_position, const Voxel::Vector3i &_amount, const Voxel::Vector3i &_chunk_size, FastNoiseLite *noise, FastNoiseLite *cave){
            std::unordered_map<Voxel::Vector3i, Chunk> chunk_list;

            Voxel::Vector3i _amount_six = _amount.div(6);
            Voxel::Vector3i _position_six = _position.div(3);

            std::future<std::vector<GenerationChunk>> future_chunk_0 = std::async(std::launch::async, gen_loop_chunk, _world->all_chunk, _position, _amount, _chunk_size, noise, cave);


            for (const GenerationChunk& result : future_chunk_0.get()){
                chunk_list[result.chunk.position] = result.chunk;
                _world->all_chunk.insert(result.chunk.position);
            }
            //for (const std::pair<Voxel::Vector3i, Chunk>& result : future_chunk_4.get().second){chunk_list[result.first] = result.second;};
            //for (const std::pair<Voxel::Vector3i, Chunk>& result : future_chunk_5.get().second){chunk_list[result.first] = result.second;};
            //for (const std::pair<Voxel::Vector3i, Chunk>& result : future_chunk_6.get().second){chunk_list[result.first] = result.second;};

            return chunk_list;

        };
        static std::vector<GenerationChunk> gen_loop_chunk(std::unordered_set<Voxel::Vector3i> all_chunk,const Voxel::Vector3i &_position, const Voxel::Vector3i &_amount, const Voxel::Vector3i &_chunk_size, FastNoiseLite *noise, FastNoiseLite *cave){

            std::vector<GenerationChunk> gen_vector;

            std::unordered_map<Voxel::Vector3i, Chunk> chunk_list;
            Voxel::Vector3i _amount_div = _amount.div(2);

            for (uint16_t x = 0; x < _amount.x; x++){
            for (uint16_t y = 0; y < _amount.y; y++){
            for (uint16_t z = 0; z < _amount.z; z++){
                Voxel::Vector3i _chunk_position = (_position + (Voxel::Vector3i(x,y,z).sub_xz(_amount_div) * _chunk_size));

                if (all_chunk.find(_chunk_position) == all_chunk.end()){
                    std::cout << _chunk_position.to_string() << std::endl;

                    gen_vector.push_back(gen_chunk( _chunk_position, _chunk_size, noise, cave));
                };
            }}};

            return gen_vector;
        };

        static GenerationChunk gen_chunk(const Voxel::Vector3i &_position, const Voxel::Vector3i &_size, FastNoiseLite *noise, FastNoiseLite *cave){

            GenerationChunk generate;

            generate.chunk.position = _position;

            Voxel::Vector3i _size_div = _size.div(2);

            //mutex.lock();
            std::scoped_lock lock(mutex);

            for (uint32_t x = 0; x < _size.x; x++){
            for (uint32_t y = 0; y < _size.y; y++){
            for (uint32_t z = 0; z < _size.z; z++){
                Block new_block = BlockTemplate::Air();
                Voxel::Vector3i block_position = _position + (Voxel::Vector3i(x,y,z).sub_xz(_size_div));

                float value = noise->GetNoise(float(block_position.x), float(block_position.y), float(block_position.z));
                //float cave_value = cave->GetNoise(float(block_position.x), float(block_position.y), float(block_position.z));

                uint32_t height = (value * _size.y) + _size.y + _position.y;

                if (block_position.y == 0){
                    new_block = BlockTemplate::Bedrock();

                    }else{
                        if ((height - 17) > y){
                            new_block = BlockTemplate::Grass();
                        } else if((height - 20) > y){
                            new_block = BlockTemplate::Stone();
                        }
                    }

                new_block.position = block_position;
                generate.chunk.block_array[new_block.position] = new_block;

                if (new_block.id == BlockScope::AIR){
                    generate.chunk.air_block.insert(block_position);
                };
            }}};

            //_world->all_chunk.insert(new_chunk.position);
            //mutex.unlock();

            return generate;
        };
};
