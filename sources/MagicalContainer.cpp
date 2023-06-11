#include "MagicalContainer.hpp"
#include <memory>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace ariel;
constexpr int dummyZero = 0;
constexpr int iteratorStartIndex = 0;
constexpr int containerSizeReduction = 1;
constexpr int evenAmountOfElementsInContainer = 2;
// Copy Constructor
MagicalContainer::MagicalContainer(MagicalContainer &other)
{
    this->_primeElems.clear();
    this->_elements.clear();
    this->_elements = other._elements;
    this->_primeElems = other._primeElems;
}

// Copy assignment operator
MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other)
{
    // clear vector elements
    this->_elements.clear();
    this->_primeElems.clear();
    // re-assign vector values
    this->_elements = other._elements;
    this->_primeElems = other._primeElems;
    return *this;
}
// Destructor
MagicalContainer::~MagicalContainer()
{
    this->_primeElems.clear();
    this->_elements.clear();
}

void MagicalContainer::addElement(int _recvVal)
{
    this->_primeElems.clear();
    this->_elements.emplace_back(_recvVal);        // insert value to vector
    this->_elements.shrink_to_fit();
    std::sort(_elements.begin(), _elements.end()); // sort vector (ascending order by default)
    this->reAddPrimes();                           // re-add all the primes
}

void MagicalContainer::removeElement(int _recvVal)
{
    auto _iterator = std::find(this->_elements.begin(), this->_elements.end(), _recvVal);
    if (_iterator == this->_elements.end() && *_iterator != _recvVal)
    {
        throw std::runtime_error("Tried removing non-existent value from container.");
    }
    this->_primeElems.clear(); // clear all previous pointers of primes in this->_elems
    this->_elements.erase(_iterator);
    this->_elements.shrink_to_fit();
    // no need to sort again as vector will move already sorted elements
    this->reAddPrimes(); // re-add the primes again
}

void MagicalContainer::print()
{
}
// helper func
bool MagicalContainer::isPrime(int _recvVal)
{
    if (_recvVal == 0 || _recvVal == 1)
    { // 0/1 arent primes
        return false;
    }
    // find if element is a prime number
    for (int i = 2; i <= (_recvVal / 2); ++i)
    {
        if (_recvVal % i == 0)
        {
            return false;
            break;
        }
    }
    // else
    return true;
}
void MagicalContainer::reAddPrimes() //  and add their address to the _primeElems pointer-vector
{
    // iterate over all elements
    for (auto iter = this->_elements.begin(); iter != this->_elements.end(); ++iter)
    {
        // if element is prime add pointer to _primeElems
        if (this->isPrime(*iter))
        {
            this->_primeElems.emplace_back(&(*iter));
        }
    }
}
//
//////////////// iterators
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ascending
//
// Constructor
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &other) : _container(other), iter(other._elements.begin()), _currentElement(iteratorStartIndex) {}

// Copy Constructor
MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer::AscendingIterator &other) : _container(other._container), iter(other.iter), _currentElement(other._currentElement) {}
// Copy assignment operator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this == &other)
        return *this;

    if (&(this->_container) != &other._container)
    {
        throw std::runtime_error("Iterators are bound to different containers. References cannot be re-assigned");
    }
    this->_currentElement = other._currentElement;
    this->iter = other.iter;
    return *this;
}
// Postfix
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::operator++(int dummy)
{
    if (this->iter == this->_container._elements.end())
    {
        throw std::runtime_error("Iterator is out of bounds");
    }
    MagicalContainer::AscendingIterator copy = *this;
    this->iter++;
    this->_currentElement++;
    return copy;
}
// Prefix
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (this->iter == this->_container._elements.end())
    {
        throw std::runtime_error("Iterator is out of bounds");
    }
    iter++;
    _currentElement++;
    return *this;
}
//
//
// Logical Comparisons
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value))
    {
        throw std::invalid_argument("Right iterator isn't AscendingIterator");
    }
    return (this->_currentElement == other._currentElement);
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value))
    {
        throw std::invalid_argument("Right iterator isn't AscendingIterator");
    }
    return (this->_currentElement > other._currentElement);
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value))
    {
        throw std::invalid_argument("Right iterator isn't AscendingIterator");
    }
    return (this->_currentElement < other._currentElement);
}

