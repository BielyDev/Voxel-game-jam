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
            std::vector<int> indices;


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

        const std::vector<Voxel::Vector3> UP = {
            Voxel::Vector3(SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,-SIZE),
            Voxel::Vector3(SIZE,SIZE,-SIZE)
        };
        const std::vector<Voxel::Vector3> FLOOR = {
            Voxel::Vector3(SIZE,-SIZE,SIZE),
            Voxel::Vector3(-SIZE,-SIZE,SIZE),
            Voxel::Vector3(-SIZE,-SIZE,-SIZE),
            Voxel::Vector3(SIZE,-SIZE,-SIZE)
        };
        const std::vector<Voxel::Vector3> FRONT = {
            Voxel::Vector3(SIZE,-SIZE,-SIZE),
            Voxel::Vector3(SIZE,SIZE,-SIZE),
            Voxel::Vector3(-SIZE,SIZE,-SIZE),
            Voxel::Vector3(-SIZE,-SIZE,-SIZE)
        };
        const std::vector<Voxel::Vector3> BACK = {
            Voxel::Vector3(SIZE,-SIZE,SIZE),
            Voxel::Vector3(SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,-SIZE,SIZE)
        };
        const std::vector<Voxel::Vector3> RIGHT = {
            Voxel::Vector3(SIZE,-SIZE,SIZE),
            Voxel::Vector3(SIZE,SIZE,SIZE),
            Voxel::Vector3(SIZE,SIZE,-SIZE),
            Voxel::Vector3(SIZE,-SIZE,-SIZE)
        };
        const std::vector<Voxel::Vector3> LEFT = {
            Voxel::Vector3(-SIZE,-SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,SIZE),
            Voxel::Vector3(-SIZE,SIZE,-SIZE),
            Voxel::Vector3(-SIZE,-SIZE,-SIZE)
        };


        const std::vector<Voxel::Vector3i> UP_NORMAL = {
            Voxel::Vector3i(0,1,0),
            Voxel::Vector3i(0,1,0),
            Voxel::Vector3i(0,1,0),
            Voxel::Vector3i(0,1,0)
        };
        const std::vector<Voxel::Vector3i> FLOOR_NORMAL = {
            Voxel::Vector3i(0,-1,0),
            Voxel::Vector3i(0,-1,0),
            Voxel::Vector3i(0,-1,0),
            Voxel::Vector3i(0,-1,0)
        };
        const std::vector<Voxel::Vector3i> FRONT_NORMAL = {
            Voxel::Vector3i(0,0,-1),
            Voxel::Vector3i(0,0,-1),
            Voxel::Vector3i(0,0,-1),
            Voxel::Vector3i(0,0,-1)
        };
        const std::vector<Voxel::Vector3i> BACK_NORMAL = {
            Voxel::Vector3i(0,0,1),
            Voxel::Vector3i(0,0,1),
            Voxel::Vector3i(0,0,1),
            Voxel::Vector3i(0,0,1)
        };
        const std::vector<Voxel::Vector3i> RIGHT_NORMAL = {
            Voxel::Vector3i(1,0,0),
            Voxel::Vector3i(1,0,0),
            Voxel::Vector3i(1,0,0),
            Voxel::Vector3i(1,0,0)
        };
        const std::vector<Voxel::Vector3i> LEFT_NORMAL = {
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0),
            Voxel::Vector3i(-1,0,0)
        };



        const std::vector<int> UP_INDEX = {0,1,2,0,2,3};
        const std::vector<int> FLOOR_INDEX = {4,6,5,4,7,6};
        const std::vector<int> FRONT_INDEX = {8,9,10,8,10,11};
        const std::vector<int> BACK_INDEX = {12,14,13,12,15,14};
        const std::vector<int> RIGHT_INDEX = {16,17,18,16,18,19};
        const std::vector<int> LEFT_INDEX = {20,22,21,20,23,22};


        ModelMap Cube() const {
            ModelMap mm;

            mm.vertices.insert(mm.vertices.end(),UP.begin(),UP.end());
            mm.vertices.insert(mm.vertices.end(),FLOOR.begin(),FLOOR.end());
            mm.vertices.insert(mm.vertices.end(),FRONT.begin(),FRONT.end());
            mm.vertices.insert(mm.vertices.end(),BACK.begin(),BACK.end());
            mm.vertices.insert(mm.vertices.end(),RIGHT.begin(),RIGHT.end());
            mm.vertices.insert(mm.vertices.end(),LEFT.begin(),LEFT.end());

            mm.normal.insert(mm.normal.end(),UP_NORMAL.begin(),UP_NORMAL.end());
            mm.normal.insert(mm.normal.end(),FLOOR_NORMAL.begin(),FLOOR_NORMAL.end());
            mm.normal.insert(mm.normal.end(),FRONT_NORMAL.begin(),FRONT_NORMAL.end());
            mm.normal.insert(mm.normal.end(),BACK_NORMAL.begin(),BACK_NORMAL.end());
            mm.normal.insert(mm.normal.end(),RIGHT_NORMAL.begin(),RIGHT_NORMAL.end());
            mm.normal.insert(mm.normal.end(),LEFT_NORMAL.begin(),LEFT_NORMAL.end());

            mm.indices.insert(mm.indices.end(),UP_INDEX.begin(),UP_INDEX.end());
            mm.indices.insert(mm.indices.end(),FLOOR_INDEX.begin(),FLOOR_INDEX.end());
            mm.indices.insert(mm.indices.end(),FRONT_INDEX.begin(),FRONT_INDEX.end());
            mm.indices.insert(mm.indices.end(),BACK_INDEX.begin(),BACK_INDEX.end());
            mm.indices.insert(mm.indices.end(),RIGHT_INDEX.begin(),RIGHT_INDEX.end());
            mm.indices.insert(mm.indices.end(),LEFT_INDEX.begin(),LEFT_INDEX.end());

            //std::cout << "vertice" << (mm.vertices.size()) << std::endl;
            //std::cout << "normal" << (mm.normal.size()) << std::endl;

            return mm;
        };

};
