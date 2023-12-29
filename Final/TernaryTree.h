#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
class TernaryTreePrefixIterator;

template<typename T>
class TernaryTree {
public:

    using TTree = TernaryTree<T>;
    using TSubTree = TTree *;
private:

    T fKey;
    TSubTree fSubTrees[3];

    // private default constructor used for declaration of NIL
    TernaryTree() :
            fKey(T()) {
        for (size_t i = 0; i < 3; i++) {
            fSubTrees[i] = &NIL;
        }
    }

public:
    using Iterator = TernaryTreePrefixIterator<T>;

    static TTree NIL; // sentinel
    // getters for subtrees
    const TTree &getLeft() const { return *fSubTrees[0]; }

    const TTree &getMiddle() const { return *fSubTrees[1]; }

    const TTree &getRight() const { return *fSubTrees[2]; }

    // add a subtree
    void addLeft(const TTree &aTTree) { addSubTree(0, aTTree); }

    void addMiddle(const TTree &aTTree) { addSubTree(1, aTTree); }

    void addRight(const TTree &aTTree) { addSubTree(2, aTTree); }

    // remove a subtree, may through a domain error
    const TTree &removeLeft() { return removeSubTree(0); }

    const TTree &removeMiddle() { return removeSubTree(1); }

    const TTree &removeRight() { return removeSubTree(2); }

/////////////////////////////////////////////////////////////////////////
// Problem 1: TernaryTree Basic Infrastructure
private:
    // remove a subtree, may throw a domain error [22]
    const TTree& removeSubTree(size_t aSubtreeIndex)
    {
        if (aSubtreeIndex >= 3)
        {
            throw domain_error("Illegal subtree index");
        }

        TSubTree& subtreeToRemove = fSubTrees[aSubtreeIndex];

        if (subtreeToRemove->empty())
        {
            throw domain_error("Subtree is NIL");
        }

        const TTree& removedSubtree = *subtreeToRemove;
        subtreeToRemove = &NIL;

        return removedSubtree;
    }


    // add a subtree; must avoid memory leaks; may throw domain error [18]
    void addSubTree(size_t aSubtreeIndex, const TTree& aTTree)
    {
        if (empty())
        {
            throw domain_error("Operation not supported");
        }

        if (aSubtreeIndex >= 3)
        {
            throw domain_error("Operation not supported");
        }
        TSubTree& currentSubTree = fSubTrees[aSubtreeIndex];

        if (!currentSubTree->empty())
        {
            throw domain_error("Subtree is not NIL");
        }

        currentSubTree = new TTree(aTTree);
    }
public:

    // TernaryTree l-value constructor [10]
    explicit TernaryTree(const T& aKey) : fKey(aKey)
    {
        for (auto& subtree : fSubTrees)
        {
            subtree = &NIL;
        }
    }
    // destructor (free sub-trees, must not free empty trees) [14]
    ~TernaryTree()
    {
        if (!empty())
        {
            for (auto& subtree : fSubTrees)
            {
                if (!subtree->empty())
                {
                    delete subtree;
                }
            }
        }
    }

    // return key value, may throw domain_error if empty [6]
    const T& operator*() const
    {
        return (empty()) ? throw domain_error("Tree is empty") : fKey;
    }

    // returns true if this ternary tree is empty [4]
    [[nodiscard]] bool empty() const
    {
        return this == &NIL;
    }

    // returns true if this ternary tree is a leaf [10]
    [[nodiscard]] bool leaf() const
    {
        for (const auto& subtree : fSubTrees)
        {
            if (!subtree->empty())
            {
                return false;
            }
        }
        return true;
    }

    // return height of ternary tree, may throw domain_error if empty [48]
    [[nodiscard]] size_t height() const
    {
        if (empty())
        {
            throw domain_error("Operation not supported");
        }
        else
        {
            return calculateHeight();
        }
    }

    // return height of ternary tree, may throw domain_error if empty [48]
    [[nodiscard]] size_t calculateHeight() const
    {
        if (leaf())
        {
            return 0;
        }

        size_t maxChildHeight = 0;
        for (auto & fSubTree : fSubTrees)
        {
            if (!fSubTree->empty())
            {
                size_t childHeight = fSubTree->calculateHeight();
                maxChildHeight = max(maxChildHeight, childHeight);
            }
        }

        return maxChildHeight + 1;
    }

/////////////////////////////////////////////////////////////////////////
// Problem 2: TernaryTree Copy Semantics

    // copy constructor, must not copy empty ternary tree [10]
    TernaryTree(const TTree& aOtherTTree)
    {
        fKey = aOtherTTree.fKey;

        for (int i = 0; i < 3; i++)
        {
            if (!aOtherTTree.fSubTrees[i]->empty())
            {
                fSubTrees[i] = new TTree(*(aOtherTTree.fSubTrees[i]));
            }
            else
            {
                fSubTrees[i] = &NIL;
            }
        }
    }
    // copy assignment operator, must not copy empty ternary tree
    // may throw a domain error on attempts to copy NIL [36]
    TTree& operator=(const TTree& aOtherTTree)
    {
        if (this != &aOtherTTree)
        {
            if (!aOtherTTree.empty())
            {
                fKey = aOtherTTree.fKey;

                for (auto& subtree : fSubTrees)
                {
                    const auto& otherSubtree = *aOtherTTree.fSubTrees[&subtree - fSubTrees];

                    subtree = otherSubtree.empty() ? &NIL : otherSubtree.clone();
                }
            }
            else
            {
                throw domain_error("NIL as source not permitted.");
            }
        }
        return *this;
    }

    // clone ternary tree, must not copy empty trees [10]
    TSubTree clone() const
    {
        if (empty())
        {
            throw domain_error("NIL as source not permitted.");
        }
        else
        {
            auto* clonedTree = new TTree(*this);
            return clonedTree;
        }
    }

/////////////////////////////////////////////////////////////////////////
// Problem 3: TernaryTree Move Semantics
    // TTree r-value constructor [12]
    explicit TernaryTree(T&& aKey) : fKey(std::move(aKey))
    {
        for (auto& subtree : fSubTrees)
        {
            subtree = &NIL;
        }
    }
    // move constructor, must not copy empty ternary tree [12]
    TernaryTree(TTree&& aOtherTTree)
    {
        fKey = std::move(aOtherTTree.fKey);

        for (int i = 0; i < 3; i++)
        {
            fSubTrees[i] = std::exchange(aOtherTTree.fSubTrees[i], &NIL);
        }
    }

    // move assignment operator, must not copy empty ternary tree [36]
    TTree& operator=(TTree&& aOtherTTree)
    {
        if (this != &aOtherTTree)
        {
            if (!aOtherTTree.empty())
            {
                this->~TernaryTree();
                fKey = std::move(aOtherTTree.fKey);

                for (int i = 0; i < 3; i++)
                {
                    fSubTrees[i] = aOtherTTree.fSubTrees[i];
                    aOtherTTree.fSubTrees[i] = &NIL;
                }

                aOtherTTree.fKey = T();
            }
            else
            {
                throw std::domain_error("NIL as source not permitted.");
            }
        }
        return *this;
    }

/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator
    // return ternary tree prefix iterator positioned at start [4]
    Iterator begin() const
    {
        return Iterator(this).begin();
    }

    // return ternary prefix iterator positioned at end
    Iterator end() const
    {
        return Iterator(this).end();
    }
};

template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;