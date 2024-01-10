#include "allocator.h"

arenaAllocator::arenaAllocator(int size)
{

    this->safety = false;
    this->arenaPointer = new link[size];
    this->size = size;
    this->head = this->arenaPointer;

    link *tmp = this->head;

    // Link the links from arenaPointer
    for (int i = 0; i < this->size; i++){

        tmp->next = &this->arenaPointer[i];
        tmp = tmp->next;

    }

}

arenaAllocator::~arenaAllocator()
{
    // If exception handling
    if(safety){

        // Goto the start
        head = this->arenaPointer;

        while(head){

            std::cout << head << '\n';
            head = head->next;

        }

        // Space out statement in console
        std::cout << "\n";

    }

    // Delete arena
    delete[] arenaPointer;

}

void arenaAllocator::setSafety(bool value)
{

    this->safety = value;

}

bool arenaAllocator::inBounds(item* thePointer)
{
    // Current link to be checked
    link* theLink = (link*) thePointer;

    bool afterEnd = std::greater<link*>{}(theLink, (arenaPointer+size));
    bool beforeStart = std::less<link*>{}(theLink, arenaPointer);

    // If either is afterEnd or beforeStart then return false (not in bounds)
    return ! ( afterEnd || beforeStart );

}

item* arenaAllocator::alloc()
{

    // If empty (if nullptr is true)
    if(this->head == nullptr){

        if(safety){
            throw outOfMemory();
        }   

        return nullptr; // Return empty link

    }
    
    // Set temporary variable which holds next in list
    item* tmp = (item*)this->head;

    // Set first to next after previous first
    this->head = this->head->next;

    // Return address of removed first
    return tmp;


}

void arenaAllocator::free(item* currentItem)
{

    // If empty (if nullptr is true)
    if(safety){

        link *tmp = this->head;
        while (tmp)
        {

            // If trying to free already free addresses
            if((link*)currentItem == tmp){
                
                throw doubleFree();

            }
            tmp = tmp->next;

        }

        // If not in bound
        if (!this->inBounds(currentItem))
        {

            throw outOfBounds();

        }
    }

    // New first next is previous first
    ((link*)currentItem)->next = this->head;

    // Set first to currentLink
    this->head = (link*)currentItem;


}


