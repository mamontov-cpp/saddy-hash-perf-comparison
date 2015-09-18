#include <google/dense_hash_map>
#include "command.h"
#include "mem.h"



template<typename T>
size_t testDenseMapInsertRemoveLookup(const std::vector<Command<T> >& commands)
{
    size_t memory_size = getCurrentRSS();
    google::dense_hash_map<T, int> v;
    v.set_empty_key(INT_MAX);
    v.set_deleted_key(INT_MAX - 1);
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(std::make_pair<T, int>(commands[i].value, 0));
        }

        if (commands[i].type == Command<T>::REMOVE)
        {
            // Yeah, we need to call that, because repeating erases gonna break our hash table
            if (v.find(commands[i].value) != v.end())
            {
                v.erase(commands[i].value);
            }
        }

        if (commands[i].type == Command<T>::LOOKUP)
        {
            k = v[commands[i].value];
        }
    }
    return getCurrentRSS() - memory_size;
}

template<typename T>
size_t testDenseMapWalkthrough(const std::vector<Command<T> >& commands)
{
    size_t memory_size = getCurrentRSS();
    google::dense_hash_map<T, int> v;
    v.set_empty_key(INT_MAX);
    v.set_deleted_key(INT_MAX - 1);
    int k = 0;
    for(size_t i = 0 ; i < commands.size(); i++)
    {
        if (commands[i].type == Command<T>::ADD)
        {
            v.insert(std::make_pair<T, int>(commands[i].value, 0));
        }
    }
    for(typename google::dense_hash_map<T, int> ::iterator it = v.begin(); it != v.end(); ++it)
    {
        k = it->second;
    }
    return getCurrentRSS() - memory_size;
}