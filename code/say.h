#pragma once
#include "component.h"
#include <iostream>

class Say :public Component
{
public:
    void Update()
    {
        if (pOwner)
        {
            std::cout << (pOwner->root)->getLocalPosition() << '\n';
        }
    }
};