// hw11.cpp
// to illustrate function pointers and virtual functions

/*************************************************************************
 * AUTHOR     : Justin Gea
 * HW11       : function pointers and virtual functions
 * CLASS      : CS 1C
 * SECTION    : 7/19/2022
 *************************************************************************/

#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// function & class definitions go into hw11.cpp:

// hw11.cpp

namespace hw11
{

    //--Q#1-------------------------------------------------------------------------

    // (footnote 1)

    string foo()
    {
        return "foo";
    }

    //------------------------------------------------------------------------------

    int hoo(int x)
    {
        return x;
    }

    //------------------------------------------------------------------------------

    int boo(int x)
    {
        return 2 * x;
    }

    //------------------------------------------------------------------------------

    double goo(int x, double y)
    {
        return x * y;
    }

    // (footnote 1 - source) adapted from learncpp.com - Alex - 7.8 function pointers

    //--Q#2-------------------------------------------------------------------------

    // (footnote 1)

    // Note our user-defined comparison is the third parameter
    void selectionSort(int *array, int size, bool (*comparison)(int, int))
    {
        // Step through each element of the array
        for (int startIndex = 0; startIndex < size; ++startIndex)
        {
            // bestIndex is the index of the smallest/largest element we've encountered so far.
            int bestIndex = startIndex;

            // Look for smallest/largest element remaining in the array (starting at startIndex+1)
            for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
            {
                // If the current element is smaller/larger than our previously found smallest
                if (comparison(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
                    // This is the new smallest/largest number for this iteration
                    bestIndex = currentIndex;
            }

            // Swap our start element with our smallest/largest element
            std::swap(array[startIndex], array[bestIndex]);
        }
    }

    //------------------------------------------------------------------------------

    // Here is a comparison function that sorts in ascending order
    // (Note: it's exactly the same as the previous ascending() function)
    bool ascending(int x, int y)
    {
        // ...
        // temp, replace when defining function
        return x > y; // included so that incomplete lab code will compile
    }

    //------------------------------------------------------------------------------

    // Here is a comparison function that sorts in descending order
    bool descending(int x, int y)
    {
        // ...
        // temp, replace when defining function
        return x < y; // included so that incomplete lab code will compile
    }

    //------------------------------------------------------------------------------

    // custom comparison function, explain how your function sorts array components
    bool custom_sort(int x, int y)
    {
        // ...
        // temp, replace when defining function
        x = (x - 8) * (x - 10) * (x - 4) * x * 0.01;
        y = (y - 8) * (y - 10) * (y - 4) * y * 0.01;
        return x >= y; // included so that incomplete lab code will compile
    }

    //------------------------------------------------------------------------------

    // This function prints out the values in the array
    void printArray(int *array, int size)
    {
        for (int index = 0; index < size; ++index)
            cout << array[index] << " ";
        cout << '\n';
    }

    // (footnote 1 - source) learncpp.com - Alex - 7.8 function pointers

    //--Q#3,4-----------------------------------------------------------------------

    // (footnote 2)

    class Base
    {
    public:
        virtual void function1(){};
        virtual void function2(){};
    };

    //------------------------------------------------------------------------------

    class D1 : public Base
    {
    public:
        virtual void function2(){};
    };

    //------------------------------------------------------------------------------

    class D2 : public Base
    {
    public:
        virtual void function1(){};
        virtual void function3(){};
    };

    //------------------------------------------------------------------------------

    class D3 : public D2
    {
    public:
        virtual void function2(){};
    };

    // (footnote 2 - source) adapted from learncpp.com - Alex - 12.5 the virtual table

    //--Q#5-------------------------------------------------------------------------

    class BaseSlice
    {
        int base_id;
    };

    //------------------------------------------------------------------------------

    class DerivedSlice : public BaseSlice
    {
        int derived_id;
    };

    //------------------------------------------------------------------------------

} // hw11

//------------------------------------------------------------------------------

using namespace hw11;

int main()
{
    // console header
    cout << endl;
    cout << "************************************** " << endl;
    cout << "*           Running HW11             * " << endl;
    cout << "*      Programmed by First Last      * " << endl;
    cout << "*      CS1C Date & Time              * " << endl;
    cout << "************************************** " << endl;
    cout << endl;

    // Q#1 - function pointer examples

    // function pointer assignments
    // ... // [1.1] declare and init function pointer fcnPtr1 to point to function foo
    string (*fcnPtr1)() = foo;
    // ... // [1.2] declare and init function pointer fcnPtr2 to point to function hoo
    int (*fcnPtr2)(int) = hoo;
    // ... // [1.3] declare and init function pointer fcnPtr3 to point to function goo
    double (*fcnPtr3)(int, double) = goo;
    // ... // [1.4] assign fcnPtr1 to point to boo
    // error: different return types
    // ... // [1.5] assign fcnPtr2 to point to boo, okay - function pointer signature matches function boo
    fcnPtr2 = boo;

    // calling a function using a function pointer via explicit dereference
    // ... // [1.6] call function goo(2,5.0) through fcnPtr3 via explicit dereference
    (*fcnPtr3)(2, 5.0);

    // calling a function using a function pointer via implicit dereference
    // ... // [1.7] call function goo(2,5.0) through fcnPtr3 implicit dereference
    fcnPtr3(2, 5.0);

    // Q#2 - function pointers - calling user defined comparison functions in algorithms

    int array[9] = {3, 7, 9, 5, 6, 1, 8, 2, 4};

    // TEMP - COMPLETE FUNCTION CALL AND UNCOMMENT LINE BELOW
    // selectionSort( /* ... */ ); // [2.1] sort array in descending order
    selectionSort(array, 9, descending);
    printArray(array, 9);

    // TEMP - COMPLETE FUNCTION CALL AND UNCOMMENT LINE BELOW
    // selectionSort( /* ... */ ); // [2.2] sort array in ascending order
    selectionSort(array, 9, ascending);
    printArray(array, 9);

    // TEMP - COMPLETE FUNCTION CALL AND UNCOMMENT LINE BELOW
    // selectionSort( /* ... */ ); // [2.3] sort array via custom_sort algorithm
    selectionSort(array, 9, custom_sort);
    printArray(array, 9);

    // Q#3,4 - virtual function tables & calls

    D2 d2;
    Base *dPtr = &d2;
    dPtr->function1(); // [Q#4] what happens here ... explain in WRITTEN ANSWERS below?

    // Q#5 - the slicing problem

    DerivedSlice dSlice;          // instantiate derived class object
    BaseSlice baseSlice = dSlice; // instantiate base class object and assign to derived class
                                  // [Q#5] what is the slicing problem ... explain in WRITTEN ANSWERS below?

    return 0;
}

//------------------------------------------------------------------------------

// WRITTEN ANSWERS

// Q#3 (footnote 1)

/******* Base Class Virtual Function Table ********/
/* virtual function1() -> calls Base::function1() */
/* virtual function2() -> calls Base::function2() */
/**************************************************/

/******* D1 Class Virtual Function Table **********/
/* virtual function1() -> Base::function1() */
/* virtual function2() -> calls D1::function2() */
/**************************************************/

/******* D2 Class Virtual Function Table **********/
/* virtual function1() -> calls D2::function1() */
/* virtual function2() -> calls Base::function2() */
/* virtual function3() -> calls D2::function3() */
/**************************************************/

/******* D3 Class Virtual Function Table **********/
/* virtual function1() -> calls D2::function1() */
/* virtual function2() -> calls D3::function2() */
/* virtual function3() -> calls D2::function3() */
/**************************************************/

// (footnote 1 - source) adapted from learncpp.com - Alex - 12.5 the virtual table

// Q#4

// dPtr->function1(); // [Q#4] what happens here ... explain in WRITTEN ANSWERS below?
// the call to function1() is made through the virtual table, which points to D2::function1()

// Q#5

// BaseSlice baseSlice = dSlice; // instantiate base class object and assign to derived class
// [Q#5] what is the slicing problem ... explain in WRITTEN ANSWERS below?
// the slicing problem is that the compiler cannot determine which class the object belongs to,
// so it cannot determine which virtual function table to use.
