#include <iostream>
#include <string>
#include <queue> // to usuniecia
#include <list>
using namespace std;
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

    list<string> splitString(string text, string separator)
    {
        int  foundSeparator = text.find(separator);
        int indexStart = 0;
        list <string> arguments;
        if (foundSeparator != -1)
        {
            while (true)
            {
                string textToPush = text.substr(indexStart, foundSeparator - indexStart);
                arguments.push_back(textToPush);
                text = text.substr(foundSeparator + 1);
                foundSeparator = text.find(separator);
                if (foundSeparator == -1)
                {
                    arguments.push_back(text);
                    break;
                }
            }
        }
        return arguments;
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
    void frontendCore()
    {
        list<string> commandListToExecute;
        commandListToExecute.push_back("new_s 0");
        commandListToExecute.push_back("push 0 96");
        commandListToExecute.push_back("new_s 5");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("push 5 28");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("push 5 88");
        commandListToExecute.push_back("pop 0");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("push 0 65");
        commandListToExecute.push_back("stack->stack 5 0");
        commandListToExecute.push_back("print_s 0");


        /*while (true)
        {
            string commandToExecute;
            getline(cin, commandToExecute);
            if (commandToExecute == "")
            {
                break;
            }
            commandListToExecute.push_back(commandToExecute);
        }*/
        for (auto simpleCommand : commandListToExecute)
        {
            cout << simpleCommand << "\n";
            list<string> commandArguments = this->splitString(simpleCommand," ");
            string operationType = commandArguments.front();
            commandArguments.pop_front();
            
            if (operationType == "new_s") 
            {
                
                string argument1 = commandArguments.front();
                int value1 = stoi(argument1);
                this->createStack(value1);
            }
            else if (operationType == "push")
            {
                string argument1 = commandArguments.front();
                commandArguments.pop_front();
                string argument2 = commandArguments.front();

                int value1 = stoi(argument1);
                int va

            }
            else if (operationType == "pop")
            {

            }
            else if (operationType == "stack->stack")
            {

            }
            else if (operationType == "delete_s")
            {

            }
            else if (operationType == "print_s")
            {

            }
        }
            
    }
    int returnArgumentFromCommand()
  
};

int main()
{/*
    QueueAndStackSystem q1(10,10,10,10);
    q1.createStack(2);
    q1.addElementToStack(1, 2);
    q1.addElementToStack(2, 2);
    q1.addElementToStack(3, 2);
    q1.printStack(2);*/
   /* q1.test();*/


    QueueAndStackSystem q1(10, 10, 10, 10);
    q1.frontendCore();
    //q1.splitString("test1 testt2 testtt3", " ");

}
