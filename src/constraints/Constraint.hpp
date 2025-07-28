#pragma once
#include <vector>
#include "../core/VerletObject.hpp"

class Constraint {
public:
    virtual void apply(std::vector<VerletObject>& objects) const = 0;
    virtual ~Constraint() = default;
};
