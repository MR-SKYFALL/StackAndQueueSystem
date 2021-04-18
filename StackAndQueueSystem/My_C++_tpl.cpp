#include <iostream>
#include <string>
#include <queue> // to usuniecia
#include <list>
using namespace std;
bool IS_PRINT = false;

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
    bool* isStackExist;
    const int maxAmountItemsPerStack;
    const int stackAmount;

    //queue
    list<int>** queueList;
    bool* isQueueExist;
    const int maxAmountItemsPerQueue;
    const int queueAmount;
    

public:
    QueueAndStackSystem(const int stackAmount, const int maxAmountItemsPerStack,
        const int queueAmount, const int maxAmountItemsPerQueue)
        :stackAmount(stackAmount), maxAmountItemsPerStack(maxAmountItemsPerStack),
        queueAmount(queueAmount), maxAmountItemsPerQueue(maxAmountItemsPerQueue)
    {
        this->stackList = new list <int>*[stackAmount];
        this->isStackExist = new bool[stackAmount]();

        this->queueList = new list <int>*[queueAmount];
        this->isQueueExist = new bool[queueAmount]();
    }

    //----------------------
    //tools methods
    //----------------------

    bool stackCheckIsIndexOK(int stackIndex)
    {
        // check is stack index correct
        //a) check is index beetween 0 and stackAmount
        //b) check is stack exist 
        if (stackIndex < this->stackAmount && stackIndex >= 0 && this->isStackExist[stackIndex] == true)
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
            this->isStackExist[stackIndex] = true;
            this->stackList[stackIndex] = new list <int>;
            
            DEV_PRINT("ok -> stack created");
        }
        else
        {
            DEV_PRINT("cant create stack -> bad index");
        }
    }
    void createQueue(int queueIndex)
    {
        if (queueIndex >= 0 && queueIndex <= this->maxAmountItemsPerQueue)
        {
            this->isStackExist[queueIndex] = true;
            this->stackList[queueIndex] = new list <int>;

            DEV_PRINT("ok -> queue created");
        }
        else
        {
            DEV_PRINT("cant create queue -> bad index");
        }
    }
    void addElementToStack( int stackIndex, int elementToInsert)
    {
        if (this->stackCheckIsIndexOK(stackIndex))
        {
            
            if (this->stackList[stackIndex]->size() < this->maxAmountItemsPerStack)
            {
                this->stackList[stackIndex]->push_front(elementToInsert);
            }
            else
            {
                cout << "error: stack is full\n";
            }
        }
        else
        {
            DEV_PRINT("add element -> bad stack index");
        }
    }
    void deleteElementFromStack(int stackIndex)
    {
        if (this->stackCheckIsIndexOK(stackIndex))
        {
            if (this->stackList[stackIndex]->size() > 0)
            {
                this->stackList[stackIndex]->pop_front();
            }
            else
            {
                cout << "error: stack is empty\n";
            }
        }
        else
        {
            DEV_PRINT("delete element -> bad stack index");
        }
    }
    void moveElementFromStackAToStackB(int stackIndexA, int stackIndexB)
    {
        if (this->stackCheckIsIndexOK(stackIndexA) && this->stackCheckIsIndexOK(stackIndexB))
        {
            int tmp = this->stackList[stackIndexA]->front();
            this->deleteElementFromStack(stackIndexA);
            this->addElementToStack(stackIndexB, tmp );
        }
        else
        {
            DEV_PRINT("move element -> bad stack index");
        }
    }
    void deleteStack(int stackIndex)
    {
        if ( this->stackCheckIsIndexOK(stackIndex))
        {
            delete this->stackList[stackIndex];
            this->isStackExist[stackIndex] = false;
        }
        else
        {
            DEV_PRINT("delete stack -> bad stack index");
        }
    }
    void printStack(int stackIndex)
    {
        if (this->stackCheckIsIndexOK(stackIndex))
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
                cout << "\n";
            }
            
        }
    }
    void frontendCore()
    {
        list<string> commandListToExecute;

        //--------------
        //test-1
        //--------------
        /*commandListToExecute.push_back("new_s 0"); 
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
        commandListToExecute.push_back("print_s 0");*/


        //--------------
        //test-2
        //--------------
        commandListToExecute.push_back("new_s 0");
        commandListToExecute.push_back("push 0 96");
        commandListToExecute.push_back("new_s 5");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("push 5 28");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("push 5 33");
        commandListToExecute.push_back("push 5 88");
        commandListToExecute.push_back("pop 0");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("pop 0");
        commandListToExecute.push_back("push 0 65");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("push 5 13");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("push 5 1");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("push 5 0");
        commandListToExecute.push_back("push 5 9");
        commandListToExecute.push_back("push 5 87");
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
            DEV_PRINT(simpleCommand);
            list<string> commandArguments = this->splitString(simpleCommand," ");
            string operationType = commandArguments.front();
            commandArguments.pop_front();
            
            if (operationType == "new_s") 
            {
                int arg1 = returnNextArgument(commandArguments);
                this->createStack(arg1);
            }
            else if (operationType == "push")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->addElementToStack(arg1, arg2);
            }
            else if (operationType == "pop")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->deleteElementFromStack(arg1);
            }
            else if (operationType == "stack->stack")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->moveElementFromStackAToStackB(arg1, arg2);
            }
            else if (operationType == "delete_s")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->deleteStack(arg1);
            }
            else if (operationType == "print_s")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->printStack(arg1);
            }
        }
            
    }
    int returnNextArgument(list<string> &command)
    {
        string argument1 = command.front();
        command.pop_front();
        int value1 = stoi(argument1);
        return value1;
    }
    
  
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

    // TODO
    // stack a->b bad stack index
}
