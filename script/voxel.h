#pragma once
#include <iostream>

class Voxel{
    public:


        struct Vector3i{
            int32_t x = 0;
            int32_t y = 0;
            int32_t z = 0;

            Vector3i() = default;
            Vector3i(int32_t _x, int32_t _y, int32_t _z) : x(_x), y(_y), z(_z) {}

            static Vector3i zero() {
                return Vector3i(0, 0, 0);
            };
            Vector3i div(int32_t v) const {
                return Vector3i(x / v, y / v, z / v);
            };
            Vector3i sub_xz(Vector3i v) const {
                return Vector3i(x - v.x, y, z - v.z);
            };
            int sum_xyz() const {
                return x + y + z;
            };
            int index(Vector3i size) const {
                return x + y * size.x + z * size.x * size.y;
            };
            bool operator==(const Vector3i& other) const {
                return x == other.x && y == other.y && z == other.z;
            };
            Vector3i operator+(const Vector3i other) const {
                return Vector3i(x + other.x, y + other.y, z + other.z);
            };
            Vector3i operator-(const Vector3i other) const {
                return Vector3i(x - other.x, y - other.y, z - other.z);
            };
            Vector3i operator*(const Vector3i other) const {
                return Vector3i(x * other.x, y * other.y, z * other.z);
            };
        };
        struct Vector3{
            float x = 0;
            float y = 0;
            float z = 0;

            Vector3() = default;
            Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
            Vector3(Vector3i v) : x(float(v.x)), y(float(v.y)), z(float(v.z)) {}

            static Vector3 zero() {
                return Vector3(0, 0, 0);
            };
            Vector3 div(float v) const {
                return Vector3(x / v, y / v, z / v);
            };
            float sum_xyz() const {
                return x + y + z;
            };
            float index(Vector3 size) const {
                return x + y * size.x + z * size.x * size.y;
            };
            bool operator==(const Vector3& other) const {
                return x == other.x && y == other.y && z == other.z;
            };
            Vector3 operator+(const Vector3 other) const {
                return Vector3(x + other.x, y + other.y, z + other.z);
            };
            Vector3 operator-(const Vector3 other) const {
                return Vector3(x - other.x, y - other.y, z - other.z);
            };
            Vector3 operator*(const Vector3 other) const {
                return Vector3(x * other.x, y * other.y, z * other.z);
            };
        };
        struct Vector2{
            float x = 0;
            float y = 0;

            Vector2() = default;
            Vector2(float _x, float _y) : x(_x), y(_y) {}

            static Vector2 zero() {
                return Vector2(0, 0);
            };
            Vector2 div(float v) const {
                return Vector2(x / v, y / v);
            };
            float sum_xy() const {
                return x + y;
            };
            bool operator==(const Vector2& other) const {
                return x == other.x && y == other.y;
            };
            Vector2 operator+(const Vector2 other) const {
                return Vector2(x + other.x, y + other.y);
            };
            Vector2 operator-(const Vector2 other) const {
                return Vector2(x - other.x, y - other.y);
            };
            Vector2 operator*(const Vector2 other) const {
                return Vector2(x * other.x, y * other.y);
            };
            Vector2 operator/(const Vector2 other) const {
                return Vector2(x / other.x, y / other.y);
            };
            Vector2 operator/(const int other) const {
                return Vector2(x / float(other), y / float(other));
            };
        };

        inline static const std::vector<Vector3i> DIRECTION = {
            Vector3i(0,1,0),
            Vector3i(0,-1,0),
            Vector3i(0,0,-1),
            Vector3i(0,0,1),
            Vector3i(1,0,0),
            Vector3i(-1,0,0)
        };

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
