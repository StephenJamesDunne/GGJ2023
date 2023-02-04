#pragma once
#include "Tooth.h"
class Incisor :
    public Tooth
{
public:
    Incisor();

    virtual bool contains(sf::Vector2f t_point) override;
private:
};

