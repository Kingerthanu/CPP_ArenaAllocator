# CPP_ArenaAllocator

  Used to understand usage of memory and its allocation in a general sense to how memory is managed
in RAM.

<img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/d7f7f851-9c4c-4b1a-85b1-47fa36346a9f" alt="Cornstarch <3" width="105" height="169">

Works with an arena-type allocator and unit testing to display understanding of how the code
looks under the hood in which makes it work. Mainly working with exceptions like outOfBounds, doubleFree,
as well as outOfMemory to show how issues can arise, and be caught and managed in a way which is concurrent with a ADT model.



----------------------------------------------

<img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/b1193feb-0b3d-44c1-bcef-380c1d68e528" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/b1193feb-0b3d-44c1-bcef-380c1d68e528" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/b1193feb-0b3d-44c1-bcef-380c1d68e528" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/b1193feb-0b3d-44c1-bcef-380c1d68e528" alt="Cornstarch <3" width="55" height="49">



**The Breakdown:**

This Program Uses The Terminal To Display Behaivor Of A Defined Dynamically Allocated Memory Arena Allocator.

This Program Works With A Defined Allocator Class In Which Manages Multiple Spots Of Memory In Its Own Closes Space Of Active Pointed To Memory. A User Can Ask For Memory From The Allocator As Well As Ask It To Free Some Memory Stored. We Also Defined Some Exception Types For Our Allocator To Use As Unique Identifiers To Specific Errors Expressed By Our ADT.

Each Piece Of Memory Allocated By The Arena Is Held In Item Objects In Which Are A Simple Struct Holding A Integer Value.

Currently We Have A Extensive Testing Driver Made In Which Asks The User For A **X** Sized Array Of Data For The Arena To Allocate Up To And Makes Every Increasing In Size Arenas And Unit Testing Each For Proper Functionality.

We Use Our Own Defined Testing To Ensure Proper Behaivor And We Also Include Verbosity To Allow The User To See More About Specific Entries Being Allocated For Debugging Purposes.


<img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/c70495d9-dade-4fa0-8c9e-8285f1193c97" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/c70495d9-dade-4fa0-8c9e-8285f1193c97" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/c70495d9-dade-4fa0-8c9e-8285f1193c97" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/c70495d9-dade-4fa0-8c9e-8285f1193c97" alt="Cornstarch <3" width="55" height="49">

----------------------------------------------

<img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/8a95b7da-34be-4338-8ed7-8c04c1535217" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/8a95b7da-34be-4338-8ed7-8c04c1535217" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/8a95b7da-34be-4338-8ed7-8c04c1535217" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/8a95b7da-34be-4338-8ed7-8c04c1535217" alt="Cornstarch <3" width="55" height="49">


**Features:**

![2024-01-1018-15-18-ezgif com-crop](https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/149c0b5e-54ec-4ba0-8674-0d5d7de826c3)




<img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/975315dc-267d-481c-a33e-259c16f3f34d" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/975315dc-267d-481c-a33e-259c16f3f34d" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/975315dc-267d-481c-a33e-259c16f3f34d" alt="Cornstarch <3" width="55" height="49"><img src="https://github.com/Kingerthanu/CPP_ArenaAllocator/assets/76754592/975315dc-267d-481c-a33e-259c16f3f34d" alt="Cornstarch <3" width="55" height="49">
