#include <vector>
#include <ctime>

#include <timer.h>

#include "command.h"
#include "testhash.h"


void produceCommands(std::vector<Command<int> >& commands, size_t count)
{
    std::vector<int> values;
    commands.clear();
    for(size_t i = 0; i < count; i++)
    {
        values.push_back(rand());
    }
    for(size_t i = 0; i < values.size(); i++)
    {
        Command<int> t;
        t.type = Command<int>::ADD;
        t.value = values[i];
        commands.push_back(t);
    }


    for(size_t i = 0; i < values.size() * 2; i++)
    {
        Command<int> t;
        t.type = Command<int>::REMOVE;
        if (i >= values.size())
        {
            t.type = Command<int>::LOOKUP;
        }
        if (rand() % 1000 < 500)
        {
            t.value = rand();
        }
        else
        {
            t.value = values[rand() % count];
        }
        commands.push_back(t);
    }

}



int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::vector<Command<int> > commands;
    produceCommands(commands, 100);
    sad::Timer timer;
    size_t mem;

    printf("Tests insert-remove-lookup (ms):\n");

    printf("\n\nint:\n");
    timer.start();
    mem = testSadHashInsertRemoveLookup<int>(commands);
    timer.stop();
    printf("sad::Hash: %lf  %lf\n", timer.elapsed(), mem / 1024.0);


    printf("Tests walkthrough (ms):\n");

    printf("\n\nint:\n");
    timer.start();
    testSadHashWalkthrough<int>(commands);
    timer.stop();
    printf("sad::Hash: %lf %lf\n", timer.elapsed(), mem / 1024.0);

    return 0;
}
