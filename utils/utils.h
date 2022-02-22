#pragma once

#include <functional>
#include <numeric>
#include <set>
#include <string>
#include <vector>

namespace runai::utils
{

namespace string
{

std::string join(const std::vector<std::string> & elements, char delimiter);
std::vector<std::string> split(const std::string & str, char delimiter);
std::string strip(std::string && str, const std::set<char> & chars = { ' ', '\r', '\n' });

} // namespace string

template <typename R, typename T>
using Op = std::function<R(const T &)>;

template <typename R, typename Iterator>
R sum(const Iterator & v, const Op<R, typename Iterator::value_type> & op)
{
    return std::accumulate(v.begin(), v.end(), static_cast<R>(0), [&](R value, const typename Iterator::value_type & t){ return value + op(t); });
}

template <typename R, typename Iterator>
R avg(const Iterator & v, const Op<R, typename Iterator::value_type> & op)
{
    return sum<R, Iterator>(v, op) / v.size();
}

} // namespace runai::utils
