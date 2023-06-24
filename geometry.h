#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

template <size_t DIM, typename Type>
struct vec
{
    vec()
    {
        for (size_t i = 0; i < DIM; i++)
            data_[i] = Type();
    }
    Type &operator[](const size_t i)
    {
        assert(i < DIM);
        return data_[i];
    }
    const Type &operator[](const size_t i) const
    {
        assert(i < DIM);
        return data_[i];
    }

private:
    Type data_[DIM];
};

typedef vec<2, float> Vec2f;
typedef vec<3, float> Vec3f;
typedef vec<3, int> Vec3i;
typedef vec<4, float> Vec4f;

template <typename Type>
struct vec<2, Type>
{
    vec() : x(Type()), y(Type()) {}
    vec(Type X, Type Y) : x(X), y(Y) {}
    template <class Other>
    vec<2, Type>(const vec<2, Other> &v);
    Type &operator[](const size_t i)
    {
        assert(i < 2);
        return i <= 0 ? x : y;
    }
    const Type &operator[](const size_t i) const
    {
        assert(i < 2);
        return i <= 0 ? x : y;
    }
    Type x, y;
};

template <typename Type>
struct vec<3, Type>
{
    vec() : x(Type()), y(Type()), z(Type()) {}
    vec(Type X, Type Y, Type Z) : x(X), y(Y), z(Z) {}
    Type &operator[](const size_t i)
    {
        assert(i < 3);
        return i <= 0 ? x : (i == 1 ? y : z);
    }
    const Type &operator[](const size_t i) const
    {
        assert(i < 3);
        return i <= 0 ? x : (1 == i ? y : z);
    }
    float norm() { return std::sqrt(x * x + y * y + z * z); }
    vec<3, Type> &normalize(Type l = 1)
    {
        *this = (*this) * (l / norm());
        return *this;
    }
    Type x, y, z;
};

template <typename Type>
struct vec<4, Type>
{
    vec() : x(Type()), y(Type()), z(Type()), w(Type()) {}
    vec(Type X, Type Y, Type Z, Type W) : x(X), y(Y), z(Z), w(W) {}
    Type &operator[](const size_t i)
    {
        assert(i < 4);
        return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w));
    }
    const Type &operator[](const size_t i) const
    {
        assert(i < 4);
        return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w));
    }
    Type x, y, z, w;
};

template <size_t DIM, typename Type>
Type operator*(const vec<DIM, Type> &lhs, const vec<DIM, Type> &rhs)
{
    Type ret = Type();
    for (size_t i = 0; i < DIM; i++)
        ret += lhs[i] * rhs[i];
    return ret;
}

template <size_t DIM, typename Type>
vec<DIM, Type> operator+(vec<DIM, Type> lhs, const vec<DIM, Type> &rhs)
{
    for (size_t i = 0; i < DIM; i++)
        lhs[i] += rhs[i];
    return lhs;
}

template <size_t DIM, typename Type>
vec<DIM, Type> operator-(vec<DIM, Type> lhs, const vec<DIM, Type> &rhs)
{
    for (size_t i = 0; i < DIM; i++)
        lhs[i] -= rhs[i];
    return lhs;
}

template <size_t DIM, typename Type, typename Other>
vec<DIM, Type> operator*(const vec<DIM, Type> &lhs, const Other &rhs)
{
    vec<DIM, Type> ret;
    for (size_t i = 0; i < DIM; i++)
        ret[i] = lhs[i] * rhs;
    return ret;
}

template <size_t DIM, typename Type>
vec<DIM, Type> operator-(const vec<DIM, Type> &lhs)
{
    return lhs * Type(-1);
}

template <typename Type>
vec<3, Type> cross(vec<3, Type> v1, vec<3, Type> v2)
{
    return vec<3, Type>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <size_t DIM, typename Type>
std::ostream &operator<<(std::ostream &out, const vec<DIM, Type> &v)
{
    for (unsigned int i = 0; i < DIM; i++)
        out << v[i] << " ";
    return out;
}
#endif // GEOMETRY_H
