
// COS30008, Problem Set 3, 2023

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

template<typename T>
class ListPS3
{
private:
    using Node = typename DoublyLinkedList<T>::Node;
    
    Node fHead;		// first element
    Node fTail;		// last element
    size_t fSize;	// number of elements
    
public:

    using Iterator = DoublyLinkedListIterator<T>;
    
    ListPS3() noexcept;							// default constructor

	// copy semantics
    ListPS3(const ListPS3& aOther );					// copy constructor
    ListPS3& operator=(const ListPS3& aOther );		// copy assignment

	// move semantics
    ListPS3(ListPS3&& aOther ) noexcept;				// move constructor
    ListPS3& operator=(ListPS3&& aOther ) noexcept;	// move assignment
    void swap(ListPS3& aOther ) noexcept;			// swap elements

	// basic operations
    size_t size() const noexcept;				// list size
    
    template<typename U>
    void push_front( U&& aData );				// add element at front
    
    template<typename U>
    void push_back( U&& aData );				// add element at back
    
    void remove( const T& aElement ) noexcept;	// remove element
    
    const T& operator[]( size_t aIndex ) const;	// list indexer
    
	// iterator interface
    Iterator begin() const noexcept;
    Iterator end() const noexcept;
	Iterator rbegin() const noexcept;
    Iterator rend() const noexcept;
};
