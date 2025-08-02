#pragma once

#include "block.h"
#include "voxel.h"
#include <unordered_map>

class Chunk {
    public:
        std::unordered_map<Voxel::Vector3i, Block> block_array;
        std::unordered_set<Voxel::Vector3i> air_block;
        Voxel::Vector3i position;
        Voxel::Vector3i size;

};
