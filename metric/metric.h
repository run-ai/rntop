#pragma once

#include "mutex/mutex.h"

#include "gui/window/window.h"

#include "unit/unit.h"

#include "utils/utils.h"

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

    Common(size_t utilization, double used_memory, double total_memory, Unit unit) :
        utilization(utilization),
        used_memory(used_memory),
        total_memory(total_memory),
        unit(unit)
    {}

    void print(gui::Window & window) const override
    {
        const auto utilization_color = Color == false ? ncurses::Color::None :
            utilization < 10  ? ncurses::Color::Red   :
            utilization >= 80 ? ncurses::Color::Green :
                                ncurses::Color::Cyan;

        const auto used_memory_percentage = used_memory / total_memory * 100.f;

        const auto memory_color = Color == false ? ncurses::Color::None :
            used_memory_percentage < 50  ? ncurses::Color::Red   :
            used_memory_percentage >= 80 ? ncurses::Color::Green :
                                           ncurses::Color::Cyan;

        window.print(utilization_color, "GPU utilization: %3d%%", utilization);
        window.print("    ");

        const auto symbol = utils::unit::symbol(unit);

        if (unit < Unit::GB)
        {
            window.print(memory_color, "Used GPU memory: %5d %s / %-5d %s (%.0f%%)",
                static_cast<size_t>(used_memory), symbol.c_str(),
                static_cast<size_t>(total_memory), symbol.c_str(),
                used_memory_percentage);
        }
        else
        {
            window.print(memory_color, "Used GPU memory: %.2f %s / %-.2f %s (%.0f%%)",
                used_memory, symbol.c_str(),
                total_memory, symbol.c_str(),
                used_memory_percentage);
        }
    }

    Common convert(Unit to)
    {
        return Common
            {
                .utilization = utilization,
                .used_memory = utils::unit::convert(used_memory, unit, to),
                .total_memory = utils::unit::convert(total_memory, unit, to),
                .unit = to,
            };
    }

    size_t utilization = {};
    double used_memory = {};
    double total_memory = {};
    Unit unit;
};

} // namespace metric

} // namespace runai
