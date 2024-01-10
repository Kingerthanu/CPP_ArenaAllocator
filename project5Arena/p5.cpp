// Benjamin Rudolph Spitzauer
// Project 5 - "Typed Arena Allocator"
// 12/02/2022
/* Used to understand usage of memory and its allocation in a general sense to how memory is managed
in RAM. Works with an arena-type allocator and unit testing to display understanding of how the code
looks under the hood in which makes it work. Mainly working with exceptions like outOfBounds, doubleFree,
as well as outOfMemory to show how issues can arise, and be caught and managed in a way which is concurrent
with the ADT understanding of this class.
*/
#include "item.h"
#include "allocator.h"
#include <iostream>
#include <random>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ProtoTypes~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
    Precondition: Must intake the intended arenaAllocator in order to unit test
    Postcondition: Will unit test for data being "lost" when not freed before deleting a
    arenaAllocator instance. It will check out of bounds, out of memory, as well as double
    free exceptions.
*/
void testAllocator(arenaAllocator*& currentArena);
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Tracks the alloction state of an arenaAllocator independant
// of its internal representation.
// Invariants: 
//  - size must be non-negative, and equal to the size of the arena
//  - allocRecord must point to valid storage containing an array
//    of at least `size` item pointers
class allocTestSuite
{

    private:
    // The size of the arena
    int             size;
    // The allocator, itself
    arenaAllocator  allocator;
    // A pseudo-random number generator, used to add stochasticity
    std::mt19937    rng;
    // Points to an array that tracks outstanding allocations
    item**          allocRecord;

    public:
    
    // Allocates an array for allocRecord, matching allocatorSize,
    // initializes size to allocatorSize, and constructs the allocator
    // member to have an arena size of allocatorSize
    // pre  : allocatorSize must be non-negative
    // post : None, aside from description
    allocTestSuite(int allocatorSize, int seed);

    // Frees the array identified by allocRecord
    // pre  : None
    // post : None
    ~allocTestSuite();

    bool randomValidOperation(bool verbose);

};


void testAllocator(arenaAllocator*& currentArena)
{

    // Set safety to true to display loss data
    currentArena->setSafety(true);

    // First test if currentArena displays addresses when deleted with still allocated data
    std::cout << "Start Test on Forgotten Data?\n";
    std::cin.ignore();

    /* 
    Don't need to have a catch block as destructor at worst case will have values of null which will
    fall through without syntax issues
    */
    delete currentArena;

    std::cout << "Finished Forgotten Data Test!\n\n\n";

    // Reallocate variable
    currentArena = new arenaAllocator(10);

    // Set to enable safety nets
    currentArena->setSafety(true);

    std::cout << "Start Test Double Free?\n";
    std::cin.ignore();

    // Attempt to double frees
    for(int i = 0; i < 10; i++){

        item* currentAlloc = currentArena->alloc();

        try{

            // Try removing same address twice to look if a double free is caught 
            currentArena->free(currentAlloc);
            currentArena->free(currentAlloc);

        }
        catch(doubleFree){

            // Should print 10 times
            std::cout << "Tried to free a spot in data which is already freed! (Double Free Exception)\n\n";

        }
        
    }

    std::cout << "Finished Double Free Test!\n\n\n";
    std::cout << "Start Test Out of Memory?\n";
    std::cin.ignore();

    // Attempt to Out of Memory (allocate beyond accepted fixed size) should print 10 catch statements
    for(int i = 0; i < 20; i++){
        
        try{

            item* currentAlloc = currentArena->alloc();

        }
        catch(outOfMemory){

            // Should print 10 times
            std::cout << "\nRan out of memory to allocate upon! (Out of Memory Exception)\n";

        }
        
    }

    std::cout << "\nFinished Out of Memory Test!\n\n\n";
    std::cout << "Start Test Out of Bounds?\n";
    std::cin.ignore();

    // Free current set of data (hide from user; turn off safety and turn back on)
    currentArena->setSafety(false);
    delete currentArena;

    // Create new instance
    currentArena = new arenaAllocator(10);

    currentArena->setSafety(true);

    // Attempt out of bounds as well as one in bound call
    item notInside{-529083475};
    item* isInside = currentArena->alloc();

    // Should always call catch block
    try{

        currentArena->free(&notInside);

    }
    catch(outOfBounds){

        std::cout << &notInside << " is not inside the allocators range of data :( (Out of Bounds Exception)\n\n";

    }

    try{   

        // Should never call catch block as its inside range and inheritly should be non-freed memory at this time
        currentArena->free(isInside);
        std::cout << isInside << " is inside the allocators range of data :) (Out of Bounds Exception [should always be true])\n\n";


    }
    catch(outOfBounds){

        std::cout << &isInside << " is not inside the allocators range of data :( (Out of Bounds Exception [Shouldn't ever be called])\n\n";

    }
    catch(doubleFree){

        std::cout << &isInside << " is already removed; trying to free already freed data :( (Double Free Exception [Shouldn't ever be called])\n\n";
    }

    // Display current addresses at end of function
    std::cout << "Arena allocators addresses: \n";
    delete currentArena;

    // Make new arena so when returned the referenced variable is not pointing to null
    currentArena = new arenaAllocator(10);

    std::cout << "Finished Out of Bounds Test!\n\n\n";

}

