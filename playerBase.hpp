#pragma once

#include "context.hpp"

using namespace std;

class PlayerBase
{
public:
    PlayerBase(char color);
    virtual pair<int, int> makeMove() = 0;
    virtual void lookTable(vector<vector<char>> table, vector<pair<int, int>>) = 0;
    char getColor();

protected:
    char color;
};

PlayerBase::PlayerBase(char color)
{
    this->color = color;
}

char PlayerBase::getColor()
{
    return color;
}