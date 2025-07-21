#pragma once

#include <iostream>
#include <vector>

#include "models.h"
#include "block_static.h"

class BlockRegistry: public BlockScope{
    public:
        int8_t id = BlockScope::AIR;
        int8_t render = BlockScope::RENDER_NONE;
        int8_t collision = BlockScope::COLLISION_NONE;

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

            block.id = BlockScope::GRASS;
            block.render = BlockScope::RENDER_SOLID;
            block.collision = BlockScope::COLLISION_SOLID;

            block.model = pre_model.Cube();

            return block;
        };
};