// Performs size*10 valid allocation/deallocation operations
// for every power-of-two size up to 2^20
int main()
{

    // set `verbose` to true for a more comprehensive walkthrough
    // of what the test suite is doing.
    bool verbose = false;
    bool failure = false;

    int limit = 1 << 20; // 2 to the power of 20

    std::cout << "Start test random allocation in range of 1-2^20?\n";
    std::cin.ignore();

    for(int size=1; size<=limit; size*=2){

        // Create fresh test suite
        allocTestSuite suite (size,1234);

        // Subject the allocator to many operations, breaking
        // early if it shows incorrect behavior
        for(int i=0; i<size*10; i++){
            //std::cout << "\n" << "CHECKED\n";
            if( ! suite.randomValidOperation(verbose)){
                failure = true;
                break;
            }
        }

        // Do not test any larger sizes if a failure was detected
        if( failure ){
            break;
        }

        std::cout << "Passed for size " << size << "\n\n";

    }

    // Announce that the random allocation testing was successfully passed
    std::cout << "Finished Random 2^20 Allocations!\n\n\n";

    // Create allocator to test upon
    arenaAllocator* currentArena = new arenaAllocator(10);

    // Run unit tests
    testAllocator(currentArena);

    // Deallocate arena
    delete currentArena;

    // Conclude
    return 0;
}


allocTestSuite::allocTestSuite(int allocatorSize, int seed)
    // This is just an alternate way of initializing
    // the members of a class. Please don't use it in the
    // Final Exam unless you know what you are doing.
    : size(allocatorSize)
    , allocator(size)
    , rng(seed)
    , allocRecord(new item*[allocatorSize])
{
    for(int i=0; i<size; i++){
        allocRecord[i] = nullptr;
    }
}


allocTestSuite::~allocTestSuite()
{
    delete[] allocRecord;
}


bool allocTestSuite::randomValidOperation(bool verbose)
{

    bool correct = true;

    // Selects a random index of the allocation record to check
    int randomIndex = rng() % size;

    // Get the element of that index by reference, to make working
    // with it more convenient
    item*& entry = allocRecord[randomIndex];

    // If the entry is null, allocate a pointer for it, and set
    // the identified storage to equal the index of the pointer
    if( entry == nullptr ){

        if( verbose ){
            std::cout << "Allocating item" << std::endl;
        }

        entry = allocator.alloc();
        entry->value = randomIndex;

        if( verbose ){
            std::cout << "Allocated item at " << entry << std::endl;
        }

    } else {

        // If the entry is not null, check that the identified storage
        // still has a value equal to the pointer's index. If not, some
        // form of corruption has occured (potential double-alloc?).
        // Either way, the pointer is de-allocated.

        if( verbose ){
            std::cout << "Deallocating item at " << entry << std::endl;
        }

        bool corruption = (entry->value != randomIndex);
        correct = correct &&  ! corruption;

        if( corruption ){
            std::cout << "Memory corruption detected at address " 
                      << entry << std::endl;
        }

        allocator.free(entry);
        entry = nullptr;

        if( verbose ){
            std::cout << "Deallocated item" << std::endl;
        }

    }

    return correct;

}



