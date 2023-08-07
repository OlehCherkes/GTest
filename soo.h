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

class Events {
public:
    enum class EventId {
        __END
    };

    int update(int delta) {
        return 0;
    }

    EventId wait_for_event() {
        return EventId::__END;
    }
};

class PirCamEsp32 {
public:
    bool mainloop() {
        auto now = std::chrono::steady_clock::now();
        auto delta = now - sysTick;

        while (true) {
            auto minTimer = events.update(std::chrono::duration_cast<std::chrono::milliseconds>(delta).count());
            delta = {};

            auto e = events.wait_for_event();
            if (e == Events::EventId::__END) {
                m_board.startTimer([this]() {
                    return this->mainloop();
                }, minTimer);

                sysTick = std::chrono::steady_clock::now();
                break;
            }
            eventProcessing(e);
        }

        return true;
    }

private:
    Events events;
    std::chrono::steady_clock::time_point sysTick;

    void eventProcessing(Events::EventId e)
    {
        std::cout << "Processing event: " << static_cast<int>(e) << std::endl;
    }

};

bool IRfBoard::startTimer(std::function<bool()> cb, uint32_t msSec) {
    m_tmrHw.expires_after(asio::chrono::milliseconds(msSec));
    m_tmrHw.async_wait(
        [this, cb](const asio::error_code& ec) {
            if (!ec) {
                if (cb()) {

                } else {

                }
            } else {

            }
        }
    );
    return true;
}