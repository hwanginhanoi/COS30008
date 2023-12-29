#pragma once
#include "BinaryTreeNode.h"
#include <stdexcept>
// Problem 3 requirement
template<typename T>
class BinarySearchTreeIterator;
template<typename T>
class BinarySearchTree
{
private:
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    BTreeNode fRoot;

public:
    BinarySearchTree() : fRoot(&BNode::NIL) {}

    ~BinarySearchTree()
    {
        if (fRoot && !fRoot->empty())
        {
            delete fRoot;
        }
    }

    [[nodiscard]] bool empty() const
    {
        return fRoot->empty();
    }

    [[nodiscard]] size_t height() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree has no height.");
        }
        else
        {
            return fRoot->height();
        }
    }

    bool insert(const T& aKey)
    {
        if (empty())
        {
            fRoot = new BNode(aKey);
            return true;
        }
        else {
            return fRoot->insert(aKey);
        }
    }

    bool remove(const T& aKey)
    {
        if (empty()) {
            throw std::domain_error("Cannot remove in an empty tree.");
        }
        else if (fRoot->leaf() && fRoot->key == aKey) {
            fRoot = &BNode::NIL;
            return true;
        }
        else {
            return fRoot->remove(aKey, &BNode::NIL);
        }
    }

    // Problem 3 methods

    using Iterator = BinarySearchTreeIterator<T>;
    // Allow iterator to access private member variables
    friend class BinarySearchTreeIterator<T>;
    Iterator begin() const
    {
        Iterator iterator(*this);
        return iterator.begin();
    }

    Iterator end() const
    {
        Iterator iterator(*this);
        return iterator.end();
    }
};