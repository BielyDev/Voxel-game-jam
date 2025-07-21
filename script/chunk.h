#pragma once

#include "block.h"
#include "voxel.h"
#include <unordered_map>

class Chunk {
    public:
        std::unordered_map<Voxel::Vector3i, Block> block_array;
        Voxel::Vector3i position;
        Voxel::Vector3i size;
};