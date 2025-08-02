#pragma once

#include <iostream>
#include <vector>

#include "models.h"
#include "block_static.h"

class BlockRegistry: public BlockScope{
    public:
        uint8_t id = BlockScope::AIR;
        uint8_t render = BlockScope::RENDER_NONE;
        uint8_t collision = BlockScope::COLLISION_NONE;

        Voxel::Vector3i position = Voxel::Vector3i::zero();

        Surface model;

};

class BlockBehavior : public BlockRegistry{
    public:
        void change_id(int8_t _new_id); //Lembrar q essa função tem que alterar todos os dados do BlockRegistry
};

class Block : public BlockBehavior{
    public:
    bool operator==(const Block& _block) const {
        return (position == _block.position) and (id == _block.id);
    };
};

class BlockTemplate{
    public:
        static Block Air(){
            Block block;

            block.id = BlockScope::AIR;
            block.render = BlockScope::RENDER_NONE;
            block.collision = BlockScope::COLLISION_NONE;

            return block;
        };
        static Block Grass(){
            Block block;
            Models pre_model;
            Models::ModelMap model = pre_model.Cube();

            model.make_tri_uv(
                std::vector<Voxel::Vector2>{
                    Voxel::Vector2(8,0),Voxel::Vector2(16,0),Voxel::Vector2(16,8),Voxel::Vector2(8,8)},
                std::vector<Voxel::Vector2>{
                    Voxel::Vector2(0,8),Voxel::Vector2(8,8),Voxel::Vector2(8,16),Voxel::Vector2(0,16)},
                std::vector<Voxel::Vector2>{
                    Voxel::Vector2(0,8),Voxel::Vector2(0,0),Voxel::Vector2(8,0),Voxel::Vector2(8,8)}
            );

            block.id = BlockScope::GRASS;
            block.render = BlockScope::RENDER_SOLID;
            block.collision = BlockScope::COLLISION_SOLID;

            block.model = model;

            return block;
        };
        static Block Dirt(){
            Block block;
            Models pre_model;
            Models::ModelMap model = pre_model.Cube();

            model.make_one_uv(
                std::vector<Voxel::Vector2>{
                    Voxel::Vector2(8,0),Voxel::Vector2(16,0),Voxel::Vector2(16,8),Voxel::Vector2(8,8)}
            );

            block.id = BlockScope::DIRT;
            block.render = BlockScope::RENDER_SOLID;
            block.collision = BlockScope::COLLISION_SOLID;

            block.model = model;

            return block;
        };
        static Block Stone(){
            Block block;
            Models pre_model;
            Models::ModelMap model = pre_model.Cube();

            model.make_one_uv(
                std::vector<Voxel::Vector2>{
                    Voxel::Vector2(8,8),Voxel::Vector2(16,8),Voxel::Vector2(16,16),Voxel::Vector2(8,16)}
            );

            block.id = BlockScope::STONE;
            block.render = BlockScope::RENDER_SOLID;
            block.collision = BlockScope::COLLISION_SOLID;

            block.model = model;

            return block;
        };
        static Block Glass(){
            Block block;
            Models pre_model;
            Models::ModelMap model = pre_model.Cube();

            model.make_one_uv(
                std::vector<Voxel::Vector2>{
                    Voxel::Vector2(16,8),Voxel::Vector2(24,8),Voxel::Vector2(24,16),Voxel::Vector2(16,16)}
            );

            block.id = BlockScope::GLASS;
            block.render = BlockScope::RENDER_SOLID;
            block.collision = BlockScope::COLLISION_SOLID;

            block.model = model;

            return block;
        };
        static Block Bedrock(){
            Block block;
            Models pre_model;
            Models::ModelMap model = pre_model.Cube();

            model.make_one_uv(
                std::vector<Voxel::Vector2>{
                    Voxel::Vector2(16,0),Voxel::Vector2(24,0),Voxel::Vector2(24,8),Voxel::Vector2(16,8)}
            );

            block.id = BlockScope::BEDROCK;
            block.render = BlockScope::RENDER_SOLID;
            block.collision = BlockScope::COLLISION_SOLID;

            block.model = model;

            return block;
        };
};
