#include <unordered_map>

#include "command.h"
#include "mem.h"


#if __cplusplus <= 199711L
    #define MAP_TYPE std::tr1::unordered_map
#else 
    #define MAP_TYPE std::unordered_map
#endif

template<typename T>
size_t testStdMapInsertRemoveLookup(const std::vector<Command<int> >& commands)
{
    size_t memory_size = getCurrentRSS();
    MAP_TYPE <T, int> v;
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
size_t testStdMapWalkthrough(const std::vector<Command<int> >& commands)
{
    size_t memory_size = getCurrentRSS();
    MAP_TYPE <T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(std::make_pair<T, int>(commands[i].value, 0));
        }
    }
    for(typename MAP_TYPE <T, int> ::iterator it = v.begin(); it != v.end(); ++it)
    {
        k = it->second;
    }
    return getCurrentRSS() - memory_size;
}