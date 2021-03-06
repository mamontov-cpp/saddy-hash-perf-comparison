#include "command.h"
#include "old/hptrie.hpp"
#include "mem.h"

template<typename T>
size_t testPtrieInsertRemoveLookup(const std::vector<Command<T> >& commands)
{
    size_t memory_size = getCurrentRSS();
    hst::ptrie<T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.add(commands[i].value, 0);
        }

        if (commands[i].type == Command<T>::REMOVE)
        {
            v.remove(commands[i].value);
        }

        if (commands[i].type == Command<T>::LOOKUP)
        {
            int* r = v[commands[i].value];
            if (r)
            {
               k = *r;
            }
        }
    }
    return getCurrentRSS() - memory_size;
}

template<typename T>
size_t testPtrieWalkthrough(const std::vector<Command<T> >& commands)
{
    size_t memory_size = getCurrentRSS();
    hst::ptrie<T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.add(commands[i].value, 0);
        }
    }
    for(typename hst::ptrie<T, int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        k = it.value();
    }
    return getCurrentRSS() - memory_size;
}