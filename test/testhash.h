#include "command.h"
#include "sadhash.h"
#include "mem.h"

template<typename T>
size_t testSadHashInsertRemoveLookup(const std::vector<Command<int> >& commands)
{
    size_t memory_size = getCurrentRSS();
    sad::Hash<T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(commands[i].value, 0);
        }

        if (commands[i].type == Command<T>::REMOVE)
        {
            v.remove(commands[i].value);
        }

        if (commands[i].type == Command<T>::LOOKUP)
        {
            k = v[commands[i].value];
        }
    }
    return getCurrentRSS() - memory_size;
}

template<typename T>
size_t testSadHashWalkthrough(const std::vector<Command<int> >& commands)
{
    size_t memory_size = getCurrentRSS();
    sad::Hash<T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(commands[i].value, 0);
        }
    }
    for(typename sad::Hash<T, int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        k = it.value();
    }
    return getCurrentRSS() - memory_size;
}