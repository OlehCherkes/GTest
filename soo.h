#pragma once
#include <iostream>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <chrono>

template <typename T = uint8_t, size_t size = 128>
struct Soo {
    Soo() = delete;
    Soo(Soo&& s) noexcept : m_nBytes(s.m_nBytes)
    {
        if (s.m == &s.o[0])
        {
            memmove(&o[0], &s.o[0], m_nBytes);
            m = &o[0];
        }
        else {
            m = s.m;
        }
        s.m = nullptr;
        s.m_nBytes = 0;
    }

    Soo(size_t nBytes) noexcept : m(size < nBytes ? new T[nBytes] : &o[0]), m_nBytes(nBytes) {}

    Soo(size_t nBytes, const T& v) noexcept : Soo(nBytes)
    {
        std::fill(&m[0], &m[m_nBytes], v);
    }

    ~Soo() { if (m != &o[0]) { delete[] m; } }

    T& operator[](size_t idx) noexcept { return m[idx]; }
    const T& operator[](size_t idx) const noexcept { return m[idx]; }

    T* m;
private:
    size_t m_nBytes;
    T o[size];
};