#pragma once

#include<unordered_set>

#include "voxel.h"

class World{
    public:
        std::unordered_set<Voxel::Vector3i> all_block;
        std::unordered_set<Voxel::Vector3i> all_chunk;
        std::unordered_set<Voxel::Vector3i> air_block;
        std::unordered_set<Voxel::Vector3i> render_block;
};
