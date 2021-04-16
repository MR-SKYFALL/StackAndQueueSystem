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
    list<int>** stackList;
    //list <int> avaiableStack;
    bool* avaiableStack;
    const int maxAmountItemsPerStack;
    const int stackAmount;

    //queue
    queue<int>** queueList;
    const int maxAmountItemsPerQueue;
    const int queueAmount;
    

public:
    QueueAndStackSystem(const int stackAmount, const int maxAmountItemsPerStack,
        const int queueAmount, const int maxAmountItemsPerQueue)
        :stackAmount(stackAmount), maxAmountItemsPerStack(maxAmountItemsPerStack),
        queueAmount(queueAmount), maxAmountItemsPerQueue(maxAmountItemsPerQueue)
    {
        this->stackList = new list <int>*[stackAmount];
        this->queueList = new queue <int>*[queueAmount];
        this->avaiableStack = new bool[stackAmount]();
        
    }

    //----------------------
    //tools methods
    //----------------------

    bool checkIsIndexOK(int stackIndex)
    {
        // check is stack index correct
        //a) check is index beetween 0 and stackAmount
        //b) check is stack exist 
        if (stackIndex < this->stackAmount && stackIndex >= 0 && this->avaiableStack[stackIndex] == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //----------------------
    //methods
    //----------------------
    void createStack(int stackIndex)
    {
        if (stackIndex >= 0 && stackIndex <= this->maxAmountItemsPerStack)
        {
            this->avaiableStack[stackIndex] = true;
            this->stackList[stackIndex] = new list <int>;
            
            DEV_PRINT("ok -> stack created");
        }
        else
        {
            DEV_PRINT("cant create stack -> bad index");
        }
    }
    void addElementToStack(int elementToInsert, int stackIndex)
    {
        if (this->checkIsIndexOK(stackIndex))
        {
            this->stackList[stackIndex]->push_back(elementToInsert);
            // zabezpieczyæ gdy jest max elem
        }
        else
        {
            DEV_PRINT("add element -> bad stack index");
        }
    }
    void deleteElementFromStack(int stackIndex)
    {
        if (this->checkIsIndexOK(stackIndex))
        {
            this->stackList[stackIndex]->pop_front();
            // zabezpieczyæ w przypadku gdy nie ma nic do sciagnienca
        }
        else
        {
            DEV_PRINT("delete element -> bad stack index");
        }
    }
    void moveElementFromStackAToStackB(int stackIndexA, int stackIndexB)
    {
        if (this->checkIsIndexOK(stackIndexA) && this->checkIsIndexOK(stackIndexB))
        {
            int tmp = this->stackList[stackIndexA]->front();
            this->deleteElementFromStack(stackIndexA);
            this->addElementToStack(tmp, stackIndexB);
        }
        else
        {
            DEV_PRINT("move element -> bad stack index");
        }
    }
    void deleteStack(int stackIndex)
    {
        if ( this->checkIsIndexOK(stackIndex))
        {
            delete this->stackList[stackIndex];
            this->avaiableStack[stackIndex] = false;
        }
        else
        {
            DEV_PRINT("delete stack -> bad stack index");
        }
    }
    void printStack(int stackIndex)
    {
        if (this->checkIsIndexOK(stackIndex))
        {
            if (this->stackList[stackIndex]->size() == 0)
            {
                cout << "empty\n";
            }
            else
            {
                int size = this->stackList[stackIndex]->size();
                int test = this->stackList[stackIndex]->front();
                for (int i = 0; i < size; i++)
                {
                    int tmp = this->stackList[stackIndex]->back();
                    cout << tmp << " ";
                    this->stackList[stackIndex]->pop_back();
                    this->stackList[stackIndex]->push_front(tmp);
                }
                
            }
        }
    }
    void test()
    {
        cout << "test\n";
    }
};

int main()
{
    QueueAndStackSystem q1(10,10,10,10);
    q1.createStack(2);
    q1.addElementToStack(1, 2);
    q1.addElementToStack(2, 2);
    q1.addElementToStack(3, 2);
    q1.printStack(2);
   /* q1.test();*/

    
}
