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

bool IS_PRINT = true;

void DEV_PRINT(string msg)
{
    if (IS_PRINT)
    {
        cout << msg << "\n";
    }
}

class QueueAndStackSystem
{
private:
    //stacks
    stack<int>** avaiableStack;
    const int maxAmountItemsPerStack;
    const int stackAmount;

    //queue
    queue<int>** avaiableQueue;
    const int maxAmountItemsPerQueue;
    const int queueAmount;
    

public:
    QueueAndStackSystem(const int stackAmount, const int maxAmountItemsPerStack,
        const int queueAmount, const int maxAmountItemsPerQueue)
        :stackAmount(stackAmount), maxAmountItemsPerStack(maxAmountItemsPerStack),
        queueAmount(queueAmount), maxAmountItemsPerQueue(maxAmountItemsPerQueue)
    {
        avaiableStack = new stack <int>*[stackAmount];
        avaiableQueue = new queue <int>*[queueAmount];
    }
    void createStack(int stackIndex)
    {
        if (stackIndex <= 0 && stackIndex <= this->maxAmountItemsPerStack)
        {
            avaiableStack[stackIndex] = new stack <int>;
            DEV_PRINT("ok -> stack created");
        }
        else
        {
            DEV_PRINT("cant create stack -> bad index");
        }
    }
};



int main()
{
    QueueAndStackSystem q1(10,10,10,10);
    q1.createStack(11);
}
