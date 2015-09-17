#include <boost/unordered/unordered_map.hpp>
#include "command.h"
#include "mem.h"



template<typename T>
size_t testBoostMapInsertRemoveLookup(const std::vector<Command<int> >& commands)
{
    size_t memory_size = getCurrentRSS();
    boost::unordered_map<T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(std::make_pair<T, int>(commands[i].value, 0));
        }

        if (commands[i].type == Command<T>::REMOVE)
        {
            v.erase(commands[i].value);
        }

        if (commands[i].type == Command<T>::LOOKUP)
        {
            k = v[commands[i].value];
        }
    }
    return getCurrentRSS() - memory_size;
}

template<typename T>
size_t testBoostMapWalkthrough(const std::vector<Command<int> >& commands)
{
    size_t memory_size = getCurrentRSS();
    boost::unordered_map<T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(std::make_pair<T, int>(commands[i].value, 0));
        }
    }
    for(typename boost::unordered_map<T, int> ::iterator it = v.begin(); it != v.end(); ++it)
    {
        k = it->second;
    }
    return getCurrentRSS() - memory_size;
}