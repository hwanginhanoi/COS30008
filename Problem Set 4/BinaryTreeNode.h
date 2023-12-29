#pragma once
#include <stdexcept>
#include <algorithm>
using namespace std;
template<typename T>
struct BinaryTreeNode
{
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;

    T key;
    BTreeNode left;
    BTreeNode right;

    static BNode NIL;

    const T& findMax() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree encountered");
        }
        else {
            return (right->empty()) ? key : right->findMax();
        }
    }

    const T& findMin() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree encountered");
        }
        else {
            return (left->empty()) ? key : left->findMin();
        }
    }


    bool remove(const T& aKey, BTreeNode aParent)
    {
        BTreeNode current = this;
        BTreeNode parent = aParent;

        // Search for the node to be removed
        while (!current->empty() && aKey != current->key)
        {
            parent = current;
            current = (aKey < current->key) ? current->left : current->right;
        }

        // If the node is not found
        if (current->empty())
        {
            return false;
        }

        if (!current->left->empty())
        {
            T replacementKey = std::move(current->left->findMax());
            current->key = std::move(replacementKey);
            current->left->remove(current->key, current);
        }
        else if (!current->right->empty())
        {
            T replacementKey = std::move(current->right->findMin());
            current->key = std::move(replacementKey);
            current->right->remove(current->key, current);
        }
        else // Node has no children
        {
            if (parent != &NIL)
            {
                (parent->left == current) ? parent->left = &NIL : parent->right = &NIL;
            }
            delete current;
        }

        return true;
    }

    BinaryTreeNode(): key(T()), left(&NIL), right(&NIL){}

    explicit BinaryTreeNode(const T& aKey): key(aKey), left(&NIL), right(&NIL){}

    explicit BinaryTreeNode(T&& aKey): key(std::move(aKey)), left(&NIL), right(&NIL){}

    ~BinaryTreeNode()
    {
        if (left && !left->empty())
        {
            delete left;
        }

        if (right && !right->empty())
        {
            delete right;
        }
    }

    [[nodiscard]] bool empty() const {
        return this == &NIL;
    }

    [[nodiscard]] bool leaf() const {
        return (left == &NIL) && (right == &NIL);
    }

    [[nodiscard]] size_t height() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree encountered");
        }
        else if (leaf()) {
            return 0;
        }
        else {
            return 1 + std::max(left->empty() ? 0 : left->height(), right->empty() ? 0 : right->height());
        }
    }

    bool insert(const T& aKey) {
        if (aKey == key || empty())
            return false;
        else if (aKey < key) {
            if (!left->empty())
                return left->insert(aKey);
            left = new BNode(aKey);
            return true;
        }
        else {
            if (!right->empty())
                return right->insert(aKey);
            right = new BNode(aKey);
            return true;
        }
    }

};
template<typename T>
BinaryTreeNode<T> BinaryTreeNode<T>::NIL;