int MagicalContainer::AscendingIterator::operator*()
{
    // testing > instead of ==
    if (this->iter > this->_container._elements.end())
    {
        throw std::runtime_error("Iterator is out of bounds");
    }
    return *(this->iter);
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin()
{
    this->_currentElement = iteratorStartIndex;
    this->iter = this->_container._elements.begin();

    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end()
{
    this->_currentElement = this->_container._elements.size();
    this->iter = this->_container._elements.end();

    return *this;
}
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// sidecross
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &_container) : _container(_container),
                                                                                       iter(_container._elements.begin()),
                                                                                       r_iter(_container._elements.rbegin()),
                                                                                       _currentElementFromStart(iteratorStartIndex),
                                                                                       _currentElementFromEnd(_container._elements.size() - containerSizeReduction),
                                                                                       _counter(iteratorStartIndex) {}
//
// Copy Constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : _container(other._container), iter(other.iter),
                                                                                         r_iter(other.r_iter),
                                                                                         _currentElementFromStart(other._currentElementFromStart),
                                                                                         _currentElementFromEnd(other._currentElementFromEnd),
                                                                                         _counter(other._counter) {}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this == &other)
    {
        return *this;
    }
    if (&(this->_container) != &other._container)
    {
        throw std::runtime_error("Iterators are bound to different containers. References cannot be re-assigned");
    }
    this->iter = other.iter;
    this->r_iter = other.r_iter;
    this->_currentElementFromStart = other._currentElementFromStart;
    this->_currentElementFromEnd = other._currentElementFromEnd;
    this->_counter = other._counter;
    return *this;
}
// Postfix
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::operator++(int dummy)
{
    if (this->_container.size() != dummyZero)
    {                                                                      // container isn't empty
        if (this->_currentElementFromStart > this->_currentElementFromEnd) // indexes passed each other
            throw std::runtime_error("Iterator is out of bounds");
    }
    MagicalContainer::SideCrossIterator copy = *this;
    if (_counter % evenAmountOfElementsInContainer == dummyZero)
    {
        ++this->iter;
        this->_currentElementFromStart++;
        this->_counter++;
        return copy;
    }
    ++this->r_iter;
    this->_currentElementFromEnd--;
    this->_counter++;
    return copy;
}

// Prefix
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (this->_container.size() != dummyZero)
    {                                                                      // container isn't empty
        if (this->_currentElementFromStart > this->_currentElementFromEnd) // indexes passed each other
            throw std::runtime_error("Iterator is out of bounds");
    }
    if (_counter % evenAmountOfElementsInContainer == dummyZero)
    {
        ++this->iter;
        this->_currentElementFromStart++;
        this->_counter++;
        return *this;
    }
    ++this->r_iter;
    this->_currentElementFromEnd--;
    this->_counter++;
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value) || (!(std::is_same<decltype(r_iter), decltype(other.r_iter)>::value)))
    {
        throw std::invalid_argument("Right iterator isn't SideCrossIterator");
    }

    return (this->_currentElementFromStart == other._currentElementFromStart &&
            this->_currentElementFromEnd == other._currentElementFromEnd);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value) || (!(std::is_same<decltype(r_iter), decltype(other.r_iter)>::value)))
    {
        throw std::invalid_argument("Right iterator isn't SideCrossIterator");
    }
    return this->_currentElementFromStart > other._currentElementFromStart;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value) || (!(std::is_same<decltype(r_iter), decltype(other.r_iter)>::value)))
    {
        throw std::invalid_argument("Right iterator isn't SideCrossIterator");
    }
    return this->_currentElementFromStart < other._currentElementFromStart;
}

