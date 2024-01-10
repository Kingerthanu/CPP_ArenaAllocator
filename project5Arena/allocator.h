// File        : allocator.h
// Author      : Benjamin R Spitzauer
// Description : A simple definition for the type `allocator`

#include "item.h"
#include <functional>
#include <iostream> 

#ifndef ALLOC_INCLUDE
#define ALLOC_INCLUDE

class outOfMemory
{
    /*
        Has implicit constructor; doesn't need any members as it works as a signifier
        to a type of issue so when thrown as a exception nothing is needed other than the
        type name in order to show the issue being presented.
    */
};

class outOfBounds
{
    /*
        Has implicit constructor; doesn't need any members as it works as a signifier
        to a type of issue so when thrown as a exception nothing is needed other than the
        type name in order to show the issue being presented.
    */
};

class doubleFree
{
    /*
        Has implicit constructor; doesn't need any members as it works as a signifier
        to a type of issue so when thrown as a exception nothing is needed other than the
        type name in order to show the issue being presented.
    */
};

struct link
{

    // A container type in which contains only a singular integer
    item value;

    // Pointer to address of next link in linked list
    link* next = nullptr;

};

class arenaAllocator
{
    private:

        // Works as switch to toggle the display of exceptions when unit testing
        bool safety;

        // The integer size of the arenaPointer link* array
        int size;

        /* 
            A link* which will point to an array of links which will store the current accessible addresses
            for the allocator to work with (first nullptr as we don't know the size of the allocater the 
            user wants to use).
        */
        link* arenaPointer = nullptr;

        // Works as a iterator to walk through the arenaPointers links without losing the start of the arena
        link* head;

    public:

        /*
            Precondition: Must intake the intended size of the allocator
            Postcondition: Will construct the default values of the members of the arenaAllocator type.
            Sets safety to false; this->size to parameter size; arenaPointer creates link[size] to contain;
            finally connects all links of the arenaPointer for head to iterate through.
        */
        arenaAllocator(int size);

        /*
            Precondition: None; will be called when lifetime is finished.
            Postcondition: Will display all currently allocated addresses if safety is on before deallocating
            arenaPointer.
        */
        ~arenaAllocator();

        /*
            Precondition: Must intake a boolean of true or false
            Postcondition: Will be set to the member this->safety
        */
        void setSafety(bool value);

        /*
            Precondition: Will take in a item* thePointer which will be searched for in arenaAllocator
            Postcondition: Will return true if thePointer (its address) is inside the bounds of arenaAllocator;
            if not, it will return false signifying its out of bounds.
        */
        bool inBounds(item* thePointer);

        /*
            Precondition: Must have arenaAllocator initialized and linked.
            Postcondition: Will get the next up free address in arenaPointer in which the user can use and will
            return the link in which is free but will caste it to item* before returning for the user. 
            If there is no more free spots though, then a nullptr is returned; if safety is on though,
            outOfMemory exception is thrown.
        */
        item* alloc();

        /*
            Precondition: Must intake the item* which the function is trying to find in the arenaAllocator
            Postcondition: Will "readd" the currentItem back into arenaAllocator; will return double free,
            or out of bounds exceptions if safety is set to true, and these issues arise.
        */
        void free(item* currentItem);

};

#endif