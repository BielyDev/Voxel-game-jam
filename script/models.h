#pragma once

#include <vector>
#include <any>
#include <functional>

#include "voxel.h"


class Models{
    public:
        struct ModelMap
        {
            std::vector<Voxel::Vector3> vertices;
            std::vector<Voxel::Vector3i> normal;
            std::vector<Voxel::Vector2> uv;
            std::vector<uint32_t> indices;
            std::vector<uint32_t> directions;


            std::vector<Voxel::Vector2> make_one_uv(const std::vector<Voxel::Vector2> side){
                std::vector<Voxel::Vector2> new_side = calcule_uv(side);

                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());

                return uv;
            };
            std::vector<Voxel::Vector2> make_tri_uv(const std::vector<Voxel::Vector2> floor, const std::vector<Voxel::Vector2> up, const std::vector<Voxel::Vector2> side){
                std::vector<Voxel::Vector2> new_floor = calcule_uv(floor);
                std::vector<Voxel::Vector2> new_side = calcule_uv(side);
                std::vector<Voxel::Vector2> new_up = calcule_uv(up);

                uv.insert(uv.end(),new_up.begin(),new_up.end());
                uv.insert(uv.end(),new_floor.begin(),new_floor.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());
                uv.insert(uv.end(),new_side.begin(),new_side.end());


                return uv;
            };

