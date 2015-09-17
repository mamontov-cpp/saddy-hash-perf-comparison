/*! \file command.h
    
    A command of tested program
 */
#pragma once
#include <vector>


template<typename T>
struct Command
{
    enum Type
    {
        ADD = 0,
        REMOVE = 1,
        LOOKUP = 2
    } type;
    T value;
};