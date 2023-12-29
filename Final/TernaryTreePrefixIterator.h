
// COS30008, Final Exam, 2022

#pragma once

#include "TernaryTree.h"

#include <stack>

template<typename T>
class TernaryTreePrefixIterator
{
private:
    using TTree = TernaryTree<T>;
    using TTreeNode = TTree*;
    using TTreeStack = std::stack<const TTree*>;
    
    const TTree* fTTree;                // ternary tree
    TTreeStack fStack;                  // traversal stack

public:

    using Iterator = TernaryTreePrefixIterator<T>;
       
    Iterator operator++(int)
    {
        Iterator old = *this;

        ++(*this);
           
        return old;
    }
       
    bool operator!=( const Iterator& aOtherIter ) const
    {
        return !(*this == aOtherIter);
    }

/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

private:
    
    // push subtree of aNode [30]
    void push_subtrees(const TTree* aNode)
    {
        if (!aNode->getRight().empty())
        {
            fStack.push(&aNode->getRight());
        }
        if (!aNode->getMiddle().empty())
        {
            fStack.push(&aNode->getMiddle());
        }
        if (!aNode->getLeft().empty())
        {
            fStack.push(&aNode->getLeft());
        }
    }


public:
    
	// iterator constructor [12]
    explicit TernaryTreePrefixIterator(const TTree* aTTree) : fTTree(aTTree), fStack()
    {
        if (!fTTree->empty())
        {
            fStack.push(fTTree);
        }
    }

	// iterator dereference [8]
    const T& operator*() const
    {
        return fStack.top()->operator*();
    }

    // prefix increment [12]
    Iterator& operator++()
    {
        auto poppedNode = (TTreeNode)(fStack.top());
        fStack.pop();
        push_subtrees(poppedNode);
        return *this;
    }

    // iterator equivalence [12]
    bool operator==( const Iterator& aOtherIter ) const
    {
        return fTTree == aOtherIter.fTTree && fStack.size() == aOtherIter.fStack.size();
    }

    // auxiliaries [4,10]
    Iterator begin() const
    {
        Iterator beginIterator = *this;
        beginIterator.fStack = TTreeStack();
        beginIterator.fStack.push((TTreeNode)(beginIterator.fTTree));
        return beginIterator;
    }
    Iterator end() const
    {
        Iterator endIterator = *this;
        endIterator.fStack = TTreeStack();
        return endIterator;
    }

};
