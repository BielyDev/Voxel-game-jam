#pragma once

#include <vector>
#include <functional>
#include <any>
#include <string>

#include "models.h"
#include "voxel.h"

class BlockScope{
    public:
        struct Surface{
            std::vector<Voxel::Vector3> vertices;
            std::vector<Voxel::Vector3i> normal;
            std::vector<Voxel::Vector2> uv;
            std::vector<uint32_t> indices;
            std::vector<uint32_t> directions;


            Surface() = default;
            Surface(std::vector<Voxel::Vector3> _v,std::vector<Voxel::Vector3i> _n,std::vector<uint32_t> _i,std::vector<Voxel::Vector2> _u, std::vector<uint32_t> _d): vertices(_v), indices(_i), uv(_u), normal(_n), directions(_d){};
            Surface(Models::ModelMap value):
                vertices(value.vertices), normal(value.normal), indices(value.indices),uv(value.uv) {};

            BlockScope::Surface operator=(Models::ModelMap value){
                vertices = value.vertices;
                indices = value.indices;
                normal = value.normal;
                uv = value.uv;
                directions = value.directions;

                return *this;
            };

        };

        enum BLOCK_ID {AIR, GRASS, DIRT, STONE, GLASS, BEDROCK};
        enum RENDER {RENDER_NONE, RENDER_SOLID, RENDER_TRANSPARENT};
        enum COLLISION {COLLISION_NONE, COLLISION_SOLID, COLLISION_AREA};

        static const std::string get_block_name(const uint8_t &block_id){
            switch (block_id){
                case AIR:
                    return "air";
                case GRASS:
                    return "grass";
                case BEDROCK:
                    return "bedrock";
                default:
                    return "none";
            };
        };
    };
