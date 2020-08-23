#ifndef M_VECTOR_UTIL_HPP
#define M_VECTOR_UTIL_HPP

// Use this to exclude ostream overload to decrease size of header
#define TO_STRING

// Use this to change / remove namespace name
#define NAMESPACE mp

// USe this to exclude type alias & typedefs (vec<D>, vec3, vec2, ...)
#define INCLUDE_TYPE_ALIAS

#include <cstdint>
#include <cmath>
#include <array>

#ifdef TO_STRING
#include <ostream>
#endif

#ifdef NAMESPACE
namespace NAMESPACE
{
#endif

template <typename T, std::size_t D>
class m_vector
{
private:

    using ArrayType = std::array<T, D>;

    ArrayType _data;

public:

    m_vector(const ArrayType& data): _data{data} {}
    m_vector(): _data{} {}

    m_vector(const m_vector&) = default;
    m_vector& operator=(const m_vector&) = default;
    
    ~m_vector() {}

    std::size_t size() const {return D;}

    T dot(const m_vector& rhs) const
    {
        T out = T();
        for (int i = 0; i < D;++i)
        {
            out += _data[i] * rhs._data[i];
        }
        return out;
    }

    T mag() const { return std::sqrt(dot(*this)); }

    m_vector normalize() const { return (*this) / mag(); }

    T distance_to(const m_vector& rhs) const 
    {
        T out = T();
        for (int i = 0;i < D;++i)
        {
            out += (rhs._data[i] - this->_data[i]) * (rhs._data[i] - this->_data[i]);   
        }
        return std::sqrt(out);
    }

    T& operator[](int index) const { return _data[index]; }

    T& at(int index) const { return _data.at(index); }

    m_vector& operator+=(const m_vector& rhs)
    {
        for (int i = 0; i < D;++i)
        {
            _data[i] += rhs._data[i];
        }
        return *this;
    }

    m_vector& operator+=(const T& rhs)
    {
        for (auto& el : _data)
        {
            el += rhs;
        }
        return *this;
    }

    friend m_vector operator+(m_vector lhs, const m_vector& rhs) { return lhs += rhs; }

    friend m_vector operator+(m_vector lhs, const T& rhs) { return lhs += rhs; }

    friend m_vector operator+(const T& lhs, const m_vector& rhs ) { return rhs + lhs; }

    m_vector& operator-=(const m_vector& rhs)
    {
        for (int i = 0; i < D;++i)
        {
            _data[i] -= rhs._data[i];
        }
        return *this;
    }

    m_vector& operator-=(const T& rhs)
    {
        for (auto& el : _data)
        {
            el -= rhs;
        }
        return *this;
    }

    friend m_vector operator-(m_vector lhs, const m_vector& rhs) { return lhs -= rhs; }

    friend m_vector operator-(m_vector lhs, const T& rhs) { return lhs -= rhs; }

    friend m_vector operator-(const T& lhs, const m_vector& rhs ) 
    {
        ArrayType data;
        for (int i = 0; i < D;++i)
        {
            data[i] = lhs - rhs._data[i];
        }
        return m_vector(data);
    }

    m_vector& operator*=(const m_vector& rhs)
    {
        for (int i = 0; i < D;++i)
        {
            _data[i] *= rhs._data[i];
        }
        return *this;
    }

    m_vector& operator*=(const T& rhs)
    {
        for (auto& el : _data)
        {
            el *= rhs;
        }
        return *this;
    }

    friend m_vector operator*(m_vector lhs, const m_vector& rhs) { return lhs *= rhs; }

    friend m_vector operator*(m_vector lhs, const T& rhs) { return lhs *= rhs; }

    friend m_vector operator*(const T& lhs, const m_vector& rhs ) { return rhs * lhs; }

    m_vector& operator/=(const m_vector& rhs)
    {
        for (int i = 0; i < D;++i)
        {
            _data[i] /= rhs._data[i];
        }
        return *this;
    }

    m_vector& operator/=(const T& rhs)
    {
        for (auto& el : _data)
        {
            el /= rhs;
        }
        return *this;
    }

    friend m_vector operator/(m_vector lhs, const m_vector& rhs) { return lhs /= rhs; }

    friend m_vector operator/(m_vector lhs, const T& rhs) { return lhs /= rhs; }

    friend m_vector operator/(const T& lhs, const m_vector& rhs)
    {
        ArrayType data;
        for (int i = 0; i < D;++i)
        {
            data[i] = lhs / rhs._data[i];
        }
        return m_vector(data);
    }

    #ifdef TO_STRING
    friend std::ostream& operator<<(std::ostream& os, const m_vector& rhs)
    {
        os << " { ";
        int i;
        for (i = 0; i < D-1;++i)
        {
            os << rhs._data[i] << ", ";
        }
        os << rhs._data[i] << " } ";
        return os;
    }
    #endif

};

#ifdef INCLUDE_TYPE_ALIAS

template <std::size_t D>
using vec = m_vector<double, D>;

typedef vec<2> vec2;
typedef vec<3> vec3;

#endif

#ifdef NAMESPACE
}
#endif

#endif