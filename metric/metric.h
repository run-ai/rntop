#pragma once

#include "mutex/mutex.h"

#include "gui/window/window.h"

namespace runai
{

template <typename T>
struct Metric
{
    void store(const T & data)
    {
        const auto lock = _mutex.lock();

        _data = data;
    }

    T load() const
    {
        const auto lock = _mutex.lock();

        return _data;
    }

    operator T() const
    {
        return load();
    }

    void operator=(const T & data)
    {
        store(data);
    }

 private:
    mutable Mutex _mutex;
    T _data = {};
};

namespace metric
{

template <bool Color>
struct Common : gui::View
{
    Common() = default; // empty creation

    Common(size_t utilization, size_t used_memory, size_t total_memory) :
        utilization(utilization),
        used_memory(used_memory),
        total_memory(total_memory)
    {}

    void print(gui::Window & window) const override
    {
        const auto utilization_color = Color == false ? ncurses::Color::None :
            utilization < 10  ? ncurses::Color::Red   :
            utilization >= 80 ? ncurses::Color::Green :
                                ncurses::Color::Cyan;

        const auto used_memory_percentage = static_cast<float>(used_memory) / static_cast<float>(total_memory) * 100.f;

        const auto memory_color = Color == false ? ncurses::Color::None :
            used_memory_percentage < 50  ? ncurses::Color::Red   :
            used_memory_percentage >= 80 ? ncurses::Color::Green :
                                           ncurses::Color::Cyan;

        window.print(utilization_color, "GPU utilization: %3d%%", utilization);
        window.print("    ");
        window.print(memory_color, "Used GPU memory: %5d MiB / %-5d MiB (%.0f%%)", used_memory, total_memory, used_memory_percentage);
    }

    size_t utilization = {};
    size_t used_memory = {};
    size_t total_memory = {};
};

} // namespace metric

} // namespace runai