            std::vector<Voxel::Vector2> calcule_uv(const std::vector<Voxel::Vector2> _uv) const {
                std::vector<Voxel::Vector2> return_uv;

                for (Voxel::Vector2 vec : _uv){
                    return_uv.push_back(vec/TEXTURE_SIZE);
                };

                return return_uv;

            };
        };


        inline static const float SIZE = 0.5;
        inline static const int TEXTURE_SIZE = 64;

        inline static const std::vector<Voxel::Vector3> UP = {
            Voxel::Vector3(SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,-SIZE),
            Voxel::Vector3(SIZE,SIZE,-SIZE)
        };
        inline static const std::vector<Voxel::Vector3> FLOOR = {
            Voxel::Vector3(SIZE,-SIZE,SIZE),
            Voxel::Vector3(SIZE,-SIZE,-SIZE),
            Voxel::Vector3(-SIZE,-SIZE,-SIZE),
            Voxel::Vector3(-SIZE,-SIZE,SIZE)
        };
        inline static const std::vector<Voxel::Vector3> FRONT = {
            Voxel::Vector3(SIZE,-SIZE,-SIZE),
            Voxel::Vector3(SIZE,SIZE,-SIZE),
            Voxel::Vector3(-SIZE,SIZE,-SIZE),
            Voxel::Vector3(-SIZE,-SIZE,-SIZE)
        };
        inline static const std::vector<Voxel::Vector3> BACK = {
            Voxel::Vector3(-SIZE,-SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,SIZE),
            Voxel::Vector3(SIZE,SIZE,SIZE),
            Voxel::Vector3(SIZE,-SIZE,SIZE)
        };
        inline static const std::vector<Voxel::Vector3> RIGHT = {
            Voxel::Vector3(SIZE,-SIZE,SIZE),
            Voxel::Vector3(SIZE,SIZE,SIZE),
            Voxel::Vector3(SIZE,SIZE,-SIZE),
            Voxel::Vector3(SIZE,-SIZE,-SIZE)
        };
        inline static const std::vector<Voxel::Vector3> LEFT = {
            Voxel::Vector3(-SIZE,-SIZE,-SIZE),
            Voxel::Vector3(-SIZE,SIZE,-SIZE),
            Voxel::Vector3(-SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,-SIZE,SIZE)
        };

        inline static const std::vector<Voxel::Vector3i> UP_NORMAL = {
            Voxel::Vector3i(0,1,0),
            Voxel::Vector3i(0,1,0),
            Voxel::Vector3i(0,1,0),
            Voxel::Vector3i(0,1,0)
        };
        inline static const std::vector<Voxel::Vector3i> FLOOR_NORMAL = {
            Voxel::Vector3i(0,-1,0),
            Voxel::Vector3i(0,-1,0),
            Voxel::Vector3i(0,-1,0),
            Voxel::Vector3i(0,-1,0)
        };
        inline static const std::vector<Voxel::Vector3i> FRONT_NORMAL = {
            Voxel::Vector3i(0,0,-1),
            Voxel::Vector3i(0,0,-1),
            Voxel::Vector3i(0,0,-1),
            Voxel::Vector3i(0,0,-1)
        };
        inline static const std::vector<Voxel::Vector3i> BACK_NORMAL = {
            Voxel::Vector3i(0,0,1),
            Voxel::Vector3i(0,0,1),
            Voxel::Vector3i(0,0,1),
            Voxel::Vector3i(0,0,1)
        };
        inline static const std::vector<Voxel::Vector3i> RIGHT_NORMAL = {
            Voxel::Vector3i(1,0,0),
            Voxel::Vector3i(1,0,0),
            Voxel::Vector3i(1,0,0),
            Voxel::Vector3i(1,0,0)
        };
        inline static const std::vector<Voxel::Vector3i> LEFT_NORMAL = {
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0)
        };


        ModelMap Cube() const {
            ModelMap mesh;

            mesh.vertices.insert(mesh.vertices.end(),UP.begin(),UP.end());
            mesh.vertices.insert(mesh.vertices.end(),FLOOR.begin(),FLOOR.end());
            mesh.vertices.insert(mesh.vertices.end(),FRONT.begin(),FRONT.end());
            mesh.vertices.insert(mesh.vertices.end(),BACK.begin(),BACK.end());
            mesh.vertices.insert(mesh.vertices.end(),RIGHT.begin(),RIGHT.end());
            mesh.vertices.insert(mesh.vertices.end(),LEFT.begin(),LEFT.end());

            mesh.normal.insert(mesh.normal.end(),UP_NORMAL.begin(),UP_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),FLOOR_NORMAL.begin(),FLOOR_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),FRONT_NORMAL.begin(),FRONT_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),BACK_NORMAL.begin(),BACK_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),RIGHT_NORMAL.begin(),RIGHT_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),LEFT_NORMAL.begin(),LEFT_NORMAL.end());

            mesh.indices.push_back(0);
            mesh.indices.push_back(1);
            mesh.indices.push_back(2);
            mesh.indices.push_back(0);
            mesh.indices.push_back(2);
            mesh.indices.push_back(3);

            mesh.directions.push_back(0);
            mesh.directions.push_back(1);
            mesh.directions.push_back(2);
            mesh.directions.push_back(3);
            mesh.directions.push_back(4);
            mesh.directions.push_back(5);

            return mesh;
        };
        ModelMap CubeBevel() const {
            ModelMap mesh;
            const float BEVEL = 0.1;
            const std::vector<Voxel::Vector3> BEVEL_UP = {
                Voxel::Vector3(SIZE - BEVEL, SIZE, SIZE - BEVEL),
                Voxel::Vector3(-SIZE + BEVEL, SIZE, SIZE - BEVEL),
                Voxel::Vector3(-SIZE + BEVEL, SIZE, -SIZE + BEVEL),
                Voxel::Vector3(SIZE - BEVEL, SIZE, -SIZE + BEVEL),
                Voxel::Vector3(SIZE , SIZE - BEVEL, SIZE),
                Voxel::Vector3(-SIZE , SIZE - BEVEL, SIZE),
                Voxel::Vector3(-SIZE , SIZE - BEVEL, -SIZE),
                Voxel::Vector3(SIZE , SIZE - BEVEL, -SIZE)
            };
            const std::vector<Voxel::Vector3> BEVEL_FLOOR = {
                Voxel::Vector3(SIZE - BEVEL, -SIZE, SIZE - BEVEL),
                Voxel::Vector3(SIZE - BEVEL, -SIZE, -SIZE + BEVEL),
                Voxel::Vector3(-SIZE + BEVEL, -SIZE, -SIZE + BEVEL),
                Voxel::Vector3(-SIZE + BEVEL, -SIZE, SIZE - BEVEL),
                Voxel::Vector3(SIZE , -SIZE + BEVEL, SIZE),
                Voxel::Vector3(SIZE , -SIZE + BEVEL, -SIZE),
                Voxel::Vector3(-SIZE , -SIZE + BEVEL, -SIZE),
                Voxel::Vector3(-SIZE , -SIZE + BEVEL, SIZE)
            };
            const std::vector<Voxel::Vector3> BEVEL_FRONT = {
                Voxel::Vector3( SIZE - BEVEL, -SIZE + BEVEL, -SIZE),
                Voxel::Vector3( SIZE - BEVEL, SIZE - BEVEL, -SIZE),
                Voxel::Vector3( -SIZE + BEVEL, SIZE - BEVEL, -SIZE),
                Voxel::Vector3( -SIZE + BEVEL, -SIZE + BEVEL ,-SIZE),
                Voxel::Vector3( SIZE , -SIZE, -SIZE + BEVEL),
                Voxel::Vector3( SIZE , SIZE, -SIZE + BEVEL),
                Voxel::Vector3( -SIZE , SIZE, -SIZE + BEVEL),
                Voxel::Vector3( -SIZE , -SIZE, -SIZE + BEVEL)
            };
            const std::vector<Voxel::Vector3> BEVEL_BACK = {
                Voxel::Vector3( -SIZE + BEVEL,-SIZE + BEVEL,SIZE),
                Voxel::Vector3( -SIZE + BEVEL,SIZE - BEVEL,SIZE),
                Voxel::Vector3( SIZE - BEVEL,SIZE - BEVEL,SIZE),
                Voxel::Vector3( SIZE - BEVEL,-SIZE + BEVEL,SIZE),
                Voxel::Vector3( -SIZE, -SIZE, SIZE + BEVEL),
                Voxel::Vector3( -SIZE, SIZE, SIZE + BEVEL),
                Voxel::Vector3( SIZE, SIZE, SIZE + BEVEL),
                Voxel::Vector3( SIZE, -SIZE, SIZE + BEVEL)
            };
            const std::vector<Voxel::Vector3> BEVEL_RIGHT = {
                Voxel::Vector3( SIZE ,-SIZE + BEVEL, SIZE - BEVEL),
                Voxel::Vector3( SIZE ,SIZE - BEVEL, SIZE - BEVEL),
                Voxel::Vector3( SIZE ,SIZE - BEVEL, -SIZE + BEVEL),
                Voxel::Vector3( SIZE ,-SIZE + BEVEL, -SIZE + BEVEL),
                Voxel::Vector3( SIZE - BEVEL , -SIZE, SIZE),
                Voxel::Vector3( SIZE - BEVEL , SIZE, SIZE),
                Voxel::Vector3( SIZE - BEVEL , SIZE, -SIZE),
                Voxel::Vector3( SIZE - BEVEL , -SIZE, -SIZE)
            };
            const std::vector<Voxel::Vector3> BEVEL_LEFT = {
                Voxel::Vector3( -SIZE , -SIZE + BEVEL, -SIZE + BEVEL),
                Voxel::Vector3( -SIZE , SIZE - BEVEL, -SIZE + BEVEL),
                Voxel::Vector3( -SIZE , SIZE - BEVEL, SIZE - BEVEL),
                Voxel::Vector3( -SIZE , -SIZE + BEVEL, SIZE - BEVEL),
               Voxel::Vector3( -SIZE + BEVEL, -SIZE, -SIZE),
                Voxel::Vector3( -SIZE + BEVEL, SIZE, -SIZE),
                Voxel::Vector3( -SIZE + BEVEL, SIZE, SIZE),
                Voxel::Vector3( -SIZE + BEVEL, -SIZE, SIZE)
            };

            const std::vector<Voxel::Vector3i> BEVEL_UP_NORMAL = {
                Voxel::Vector3i(0,1,0),
                Voxel::Vector3i(0,1,0),
                Voxel::Vector3i(0,1,0),
                Voxel::Vector3i(0,1,0),
                Voxel::Vector3i(0,1,0),
                Voxel::Vector3i(0,1,0),
                Voxel::Vector3i(0,1,0),
                Voxel::Vector3i(0,1,0)
            };
            const std::vector<Voxel::Vector3i> BEVEL_FLOOR_NORMAL = {
                Voxel::Vector3i(0,-1,0),
                Voxel::Vector3i(0,-1,0),
                Voxel::Vector3i(0,-1,0),
                Voxel::Vector3i(0,-1,0),
                Voxel::Vector3i(0,-1,0),
                Voxel::Vector3i(0,-1,0),
                Voxel::Vector3i(0,-1,0),
                Voxel::Vector3i(0,-1,0)
            };
            const std::vector<Voxel::Vector3i> BEVEL_FRONT_NORMAL = {
                Voxel::Vector3i(0,0,-1),
                Voxel::Vector3i(0,0,-1),
                Voxel::Vector3i(0,0,-1),
                Voxel::Vector3i(0,0,-1),
                Voxel::Vector3i(0,0,-1),
                Voxel::Vector3i(0,0,-1),
                Voxel::Vector3i(0,0,-1),
                Voxel::Vector3i(0,0,-1)
            };
            const std::vector<Voxel::Vector3i> BEVEL_BACK_NORMAL = {
                Voxel::Vector3i(0,0,1),
                Voxel::Vector3i(0,0,1),
                Voxel::Vector3i(0,0,1),
                Voxel::Vector3i(0,0,1),
                Voxel::Vector3i(0,0,1),
                Voxel::Vector3i(0,0,1),
                Voxel::Vector3i(0,0,1),
                Voxel::Vector3i(0,0,1)
            };
            const std::vector<Voxel::Vector3i> BEVEL_RIGHT_NORMAL = {
                Voxel::Vector3i(1,0,0),
                Voxel::Vector3i(1,0,0),
                Voxel::Vector3i(1,0,0),
                Voxel::Vector3i(1,0,0),
                Voxel::Vector3i(1,0,0),
                Voxel::Vector3i(1,0,0),
                Voxel::Vector3i(1,0,0),
                Voxel::Vector3i(1,0,0)
            };
            const std::vector<Voxel::Vector3i> BEVEL_LEFT_NORMAL = {
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0)
        };


            mesh.vertices.insert(mesh.vertices.end(),BEVEL_UP.begin(),BEVEL_UP.end());
            mesh.vertices.insert(mesh.vertices.end(),BEVEL_FLOOR.begin(),BEVEL_FLOOR.end());
            mesh.vertices.insert(mesh.vertices.end(),BEVEL_FRONT.begin(),BEVEL_FRONT.end());
            mesh.vertices.insert(mesh.vertices.end(),BEVEL_BACK.begin(),BEVEL_BACK.end());
            mesh.vertices.insert(mesh.vertices.end(),BEVEL_RIGHT.begin(),BEVEL_RIGHT.end());
            mesh.vertices.insert(mesh.vertices.end(),BEVEL_LEFT.begin(),BEVEL_LEFT.end());

            mesh.normal.insert(mesh.normal.end(),BEVEL_UP_NORMAL.begin(),BEVEL_UP_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),BEVEL_FLOOR_NORMAL.begin(),BEVEL_FLOOR_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),BEVEL_FRONT_NORMAL.begin(),BEVEL_FRONT_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),BEVEL_BACK_NORMAL.begin(),BEVEL_BACK_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),BEVEL_RIGHT_NORMAL.begin(),BEVEL_RIGHT_NORMAL.end());
            mesh.normal.insert(mesh.normal.end(),BEVEL_LEFT_NORMAL.begin(),BEVEL_LEFT_NORMAL.end());

            mesh.indices.push_back(0);
            mesh.indices.push_back(1);
            mesh.indices.push_back(2);
            mesh.indices.push_back(0);
            mesh.indices.push_back(2);
            mesh.indices.push_back(3);
            mesh.indices.push_back(4);
            mesh.indices.push_back(5);
            mesh.indices.push_back(6);
            mesh.indices.push_back(4);
            mesh.indices.push_back(6);
            mesh.indices.push_back(7);

            mesh.directions.push_back(0);
            mesh.directions.push_back(1);
            mesh.directions.push_back(2);
            mesh.directions.push_back(3);
            mesh.directions.push_back(4);
            mesh.directions.push_back(5);

            return mesh;
        };

};
