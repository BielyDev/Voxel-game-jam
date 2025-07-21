#pragma once

#include <vector>
#include <functional>
#include <any>

#include "models.h"
#include "voxel.h"

class BlockScope{
    public:
        struct Surface{
            std::vector<Voxel::Vector3> vertices;
            std::vector<int> indices;
            std::vector<Voxel::Vector2> uv;

            Surface() = default;
            Surface(std::vector<Voxel::Vector3> _v,std::vector<int> _i,std::vector<Voxel::Vector2> _u): vertices(_v), indices(_i), uv(_u){};
            Surface(Models::ModelMap value):
                vertices(value.vertices), indices(value.indices),uv(value.uv) {};
            
            BlockScope::Surface operator=(Models::ModelMap value){
                vertices = value.vertices;
                indices = value.indices;
                uv = value.uv;

                return *this;
            };

        };

        inline static const std::vector<Voxel::Vector3i> DIRECTION = {
            Voxel::Vector3i(1,0,0),
            Voxel::Vector3i(0,1,0),
            Voxel::Vector3i(0,0,1),
            Voxel::Vector3i(0,0,-1),
            Voxel::Vector3i(0,-1,0),
            Voxel::Vector3i(-1,0,0),
            
        };

        enum BLOCK_ID {AIR, GRASS};
        enum RENDER {RENDER_NONE, RENDER_SOLID, RENDER_TRANSPARENT};
        enum COLLISION {COLLISION_NONE, COLLISION_SOLID, COLLISION_AREA};
};




template <>
struct std::hash<Voxel::Vector3i>{
            
    std::size_t operator()(const Voxel::Vector3i& v) const {
        std::size_t hx = std::hash<int>()(v.x);
        std::size_t hy = std::hash<int>()(v.y);
        std::size_t hz = std::hash<int>()(v.z);

        return ((hx ^ (hy << 1)) >> 1) ^ (hz << 1);
    };
};
template <>
struct std::hash<Voxel::Vector3>{
            
    std::size_t operator()(const Voxel::Vector3& v) const {
        std::size_t hx = std::hash<float>()(v.x);
        std::size_t hy = std::hash<float>()(v.y);
        std::size_t hz = std::hash<float>()(v.z);

        return ((hx ^ (hy << 1)) >> 1) ^ (hz << 1);
    };
};
template <>
struct std::hash<Voxel::Vector2>{
            
    std::size_t operator()(const Voxel::Vector2& v) const {
        std::size_t hx = std::hash<float>()(v.x);
        std::size_t hy = std::hash<float>()(v.y);

        return ((hx ^ (hy << 1)) >> 1);
    };
};

