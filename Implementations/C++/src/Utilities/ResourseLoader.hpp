#ifndef RESOURSE_LOADER_HPP
#define RESOURSE_LOADER_HPP

#include "PDH.hpp"

class GLFWLoader
{
private:
public:
    static auto Initialize() -> bool;
};

class GLEWLoader
{
private:
public:
    static auto Initialize() -> bool;
    static auto SetPatchVertices(int count) -> void;
};

class TextFileLoader
{
private:
public:
    static auto LoadFile(const std::string &filepath) -> const std::string;
};
#endif