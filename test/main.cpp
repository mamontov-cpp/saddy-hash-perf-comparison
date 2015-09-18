#include <vector>
#include <ctime>
#include <string>

#include <QString>
#include <QHash>

uint qHash(std::string a,uint b)
{
    return qHash(QString(a.c_str()), b);    
}

#include <timer.h>

#include "command.h"
#include "testhash.h"
#include "testqhash.h"
#include "testptrie.h"
#include "teststdmap.h"
#include "testboostmap.h"
#include "testdensehashmap.h"

#include <google/sparse_hash_map>





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



void produceCommands(std::vector<Command<long long> >& commands, size_t count)
{
    std::vector<int> values;
    commands.clear();
    for(size_t i = 0; i < count; i++)
    {
        values.push_back(rand());
    }
    for(size_t i = 0; i < values.size(); i++)
    {
        Command<long long> t;
        t.type = Command<long long>::ADD;
        t.value = values[i];
        commands.push_back(t);
    }


    for(size_t i = 0; i < values.size() * 2; i++)
    {
        Command<long long> t;
        t.type = Command<long long>::REMOVE;
        if (i >= values.size())
        {
            t.type = Command<long long>::LOOKUP;
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


void produceCommands(std::vector<Command<std::string> >& commands, size_t count)
{
    std::vector<std::string> values;
    commands.clear();
    for(size_t i = 0; i < count; i++)
    {
        std::string v;
        size_t length = rand() % 200;
        for(size_t j = 0; j < length; j++)
        {
            v.push_back( rand() % 50 + 26);
        }
        values.push_back(v);
    }
    for(size_t i = 0; i < values.size(); i++)
    {
        Command<std::string> t;
        t.type = Command<std::string>::ADD;
        t.value = values[i];
        commands.push_back(t);
    }


    for(size_t i = 0; i < values.size() * 2; i++)
    {
        Command<std::string> t;
        t.type = Command<std::string>::REMOVE;
        if (i >= values.size())
        {
            t.type = Command<std::string>::LOOKUP;
        }
        if (rand() % 1000 < 500)
        {
            t.value = "abcde";
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
    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));

    int counts[5] = { 100, 1000, 10000, 100000, 1000000};
    {
        for(int i = 0; i < 5; i++)
        {
            std::vector<Command<int> > commands;
            produceCommands(commands, counts[i]);
            sad::Timer timer;
            size_t mem;

            printf("\n\n\nTests insert-remove-lookup %d (ms):\n", counts[i]);

            printf("\n\nint:\n");
            timer.start();
            mem = testSadHashInsertRemoveLookup<int>(commands);
            timer.stop();
            printf("sad::Hash: %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testQHashInsertRemoveLookup<int>(commands);
            timer.stop();
            printf("QHash: %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testPtrieInsertRemoveLookup<int>(commands);
            timer.stop();
            printf("hst::ptrie %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testStdMapInsertRemoveLookup<int>(commands);
            timer.stop();
            printf("std::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testBoostMapInsertRemoveLookup<int>(commands);
            timer.stop();
            printf("boost::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testDenseMapInsertRemoveLookup<int>(commands);
            timer.stop();
            printf("google::dense_hash_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);

            printf("\n\n\nTests walkthrough  %d (ms):\n", counts[i]);

            printf("\n\nint:\n");
            timer.start();
            testSadHashWalkthrough<int>(commands);
            timer.stop();
            printf("sad::Hash: %lf %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            testQHashWalkthrough<int>(commands);
            timer.stop();
            printf("QHash: %lf %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testPtrieWalkthrough<int>(commands);
            timer.stop();
            printf("hst::ptrie %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testStdMapWalkthrough<int>(commands);
            timer.stop();
            printf("std::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testBoostMapWalkthrough<int>(commands);
            timer.stop();
            printf("boost::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testDenseMapWalkthrough<int>(commands);
            timer.stop();
            printf("google::dense_hash_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);

        }
    }

    
    {
        for(int i = 0; i < 5; i++)
        {
            std::vector<Command<long long> > commands;
            produceCommands(commands, counts[i]);
            sad::Timer timer;
            size_t mem;

            printf("\n\n\nTests insert-remove-lookup %d (ms):\n", counts[i]);

            printf("\n\nlong long:\n");
            timer.start();
            mem = testSadHashInsertRemoveLookup<long long>(commands);
            timer.stop();
            printf("sad::Hash: %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testQHashInsertRemoveLookup<long long>(commands);
            timer.stop();
            printf("QHash: %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testPtrieInsertRemoveLookup<long long>(commands);
            timer.stop();
            printf("hst::ptrie %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testStdMapInsertRemoveLookup<long long>(commands);
            timer.stop();
            printf("std::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testBoostMapInsertRemoveLookup<long long>(commands);
            timer.stop();
            printf("boost::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testDenseMapInsertRemoveLookup<long long>(commands);
            timer.stop();
            printf("google::dense_hash_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);

            printf("\n\n\nTests walkthrough  %d (ms):\n", counts[i]);

            printf("\n\n long long:\n");
            timer.start();
            testSadHashWalkthrough<long long>(commands);
            timer.stop();
            printf("sad::Hash: %lf %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            testQHashWalkthrough<long long>(commands);
            timer.stop();
            printf("QHash: %lf %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testPtrieWalkthrough<long long>(commands);
            timer.stop();
            printf("hst::ptrie %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testStdMapWalkthrough<long long>(commands);
            timer.stop();
            printf("std::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testBoostMapWalkthrough<long long>(commands);
            timer.stop();
            printf("boost::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testDenseMapWalkthrough<long long>(commands);
            timer.stop();
            printf("google::dense_hash_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);

        }
    }
    
    {
        for(int i = 0; i < 5; i++)
        {
            std::vector<Command<std::string> > commands;
            produceCommands(commands, counts[i]);
            sad::Timer timer;
            size_t mem;

            printf("\n\n\nTests insert-remove-lookup %d (ms):\n", counts[i]);

            printf("\n\nstd::string:\n");
            timer.start();
            mem = testSadHashInsertRemoveLookup<std::string>(commands);
            timer.stop();
            printf("sad::Hash: %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testQHashInsertRemoveLookup<std::string>(commands);
            timer.stop();
            printf("QHash: %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            printf("hst::ptrie INF  INF\n");
            timer.start();
            mem = testStdMapInsertRemoveLookup<std::string>(commands);
            timer.stop();
            printf("std::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testBoostMapInsertRemoveLookup<std::string>(commands);
            timer.stop();
            printf("boost::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            printf("google::dense_hash_map INF  INF\n");

            printf("\n\n\nTests walkthrough  %d (ms):\n", counts[i]);

            printf("\n\n long long:\n");
            timer.start();
            testSadHashWalkthrough<std::string>(commands);
            timer.stop();
            printf("sad::Hash: %lf %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            testQHashWalkthrough<std::string>(commands);
            timer.stop();
            printf("QHash: %lf %lf\n", timer.elapsed(), mem / 1024.0);
            printf("hst::ptrie INF  INF\n");
            timer.start();
            mem = testStdMapWalkthrough<std::string>(commands);
            timer.stop();
            printf("std::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            timer.start();
            mem = testBoostMapWalkthrough<std::string>(commands);
            timer.stop();
            printf("boost::unordered_map %lf  %lf\n", timer.elapsed(), mem / 1024.0);
            printf("google::dense_hash_map INF  INF\n");

        }
    }
    return 0;
}
