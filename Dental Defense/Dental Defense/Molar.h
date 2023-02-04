#pragma once
#include "Tooth.h"
class Molar :
    public Tooth
{
public:
    Molar();

    virtual bool contains(sf::Vector2f t_point) override;

private:
};

