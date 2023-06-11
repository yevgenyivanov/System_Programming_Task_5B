#pragma once
// #include <set>
#include <vector>
#include <bits/stdc++.h> //std::sort
class MagicalContainer
{
private:
public:
    /* data */
    std::vector<int> _elements;
    // std::vector<int *> _ascendingElems;
    // std::vector<int *> _sidecrossElems;
    std::vector<int *> _primeElems;

    // ctors & dtor
    MagicalContainer(/* args */){};
    MagicalContainer(MagicalContainer &);                       // Copy constructor (non-default)
    MagicalContainer &operator=(const MagicalContainer &);      // Copy assignment operator (non-default)
    MagicalContainer(MagicalContainer &&) = default;            // Default move constructor
    MagicalContainer &operator=(MagicalContainer &&) = default; // Default move assignment operator
    ~MagicalContainer();                                        // Destructor (non-default)
    // functions
    void addElement(int);
    int size() const { return (int)this->_elements.size(); };
    void removeElement(int);
    void print(); // for troubleshooting
    // helper func for readding all elements
    bool isPrime(int);
    void reAddPrimes();

    class AscendingIterator
    {
    private:
        MagicalContainer &_container;
        std::vector<int>::iterator iter;
        size_t _currentElement;

    public:
        // constructor
        AscendingIterator(MagicalContainer &);
        //
        AscendingIterator(const AscendingIterator &);                                 // Copy constructor (non-default)
        AscendingIterator &operator=(const AscendingIterator &);                      // Copy assignment operator (non-default)
        AscendingIterator(AscendingIterator &&) noexcept = default;                   // Move constructor
        AscendingIterator &operator=(AscendingIterator &&other) noexcept { return *this; } // Move assignment operator (non-default)
        ~AscendingIterator() = default;                                               // Destructor

        // logical comparisons
        bool operator==(const AscendingIterator &) const;
        bool operator!=(const AscendingIterator &) const;
        bool operator>(const AscendingIterator &) const;
        bool operator<(const AscendingIterator &) const;
        //
        int operator*(); // dereference

        AscendingIterator operator++(int); // postfix (int is dummy flag)
        AscendingIterator &operator++();   // prefix

        AscendingIterator &begin();
        AscendingIterator &end();
    };
    //
    //
    //
    class SideCrossIterator
    {
    private:
        MagicalContainer &_container;
        std::vector<int>::iterator iter;
        std::vector<int>::reverse_iterator r_iter;
        size_t _currentElementFromStart;
        size_t _currentElementFromEnd;
        int _counter;

    public:
        // constructor
        SideCrossIterator(MagicalContainer &);
        //
        SideCrossIterator(const SideCrossIterator &);                                 // Copy constructor (non-default)
        SideCrossIterator &operator=(const SideCrossIterator &);                      // Copy assignment operator (non-default)
        SideCrossIterator(SideCrossIterator &&) noexcept = default;                   // Move constructor
        SideCrossIterator &operator=(SideCrossIterator &&other) noexcept { return *this; } // Move assignment operator (non-default)
        ~SideCrossIterator() = default;                                               // Destructor

        // logical comparison
        bool operator==(const SideCrossIterator &) const;
        bool operator!=(const SideCrossIterator &) const;
        bool operator>(const SideCrossIterator &) const;
        bool operator<(const SideCrossIterator &) const;
        //
        int operator*(); // dereference
        //
        SideCrossIterator operator++(int); // postfix (int is dummy flag)
        SideCrossIterator &operator++();   // prefix

        SideCrossIterator &begin();
        SideCrossIterator &end();
    };
    //
    //
    //
    class PrimeIterator
    {
    private:
        MagicalContainer &_container;
        std::vector<int *>::iterator iter;
        size_t _currentElement;

    public:
        // Constructor
        PrimeIterator(MagicalContainer &);
        //
        PrimeIterator(const PrimeIterator &);                                 // Copy constructor (non-default)
        PrimeIterator &operator=(const PrimeIterator &);                      // Copy assignment operator (non-default)
        PrimeIterator(PrimeIterator &&) noexcept = default;                   // Move constructor
        PrimeIterator &operator=(PrimeIterator &&other) noexcept { return *this; } // Move assignment operator (non-default)
        ~PrimeIterator() = default;                                           // Destructor
        //
        // logical comparison
        bool operator==(const PrimeIterator &) const;
        bool operator!=(const PrimeIterator &) const;
        bool operator>(const PrimeIterator &) const;
        bool operator<(const PrimeIterator &) const;
        //
        int operator*();
        //
        PrimeIterator operator++(int); // postfix (int is dummy flag)
        PrimeIterator &operator++();   // prefix

        PrimeIterator &begin();
        PrimeIterator &end();
    };

    // friend funcs
    // friend int returnAscend(AscendingIterator &, int);
    // friend int returnCross(SideCrossIterator &, int);
    // friend int returnPrime(PrimeIterator &, int);
};
//
//
//

// MagicalContainer::MagicalContainer(/* args */)
// {
// }

// MagicalContainer::~MagicalContainer()
// {
// }
namespace ariel
{
};