#pragma once
#include "BinarySearchTree.h"
#include <stack>
template<typename T>
class BinarySearchTreeIterator
{
private:

    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;
    const BSTree& fBSTree; // binary search tree
    BTNStack fStack; // DFS traversal stack

    void pushLeft(BTreeNode aNode)
    {
        if (!aNode->empty())
        {
            fStack.push(aNode);
            pushLeft(aNode->left);
        }
    }

public:

    using Iterator = BinarySearchTreeIterator<T>;

    explicit BinarySearchTreeIterator(const BSTree& aBSTree): fBSTree(aBSTree), fStack()
    {
        pushLeft(aBSTree.fRoot);
    }

    const T& operator*() const
    {
        return fStack.top()->key;
    }

    Iterator& operator++()
    {
        while (!fStack.empty()) {
            BTreeNode lPopped = fStack.top();
            fStack.pop();
            pushLeft(lPopped->right);

            if (!fStack.empty()) {
                break;
            }
        }

        return *this;
    }


    Iterator operator++(int)
    {
        Iterator temp = std::exchange(*this, Iterator(*this));
        return temp;
    }

    bool operator==(const Iterator& aOtherIter) const
    {
        return (&fBSTree == &aOtherIter.fBSTree) && (fStack == aOtherIter.fStack);
    }

    bool operator!=(const Iterator& aOtherIter) const
    {
        return !(*this == aOtherIter);
    }

    Iterator begin() const
    {
        Iterator temp(*this);
        {
            temp.fStack = BTNStack();
            temp.pushLeft(temp.fBSTree.fRoot);
        }
        return temp;
    }

    Iterator end() const
    {
        Iterator temp(*this);

        if (!temp.fBSTree.empty())
        {
            temp.fStack = BTNStack();
        }
        return temp;
    }

};