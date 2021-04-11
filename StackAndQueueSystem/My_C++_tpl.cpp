#include <iostream>
#include <string>
#include <stack> 
#include <queue>
#include <list>
using namespace std;

void frontendCore()
{
    while (true)
    {
        string commandToExecute;
        getline(cin, commandToExecute);
        if (commandToExecute == "")
        {
            break;
        }
    }
}

class QueueAndStackSystem
{
private:
    //stacks
    const int stackAmount;
    const int maxAmountItemsPerStack;
    stack<int>* avaiableStack;
    //queue
    const int queueAmount;
    const int maxAmountItemsPerQueue;
    queue<int>* avaiableQueue;
public:
    QueueAndStackSystem()
        :stackAmount(10), maxAmountItemsPerStack(10), queueAmount(10), maxAmountItemsPerQueue(10)
    {
        avaiableStack = new stack<int>[stackAmount];
        avaiableQueue = new queue<int>[queueAmount];
    }
};

int main()
{

}