int MagicalContainer::SideCrossIterator::operator*()
{
    if (this->_container.size() != dummyZero)
    {                                                                      // container isn't empty
        if (this->_currentElementFromStart > this->_currentElementFromEnd) // indexes passed each other
            throw std::runtime_error("Iterator is out of bounds");
    }
    if (_counter % evenAmountOfElementsInContainer == dummyZero)
    {
        return *(this->iter);
    }
    return *(this->r_iter);
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin()
{
    this->_counter = iteratorStartIndex;
    this->iter = this->_container._elements.begin();
    this->r_iter = this->_container._elements.rbegin();
    this->_currentElementFromStart = iteratorStartIndex;
    this->_currentElementFromEnd = (unsigned long)this->_container.size() - containerSizeReduction; // container.size - 1
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end()
{
    // even amount of elements in container
    if (this->_container.size() % evenAmountOfElementsInContainer == dummyZero)
    {
        this->_currentElementFromStart = (unsigned long)(this->_container.size() / evenAmountOfElementsInContainer);
        this->_currentElementFromEnd = (unsigned long)((this->_container.size() / evenAmountOfElementsInContainer) - containerSizeReduction); // reduce by one so indexes pass each other - indicating the end()
        // this->_currentElementFromEnd = this->_currentElementFromStart + containerSizeReduction;
        std::advance(this->iter, _currentElementFromStart);
        std::advance(this->r_iter, _currentElementFromEnd);
    }
    this->_currentElementFromStart = (unsigned long)((this->_container.size() / evenAmountOfElementsInContainer) + containerSizeReduction); // increment by one so both indexes are on the same elment
    this->_currentElementFromEnd = (unsigned long)(this->_container.size() / evenAmountOfElementsInContainer);
    std::advance(this->iter, _currentElementFromStart);
    std::advance(this->r_iter, _currentElementFromEnd);
    return *this;
}
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// primes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &_container) : _container(_container), iter(_container._primeElems.begin()), _currentElement(iteratorStartIndex) {}
// Copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : _container(other._container), iter(other.iter), _currentElement(other._currentElement) {}
// Copy assignment operator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this == &other)
    {
        return *this;
    }
    if (&(this->_container) != &other._container)
    {
        throw std::runtime_error("Iterators are bound to different containers. References cannot be re-assigned");
    }
    this->iter = other.iter;
    this->_currentElement = other._currentElement;
    return *this;
}
// Postfix
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::operator++(int dummy)
{
    if (this->iter == this->_container._primeElems.end())
    {
        throw std::runtime_error("Iterator is out of bounds");
    }
    MagicalContainer::PrimeIterator copy = *this;
    this->iter++;
    this->_currentElement++;
    return copy;
}
// Prefix
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (this->iter == this->_container._primeElems.end())
    {
        throw std::runtime_error("Iterator is out of bounds");
    }
    iter++;
    _currentElement++;
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value))
    {
        throw std::invalid_argument("Right iterator isn't PrimeIterator.");
    }
    return this->_currentElement == other._currentElement;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value))
    {
        throw std::invalid_argument("Right iterator isn't PrimeIterator.");
    }
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value))
    {
        throw std::invalid_argument("Right iterator isn't PrimeIterator.");
    }
    return this->_currentElement > other._currentElement;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    if (!(std::is_same<decltype(iter), decltype(other.iter)>::value))
    {
        throw std::invalid_argument("Right iterator isn't PrimeIterator.");
    }
    return this->_currentElement < other._currentElement;
}

int MagicalContainer::PrimeIterator::operator*()
{
    if (this->iter > this->_container._primeElems.end())
    {
        throw std::runtime_error("Iterator is out of bounds");
    }
    return **(this->iter);
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin()
{
    this->_currentElement = iteratorStartIndex;
    this->iter = this->_container._primeElems.begin();
    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end()
{
    this->_currentElement = this->_container._primeElems.size();
    this->iter = this->_container._primeElems.end();
    return *this;
}

int returnAscend(int)
{
    return 0;
}
