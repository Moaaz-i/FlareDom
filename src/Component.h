#pragma once
#include "Element.h"

class Component {
public:
    virtual Element render() = 0;
};
