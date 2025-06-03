/// \file binary_tree.h
/// \brief Defines a templated Binary Search Tree (BST) with insertion, search, and traversal functions.

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * \brief Represents a node in a binary search tree.
 *
 * \tparam T Type of the value stored in the node.
 */
template <typename T> 
class Node {
public:
    Node() = default;
    Node(T value) { value_ = value; }

public:
    T value_;                ///< The value stored in the node.
    Node *left_ = nullptr;   ///< Pointer to the left child node.
    Node *right_ = nullptr;  ///< Pointer to the right child node.
};

/**
 * \brief Implements a simple Binary Search Tree (BST).
 *
 * Provides operations to insert values, search for a single value or all occurrences,
 * and print the tree in a pre-order traversal.
 *
 * \tparam T Type of the values stored in the tree.
 */
template <typename T> 
class Tree {
public:
    /// \defgroup constructors Constructors and destructor
    /// \{
    
    Tree() { root_ = nullptr; }
    Tree(T value) { root_ = new Node<T>(value); }
    ~Tree() { DeleteTree(root_); }
    /// \}

    /// \defgroup main_methods Insert, search and visualization of the tree
    /// \{

    /// \brief Insert a new value into the BST.
    ///
    /// If the tree is empty, the new value becomes the root. Otherwise, traverse
    /// the tree and insert the new node in the correct position to maintain BST property.
    ///
    /// \param value Reference to the value to insert.
    ///
    void Insert(const T& value) {
        if (!root_) {
            root_ = new Node<T>(value);
            return;
        }

        Node<T> *cur = root_;
        while (true) {
            if (value < cur->value_) {
                if (cur->left_ == nullptr) {
                    cur->left_ = new Node<T>(value);
                    break;
                }
                cur = cur->left_;
            } else {
                if (cur->right_ == nullptr) {
                    cur->right_ = new Node<T>(value);
                    break;
                }
                cur = cur->right_;
            }
        }
    }

    /**
     * \brief Search for the first node containing a given value.
     *
     * \param value Reference to the value to search for.
     * \return Pointer to the node containing the value, or nullptr if not found.
     */
    Node<T>* Search(const T& value) const { return SupportSearch(root_, value); }

    /**
     * \brief Search for all nodes containing a given value.
     * \param value Reference to the value to search for.
     * \return A vector of pointers to nodes containing the value. If none found, returns an empty vector.
     */
    vector<Node<T>*> SearchAll(const T& value) {
        vector<Node<T>*> res;
        Node<T> *tmp = SupportSearch(root_, value);
        
        while (tmp) {
            res.push_back(tmp);
            tmp = SupportSearch(tmp->right_, value);
        }

        return res;
    }

    /// \brief Print all values in the tree using pre-order traversal.
    void PrintTree() { SupportPrint(root_); }
    /// \}

private:
    Node<T> *root_ = nullptr;

private:
    /// \defgroup supporting_methods Supporting methods for basic methods
    /// \{

    /**
     * \brief Helper function for pre-order traversal and printing.
     * \param root Pointer to the current subtree root.
     */
    void SupportPrint(Node<T> *root) {
        if (root) {
            cout << root->value_ << endl;
            SupportPrint(root->left_);
            SupportPrint(root->right_);
        }
    }

    /**
     * \brief Helper function to search for a value starting at a given node.
     *
     * Traverses the tree like a standard BST search: if the current node's value
     * matches, return it; if the value is less, go left; otherwise, go right.
     *
     * \param root  Pointer to the current node from which to start searching.
     * \param value Reference to the value to search for.
     * \return Pointer to the node containing the value, or nullptr if not found.
     */
    Node<T>* SupportSearch(Node<T>* root, const T& value) {
        Node<T> *cur = root;

        while (cur) { 
            if (cur->value_ == value) { return cur; }

            if (value < cur->value_) {
                cur = cur->left_;
            } else {
                cur = cur->right_;
            }
        }

        return nullptr;
    }

    /// \brief Recursively delete all nodes in the subtree.
    void DeleteTree(Node<T> *root) {
        if (root) {
            DeleteTree(root->left_);
            DeleteTree(root->right_);
            delete root;
        }
    }
    /// \}
};

#endif