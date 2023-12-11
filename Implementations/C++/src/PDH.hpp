#ifndef EVSYSTEM_HPP
#define EVSYSTEM_HPP

#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>

#include "Utilities/StringView.hpp"

using Timestep = float;

using Size = std::size_t;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using Scoped = std::unique_ptr<T>;

#endif