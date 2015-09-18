#include "command.h"
#include <QHash>
#include "mem.h"

template<typename T>
size_t testQHashInsertRemoveLookup(const std::vector<Command<T> >& commands)
{
    size_t memory_size = getCurrentRSS();
    QHash<T, int> v;
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
size_t testQHashWalkthrough(const std::vector<Command<T> >& commands)
{
    size_t memory_size = getCurrentRSS();
    QHash<T, int> v;
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(commands[i].value, 0);
        }
    }
    for(typename QHash<T, int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        k = it.value();
    }
    return getCurrentRSS() - memory_size;
}