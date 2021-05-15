#include <iostream>
#include <string>
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

class OperationResult
{
private:
    int item;
    bool is_succesful;
public:
    OperationResult(int item, bool is_succesful)
        :item(item), is_succesful(is_succesful)
    {}
    int getItem()
    {
        return this->item;
    }
    bool getResult()
    {
        return this->is_succesful;
    }
};

class SimpleStructure 
{
protected:
    list<int>** structureList;
    bool* isStructureExist;
    const int maxAmountItemsPerStructure;
    const int structureAmount;
public:
    SimpleStructure(const int structureAmount, const int maxAmountItemsPerStructure)
        :structureAmount(structureAmount), maxAmountItemsPerStructure(maxAmountItemsPerStructure)
    {
        this->structureList = new list <int>*[structureAmount];
        this->isStructureExist = new bool[structureAmount]();
    }
    OperationResult createStructure(int structureIndex)
    {
        if (structureIndex >= 0 && structureIndex <= this->maxAmountItemsPerStructure)
        {
            this->isStructureExist[structureIndex] = true;
            this->structureList[structureIndex] = new list <int>;
            return OperationResult(structureIndex, true);
        }
        else
        {
            return OperationResult(structureIndex, false);
        }
    }
    OperationResult deleteStructure(int structureIndex)
    {
        if (this->CheckIsStructureIndexOK(structureIndex))
        {
            delete this->structureList[structureIndex];
            this->isStructureExist[structureIndex] = false;
            return OperationResult(structureIndex, true);
        }
        else
        {
            return OperationResult(structureIndex, false);
        }
    }
protected:
    bool CheckIsStructureIndexOK(int structureIndex)
    {
        // check is stack index correct
        //a) check is index beetween 0 and stackAmount
        //b) check is stack exist 
        if (structureIndex < this->structureAmount && structureIndex >= 0 && this->isStructureExist[structureIndex] == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool checkCanAddElementToStructure(int structureIndex, int elementToInsert)
    {
        if (this->CheckIsStructureIndexOK(structureIndex))
        {

            if (this->structureList[structureIndex]->size() < this->maxAmountItemsPerStructure)
            {
                return true;
            }
            else
            {
                cout << "error: structure is full\n";
                return false;
            }
        }
        else
        {
            DEV_PRINT("add element -> bad structure index");
            return false;
        }
    }
    bool checkCanDeleteElementFromStructure(int structureIndex)
    {
        if (this->CheckIsStructureIndexOK(structureIndex))
        {
            if (this->structureList[structureIndex]->size() > 0)
            {
                return true;
            }
            else
            {
                cout << "error: structure is empty\n";
                return false;
            }
        }
        else
        {
            DEV_PRINT("delete element -> bad structure index");
            return false;
        }
    }
   
    bool checkCanPrintStructure(int structureIndex)
    {
        if (this->CheckIsStructureIndexOK(structureIndex))
        {
            if (this->structureList[structureIndex]->size() == 0)
            {
                cout << "empty\n";
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            DEV_PRINT("bad index -> structure print");
            return false;
        }
    }
    virtual OperationResult addElementToStructure(int structureIndex, int elementToInsert) = 0;
    virtual OperationResult deleteElementFromStructure(int structureIndex) = 0;
    virtual OperationResult printStructure(int structureIndex) = 0;
};

class StackStructure: public SimpleStructure
{
public:
    StackStructure(const int structureAmount, const int maxAmountItemsPerStructure)
        :SimpleStructure(structureAmount, maxAmountItemsPerStructure)
    {}
    OperationResult addElementToStructure(int structureIndex, int elementToInsert)
    {
        if (this->checkCanAddElementToStructure(structureIndex, elementToInsert))
        {
            this->structureList[structureIndex]->push_front(elementToInsert);
            return OperationResult(elementToInsert, true);
        }
        else {
            return OperationResult(elementToInsert, false);
        }
    }
    OperationResult deleteElementFromStructure(int structureIndex)
    {
        if (this->checkCanDeleteElementFromStructure(structureIndex))
        {
            int deletedElement = this->structureList[structureIndex]->front();
            this->structureList[structureIndex]->pop_front();
            return OperationResult(deletedElement, true);
        }
        else
        {
            return OperationResult(structureIndex, false);
        }
    }
    OperationResult printStructure(int structureIndex)
    {
        if (this->checkCanPrintStructure(structureIndex))
        {
            int size = this->structureList[structureIndex]->size();
            for (int i = 0; i < size; i++)
            {
                int tmp = this->structureList[structureIndex]->back();
                cout << tmp << " ";
                this->structureList[structureIndex]->pop_back();
                this->structureList[structureIndex]->push_front(tmp);
            }
            cout << "\n";
            return OperationResult(structureIndex, true);
        }
        else
        {
            cout << "bad index print queue\n";
            return OperationResult(structureIndex, false);
        }
    }
};

class QueueStructure : public SimpleStructure
{
public:
    QueueStructure(const int structureAmount, const int maxAmountItemsPerStructure)
        :SimpleStructure(structureAmount, maxAmountItemsPerStructure)
    {}
    OperationResult addElementToStructure(int structureIndex, int elementToInsert)
    {
        if (this->checkCanAddElementToStructure(structureIndex, elementToInsert))
        {
            this->structureList[structureIndex]->push_front(elementToInsert);
            return OperationResult(elementToInsert, true);
        }
        else {
            return OperationResult(elementToInsert, false);
        }
    }
    OperationResult deleteElementFromStructure(int structureIndex)
    {
        if (this->checkCanDeleteElementFromStructure(structureIndex))
        {
            int deletedElement = this->structureList[structureIndex]->back();
            this->structureList[structureIndex]->pop_back();
            return OperationResult(deletedElement, true);
        }
        else
        {
            return OperationResult(structureIndex, false);
        }
    }
    OperationResult printStructure(int structureIndex)
    {
        if (this->checkCanPrintStructure(structureIndex))
        {
            int size = this->structureList[structureIndex]->size();
            for (int i = 0; i < size; i++)
            {
                int tmp = this->structureList[structureIndex]->front();
                cout << tmp << " ";
                this->structureList[structureIndex]->pop_front();
                this->structureList[structureIndex]->push_back(tmp);
            }
            cout << "\n";
            return OperationResult(structureIndex, true);
        }
        else {
            return OperationResult(structureIndex, false);
        }
    }
};

class StructuresControler
{
private:
    QueueStructure q1;
    StackStructure s1;
public:
    StructuresControler(QueueStructure& q1, StackStructure& s1)
        :q1(q1), s1(s1)
    {}
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
    int returnNextArgument(list<string>& command)
    {
        string argument1 = command.front();
        command.pop_front();
        int value1 = stoi(argument1);
        return value1;
    }
    void frontedCore()
    {
        list<string> commandListToExecute;

        while (true)
        {
            string commandToExecute;
            getline(cin, commandToExecute);
            if (commandToExecute == "")
            {
                break;
            }
            commandListToExecute.push_back(commandToExecute);
        }
        int licznik = 1;
        for (auto simpleCommand : commandListToExecute)
        {
            licznik++;
            list<string> commandArguments = this->splitString(simpleCommand, " ");
            string operationType = commandArguments.front();
            commandArguments.pop_front();

            //stack if
            if (operationType == "new_s")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->s1.createStructure(arg1);
            }
            else if (operationType == "push")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->s1.addElementToStructure(arg1, arg2);
            }
            else if (operationType == "pop")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->s1.deleteElementFromStructure(arg1);
            }
            else if (operationType == "stack->stack")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                //this->moveElementFromStackAToStackB(arg1, arg2);
                OperationResult r1 = this->s1.deleteElementFromStructure(arg1);
                if (r1.getResult() == true)
                {
                    this->s1.addElementToStructure(arg2, r1.getItem());
                }
                else
                {
                    DEV_PRINT("error move");
                }
                
            }
            else if (operationType == "delete_s")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->s1.deleteStructure(arg1);
            }
            else if (operationType == "print_s")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->s1.printStructure(arg1);
            }

            //queue if
            else if (operationType == "new_q")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->q1.createStructure(arg1);
            }
            else if (operationType == "enqueue")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->q1.addElementToStructure(arg1, arg2);
            }
            else if (operationType == "dequeue")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->q1.deleteElementFromStructure(arg1);
            }
            else if (operationType == "delete_q")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->q1.deleteStructure(arg1);
            }
            else if (operationType == "print_q")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->q1.printStructure(arg1);
            }
            else if (operationType == "queue->queue")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                
                OperationResult r1 = this->q1.deleteElementFromStructure(arg1);
                if (r1.getResult() == true)
                {
                    this->q1.addElementToStructure(arg2, r1.getItem());
                }
                else
                {
                    DEV_PRINT("error move");
                }
            }

            //move between stack & queue
            else if (operationType == "stack->queue")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                
                OperationResult r1 = this->s1.deleteElementFromStructure(arg1);
                if (r1.getResult() == true)
                {
                    this->q1.addElementToStructure(arg2, r1.getItem());
                }
                else
                {
                    DEV_PRINT("error move");
                }
            }
            else if (operationType == "queue->stack")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                
                OperationResult r1 = this->q1.deleteElementFromStructure(arg1);
                if (r1.getResult() == true)
                {
                    this->s1.addElementToStructure(arg2, r1.getItem());
                }
                else
                {
                    DEV_PRINT("error move");
                }
            }

        }

    }

};

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
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

    bool queueCheckIsIndexOK(int queueIndex)
    {
        // check is stack index correct
        //a) check is index beetween 0 and stackAmount
        //b) check is stack exist 
        if (queueIndex < this->queueAmount && queueIndex >= 0 && this->isQueueExist[queueIndex] == true)
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
            this->isQueueExist[queueIndex] = true;
            this->queueList[queueIndex] = new list <int>;

            DEV_PRINT("ok -> queue created");
        }
        else
        {
            DEV_PRINT("cant create queue -> bad index");
        }
    }
    void addElementToStack(int stackIndex, int elementToInsert)
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
    void addElementToQueue(int queueIndex, int elementToInsert)
    {
        if (this->queueCheckIsIndexOK(queueIndex))
        {

            if (this->queueList[queueIndex]->size() < this->maxAmountItemsPerQueue)
            {
                this->queueList[queueIndex]->push_front(elementToInsert);
            }
            else
            {
                cout << "error: queue is full\n";
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
    void deleteElementFromQueue(int queueIndex)
    {
        if (this->queueCheckIsIndexOK(queueIndex))
        {
            if (this->queueList[queueIndex]->size() > 0)
            {
                this->queueList[queueIndex]->pop_back();
            }
            else
            {
                cout << "error: queue is empty\n";
            }
        }
        else
        {
            DEV_PRINT("delete element -> bad queue index");
        }
    }
    void moveElementFromStackAToStackB(int stackIndexA, int stackIndexB)
    {
        if (this->stackCheckIsIndexOK(stackIndexA) && this->stackCheckIsIndexOK(stackIndexB))
        {
            if (this->stackList[stackIndexA]->size() == 0)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element stackA to stackB -> stackA is empty");
            }
            else if (this->stackList[stackIndexB]->size() == this->maxAmountItemsPerStack)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element stackA to stackB -> stackB is full");
            }
            else
            {
                int tmp = this->stackList[stackIndexA]->front();
                this->deleteElementFromStack(stackIndexA);
                this->addElementToStack(stackIndexB, tmp);
            }

        }
        else
        {
            DEV_PRINT("move element stack A to stack B -> bad stack index");
        }
    }
    void moveElementFromQueueAToQueueB(int queueIndexA, int queueIndexB)
    {
        if (this->queueCheckIsIndexOK(queueIndexA) && this->queueCheckIsIndexOK(queueIndexB))
        {
            if (this->queueList[queueIndexA]->size() == 0)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element queueA to queueB -> queueA is empty");
            }
            else if (this->queueList[queueIndexB]->size() == this->maxAmountItemsPerQueue)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element queueA to queueB -> queueB is full");
            }
            else
            {
                int tmp = this->queueList[queueIndexA]->back();
                this->deleteElementFromQueue(queueIndexA);
                this->addElementToQueue(queueIndexB, tmp);
            }
        }
        else
        {
            DEV_PRINT("move element queue A to queue B -> bad  index");
        }
    }
    void moveElementFormStackToQueue(int stackIndex, int queueIndex)
    {
        if (this->stackCheckIsIndexOK(stackIndex) && this->queueCheckIsIndexOK(queueIndex))
        {
            if (this->stackList[stackIndex]->size() == 0)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element stack to queue -> stack is empty");
            }
            else if (this->queueList[queueIndex]->size() == this->maxAmountItemsPerQueue)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element stack to queue -> queue is full");
            }
            else
            {
                int tmp = this->stackList[stackIndex]->front();
                this->deleteElementFromStack(stackIndex);
                this->addElementToQueue(queueIndex, tmp);
            }
        }
        else
        {
            DEV_PRINT("move element stack to queue -> bad  index");
        }
    }
    void moveElementFromQueueToStack(int queueIndex, int stackIndex)
    {
        if (this->stackCheckIsIndexOK(stackIndex) && this->queueCheckIsIndexOK(queueIndex))
        {
            if (this->queueList[queueIndex]->size() == 0)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element queue to stack -> queue is empty");
            }
            else if (this->stackList[stackIndex]->size() == this->maxAmountItemsPerStack)
            {
                cout << "error: wrong command\n";
                DEV_PRINT("move element queue to stack -> stack is full");
            }
            else
            {
                int tmp = this->queueList[queueIndex]->back();
                this->deleteElementFromQueue(queueIndex);
                this->addElementToStack(stackIndex, tmp);
            }
        }
        else
        {
            DEV_PRINT("move element queue to stack -> bad  index");
        }
    }
    void deleteStack(int stackIndex)
    {
        if (this->stackCheckIsIndexOK(stackIndex))
        {
            delete this->stackList[stackIndex];
            this->isStackExist[stackIndex] = false;
        }
        else
        {
            DEV_PRINT("delete stack -> bad stack index");
        }
    }
    void deleteQueue(int queueIndex)
    {
        if (this->queueCheckIsIndexOK(queueIndex))
        {
            delete this->queueList[queueIndex];
            this->isQueueExist[queueIndex] = false;
        }
        else
        {
            DEV_PRINT("delete queue -> bad queue index");
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
        else
        {
            DEV_PRINT("bad index -> stack print");
        }
    }
    void printQueue(int queueIndex)
    {
        if (this->queueCheckIsIndexOK(queueIndex))
        {
            if (this->queueList[queueIndex]->size() == 0)
            {
                cout << "empty\n";
            }
            else
            {
                int size = this->queueList[queueIndex]->size();
                for (int i = 0; i < size; i++)
                {
                    int tmp = this->queueList[queueIndex]->front();
                    cout << tmp << " ";
                    this->queueList[queueIndex]->pop_front();
                    this->queueList[queueIndex]->push_back(tmp);
                }
                cout << "\n";
            }
        }
        else
        {
            DEV_PRINT("bad index -> queue print");
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
        //commandListToExecute.push_back("new_s 0");
        //commandListToExecute.push_back("push 0 96");
        //commandListToExecute.push_back("new_s 5");
        //commandListToExecute.push_back("print_s 5");
        //commandListToExecute.push_back("push 5 28");
        //commandListToExecute.push_back("push 5 99");
        //commandListToExecute.push_back("push 5 33");
        //commandListToExecute.push_back("push 5 88");
        //commandListToExecute.push_back("pop 0");
        //commandListToExecute.push_back("print_s 5");
        //commandListToExecute.push_back("pop 0");
        //commandListToExecute.push_back("push 0 65");
        //commandListToExecute.push_back("push 5 99");
        //commandListToExecute.push_back("push 5 13");
        //commandListToExecute.push_back("push 5 99");
        //commandListToExecute.push_back("push 5 1");
        //commandListToExecute.push_back("push 5 99");
        //commandListToExecute.push_back("push 5 0");
        //commandListToExecute.push_back("push 5 9");
        //commandListToExecute.push_back("push 5 87");
        //commandListToExecute.push_back("stack->stack 5 0");
        //commandListToExecute.push_back("print_s 0");


         //--------------
        //test-3
        //--------------
        /*commandListToExecute.push_back("new_s 0");
        commandListToExecute.push_back("push 0 96");
        commandListToExecute.push_back("new_s 5");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("push 5 28");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("new_q 0");
        commandListToExecute.push_back("push 5 33");
        commandListToExecute.push_back("push 5 88");
        commandListToExecute.push_back("pop 0");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("pop 0");
        commandListToExecute.push_back("push 0 65");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("dequeue 0");
        commandListToExecute.push_back("enqueue 0 4");
        commandListToExecute.push_back("new_q 9");
        commandListToExecute.push_back("push 5 13");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("enqueue 0 43");
        commandListToExecute.push_back("enqueue 0 21");
        commandListToExecute.push_back("enqueue 0 17");
        commandListToExecute.push_back("enqueue 0 4");
        commandListToExecute.push_back("enqueue 9 0");
        commandListToExecute.push_back("enqueue 0 4");
        commandListToExecute.push_back("enqueue 0 43");
        commandListToExecute.push_back("enqueue 0 40");
        commandListToExecute.push_back("push 5 1");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("enqueue 0 33");
        commandListToExecute.push_back("enqueue 0 99");
        commandListToExecute.push_back("enqueue 0 8");
        commandListToExecute.push_back("push 5 0");
        commandListToExecute.push_back("push 5 9");
        commandListToExecute.push_back("delete_q 0");
        commandListToExecute.push_back("print_q 9");
        commandListToExecute.push_back("push 5 87");
        commandListToExecute.push_back("new_q 0");
        commandListToExecute.push_back("enqueue 0 19");
        commandListToExecute.push_back("print_q 0");
        commandListToExecute.push_back("stack->stack 5 0");
        commandListToExecute.push_back("print_s 0");*/


        //--------------
       //test-3 only queue
       //--------------

        //commandListToExecute.push_back("new_q 0");
        //commandListToExecute.push_back("dequeue 0");
        //commandListToExecute.push_back("enqueue 0 4");
        //commandListToExecute.push_back("new_q 9");//
        //commandListToExecute.push_back("enqueue 0 43");
        //commandListToExecute.push_back("enqueue 0 21");
        //commandListToExecute.push_back("enqueue 0 17");
        //commandListToExecute.push_back("enqueue 0 4");
        //commandListToExecute.push_back("enqueue 9 0");
        //commandListToExecute.push_back("enqueue 0 4");
        //commandListToExecute.push_back("enqueue 0 43");
        //commandListToExecute.push_back("enqueue 0 40");
        //commandListToExecute.push_back("enqueue 0 33");
        //commandListToExecute.push_back("enqueue 0 99");
        //commandListToExecute.push_back("enqueue 0 8");
        //commandListToExecute.push_back("delete_q 0");
        //commandListToExecute.push_back("print_q 9");
        //commandListToExecute.push_back("new_q 0");
        //commandListToExecute.push_back("enqueue 0 19");
        //commandListToExecute.push_back("print_q 0");

        //--------------
       //test-4
       //--------------
        /*commandListToExecute.push_back("new_s 0");
        commandListToExecute.push_back("push 0 96");
        commandListToExecute.push_back("new_s 5");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("push 5 28");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("new_q 0");
        commandListToExecute.push_back("push 5 33");
        commandListToExecute.push_back("push 5 88");
        commandListToExecute.push_back("pop 0");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("pop 0");
        commandListToExecute.push_back("push 0 65");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("dequeue 0");
        commandListToExecute.push_back("enqueue 0 4");
        commandListToExecute.push_back("new_q 9");
        commandListToExecute.push_back("push 5 13");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("enqueue 0 43");
        commandListToExecute.push_back("enqueue 0 21");
        commandListToExecute.push_back("enqueue 0 17");
        commandListToExecute.push_back("stack->queue 0 0");
        commandListToExecute.push_back("enqueue 0 4");
        commandListToExecute.push_back("stack->queue 0 0");
        commandListToExecute.push_back("enqueue 9 0");
        commandListToExecute.push_back("enqueue 0 4");
        commandListToExecute.push_back("enqueue 0 43");
        commandListToExecute.push_back("queue->queue 0 0");
        commandListToExecute.push_back("stack->stack 5 5");
        commandListToExecute.push_back("enqueue 0 40");
        commandListToExecute.push_back("push 5 1");
        commandListToExecute.push_back("push 5 99");
        commandListToExecute.push_back("enqueue 0 33");
        commandListToExecute.push_back("enqueue 0 99");
        commandListToExecute.push_back("enqueue 0 8");
        commandListToExecute.push_back("push 5 0");
        commandListToExecute.push_back("push 5 9");
        commandListToExecute.push_back("delete_q 0");
        commandListToExecute.push_back("print_q 9");
        commandListToExecute.push_back("push 5 87");
        commandListToExecute.push_back("new_q 0");
        commandListToExecute.push_back("stack->queue 5 0");
        commandListToExecute.push_back("enqueue 0 3");
        commandListToExecute.push_back("queue->queue 0 0");
        commandListToExecute.push_back("enqueue 0 19");
        commandListToExecute.push_back("stack->stack 5 0");
        commandListToExecute.push_back("print_s 0");
        commandListToExecute.push_back("print_s 5");
        commandListToExecute.push_back("print_q 0");
        commandListToExecute.push_back("print_q 9");*/



        while (true)
        {
            string commandToExecute;
            getline(cin, commandToExecute);
            if (commandToExecute == "")
            {
                break;
            }
            commandListToExecute.push_back(commandToExecute);
        }
        int licznik = 1;
        for (auto simpleCommand : commandListToExecute)
        {
            //DEV_PRINT(simpleCommand);
            //cout <<"polecenie: "<< licznik << " "  << simpleCommand << "\n";
            licznik++;
            list<string> commandArguments = this->splitString(simpleCommand," ");
            string operationType = commandArguments.front();
            commandArguments.pop_front();

            //stack if
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

            //queue if
             else if (operationType == "new_q")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->createQueue(arg1);
            }
            else if (operationType == "enqueue")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->addElementToQueue(arg1, arg2);
            }
            else if (operationType == "dequeue")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->deleteElementFromQueue(arg1);
            }
            else if (operationType == "delete_q")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->deleteQueue(arg1);
            }
            else if (operationType == "print_q")
            {
                int arg1 = returnNextArgument(commandArguments);
                this->printQueue(arg1);
            }
            else if (operationType == "queue->queue")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->moveElementFromQueueAToQueueB(arg1, arg2);
            }
            
            //move between stack & queue
            else if (operationType == "stack->queue")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->moveElementFormStackToQueue(arg1, arg2);
            }
            else if (operationType == "queue->stack")
            {
                int arg1 = returnNextArgument(commandArguments);
                int arg2 = returnNextArgument(commandArguments);
                this->moveElementFromQueueToStack(arg1, arg2);
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
{
 
    /*QueueAndStackSystem q1(10,10,10,10);
    q1.frontendCore();*/

   /* q1.createQueue(0);
    q1.addElementToQueue(0, 10);
    q1.deleteElementFromQueue(0);
    q1.deleteQueue(0);
    q1.deleteElementFromQueue(0);
    q1.printQueue(3);*/

    //q1.createStack(0);
    //q1.addElementToStack(0,100);
    //q1.addElementToStack(0,200);
    //q1.addElementToStack(0,300);
    //q1.addElementToStack(0,400);


    //q1.printStack(0);

    //TODO:
    /*
    1.Test queue backend. Particulary print operation
    */

    /*StackStructure s1(10, 10);
    QueueStructure q1(10, 10);

    q1.createStructure(1);
    q1.addElementToStructure(1, 111);
    q1.addElementToStructure(1, 222);
    q1.addElementToStructure(1, 333);
    q1.printStructure(1);
    q1.deleteElementFromStructure(1);
    q1.printStructure(1);
    q1.addElementToStructure(2, 333);
    q1.printStructure(1);
    cout << "-----\n";

    s1.createStructure(1);
    s1.addElementToStructure(1, 111);
    s1.addElementToStructure(1, 222);
    s1.addElementToStructure(1, 333);
    s1.printStructure(1);
    s1.deleteElementFromStructure(1);
    s1.printStructure(1);
    s1.addElementToStructure(2, 333);
    s1.printStructure(1);*/


    
}
