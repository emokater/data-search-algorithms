/// \file rb_tree.h
/// \brief Defines a templated Red-Black Tree with insertion, search, and traversal functions.
/// 
/// This file provides:
/// - RBNode: A node structure storing a value, color, and pointers to parent and children.
/// - RBTree: A Red-Black Tree implementation supporting insertion, search (single and all occurrences),
///   and printing the tree.

#ifndef RB_TREE_H
#define RB_TREE_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

/// \brief Enumeration for node color in a Red-Black Tree.
typedef enum { RED, BLACK } Color;


/**
 * \brief Represents a node in a Red-Black Tree.
 *
 * Each node stores a value of type T, its color, and pointers to left, right, and parent nodes.
 *
 * \tparam T Type of the value stored in the node.
 */
template <typename T> 
class RBNode {
public:
    vector<T> values_;
    Color color_;

    RBNode *left_, *right_, *parent_;

public:
    RBNode() {
        color_ = RED;
        left_ = nullptr;
        right_ = nullptr;
        parent_ = nullptr;
        values_ = T();
    }

    RBNode(const T value) { 
        values_.push_back(value); 
        color_ = RED;
        left_ = nullptr;
        right_ = nullptr;
        parent_ = nullptr;
    }

    /**
     * \brief Assignment operator for RBNode.
     * \param other The node to copy from.
     * \return Reference to this node after copying.
     *
     * Copies value, color, and pointers from another node.
     */
    RBNode& operator=(const RBNode& other) {
        values_ = other.values_;
        color_ = other.color_;
        left_ = other.left_;
        right_ = other.right_;
        parent_ = other.parent_;

        return *this;
    }
};

/**
 * \brief Implements a Red-Black Tree.
 *
 * Provides operations to insert values, search for a single value or all occurrences,
 * and print the tree. Maintains Red-Black properties for balancing after insertions.
 *
 * \tparam T Type of the values stored in the tree.
 */
template <typename T> 
class RBTree {
public:
    /// \defgroup constructors Constructors and destructor
    /// \{

    RBTree() { root_ = nullptr; }
    RBTree(T value) { 
        root_ = new RBNode<T>(value);
        root_->color_ = BLACK; ///< The root node is always initialized with BLACK color.
    }
    ~RBTree() { DelTree(root_); }
    /// \}

    /// \defgroup main_methods Insert, search and visualization of the tree
    /// \{

    /**
     * \brief Insert a new value into the Red-Black Tree.
     *
     * If the tree is empty, the new node becomes the root and is colored BLACK.
     * Otherwise, insert similar to a BST and then rebalance via Balance().
     *
     * \param value Reference to the value to insert.
     */
    void Insert(const T& value) {
        if (!root_) {
            root_ = new RBNode<T>(value);
            root_->color_ = BLACK;
            return;
        }

        RBNode<T> *target = root_;
        RBNode<T> *parent = nullptr;

        while(target) {
            parent = target;
            if (value < target->values_[0]) {
                target = target->left_;
            } else if (value > target->values_[0]){
                target = target->right_;
            } else {
                target->values_.push_back(value);
                return;
            }
        }

        target = new RBNode<T>(value);
        target->parent_ = parent;

        if (value < parent->values_[0]) {
            parent->left_ = target;
        } else {
            parent->right_ = target;
        }

        Balance(target);
    }

    // /// @brief  Search for all nodes containing a given value.
    // /// @param value Reference to the value to search for.
    // /// @return Pointer to the node containing the value, or nullptr if not found.
    // RBNode<T>* Search(const T& value) {
    //     return SupSearch(root_, value);
    // }

    /// @brief Search for all nodes containing a given value.
    /// @param value Reference to the value to search for.
    /// @return A vector of pointers to nodes containing the value. If none found, returns an empty vector.
    RBNode<T>* SearchAll(const T& value) {
        if (root_) {
            RBNode<T> *cur = root_;

            while (cur) {
                if (cur->values_[0] == value) {
                    return cur;
                } 

                if (value < cur->values_[0]) {
                    cur = cur->left_;
                } else {
                    cur = cur->right_;
                }
            }
        }

        return nullptr;
    }

    /// \brief Print all nodes in the tree using pre-order traversal.
    void PrintTree() {
        SupportPrint(root_);
    }
    /// \}

private:
    RBNode<T> *root_;  ///< Pointer to the root node of the tree.

private:
    /// \defgroup supporting_methods Supporting methods for basic methods
    /// \{

    // /**
    //  * \brief Helper function to search for a value starting at a given node.
    //  *
    //  * Traverses the subtree like a standard BST search: if the current node's value
    //  * matches, returns it; if the value is less, goes left; otherwise, goes right.
    //  *
    //  * \param node  Pointer to the current node from which to start searching.
    //  * \param value Reference to the value to search for.
    //  * \return Pointer to the node containing the value, or nullptr if not found.
    //  */
    // RBNode<T>* SupSearch(RBNode<T> *node, const T& value) {
    //     if (node) {
    //         RBNode<T> *cur = node;

    //         while (cur) {
    //             if (cur->values_[0] == value) {
    //                 return cur;
    //             } 

    //             if (value < cur->value_) {
    //                 cur = cur->left_;
    //             } else {
    //                 cur = cur->right_;
    //             }
    //         }
    //     }

    //     return nullptr;
    // }

    /// @brief Helper function for pre-order traversal and printing.
    void SupportPrint(RBNode<T> *root) {
        if (root) {
            cout << root->values_ << " " << root->color_ << endl;
        
            SupportPrint(root->left_);
            SupportPrint(root->right_);
        }
    }

    /// @brief Recursively deletes all nodes in the subtree rooted at the given node.
    void DelTree(RBNode<T> *root) {
        if (root) {
            DelTree(root->left_);
            DelTree(root->right_);
            delete root;
        }
    }

    /**
     * \brief Restores Red-Black Tree properties by rebalancing starting from the given node.
     *
     * This function fixes the tree after insertion by performing recoloring and rotations
     * to ensure that:
     *   1. The root is always black.
     *   2. No red node has a red parent.
     *   3. Every path from the root to a leaf has the same number of black nodes.
     *
     * The algorithm handles two main cases depending on whether the parent of the node
     * is a left or right child of its grandparent, and within each case it distinguishes:
     *   - Case 1: Parent and uncle are both red (recoloring).
     *   - Case 2: Parent is red but uncle is black (rotations + recoloring).
     *
     * @tparam T            The type stored in the Red-Black Tree nodes.
     * @param[in,out] node  Pointer to the newly inserted node that may violate Red-Black properties.
     */
    void Balance(RBNode<T> *node) {
        RBNode<T> *dad = node->parent_;

        while (dad && dad->color_ == RED) {
            RBNode<T> *grand = dad->parent_;
            RBNode<T> *uncle;

            if (!grand) {
                return;
            } else if (dad == grand->left_) {
                uncle = grand->right_;

                // 1
                if (uncle && uncle->color_ == RED) {
                    dad->color_ = BLACK;
                    uncle->color_ = BLACK;
                    grand->color_ = RED;

                    node = grand;
                    dad = node->parent_;
                    if (dad) { grand = dad->parent_; }

                    continue;
                } else { // 2
                    if (dad->right_ == node) {
                        LeftRotate(node, dad, grand);
                        node = dad;
                        dad  = node->parent_;
                    } 
                    dad->color_ = BLACK;
                    grand->color_  = RED;
                    RightRotate(dad, grand, grand->parent_);
                    break;
                }
            } else {
                uncle = grand->left_;

                if (uncle && uncle->color_ == RED) {
                    dad->color_ = BLACK;
                    uncle->color_ = BLACK;
                    grand->color_ = RED;

                    node = grand;
                    dad = node->parent_;
                    if (dad) { grand = dad->parent_; }

                    continue;
                } else {
                    if (dad->left_ == node) {
                        RightRotate(node, dad, grand);
                        node = dad;
                        dad  = node->parent_;
                    }
                    dad->color_ = BLACK;
                    grand->color_  = RED;
                    LeftRotate(dad, grand, grand->parent_);
                    break;
                }
            }
        }

        root_->color_ = BLACK;
    }

    /**
     * @brief Perform a left rotation around a given parent and child.
     *
     * After rotation:
     *   - `child` takes the place of `dad` in the tree.
     *   - The left subtree of `child` becomes the right subtree of `dad`.
     *   - Parent pointers are updated accordingly.
     *
     * @tparam T                 The type stored in the Red-Black Tree nodes.
     * @param[in] child          Pointer to the right child of `dad` which will become the new parent.
     * @param[in,out] dad        Pointer to the node being rotated down (its right child is `child`).
     *                           After rotation, `dad` becomes the left child of `child`.
     * @param[in,out] grand      Pointer to the parent of `dad` before rotation. After rotation,
     *                           `grand`’s appropriate child pointer is updated to point to `child`.
     */
    void LeftRotate(RBNode<T> *child, RBNode<T> *dad, RBNode<T> *grand) {
        RBNode<T> *grandson = child->left_;

        dad->right_ = grandson;
        if (grandson) { grandson->parent_ = dad; }

        child->left_ = dad;
        dad->parent_ = child;

        child->parent_ = grand;
        if (!grand) {
            root_ = child;
        } else if (grand->left_ == dad) {
            grand->left_ = child;
        } else {
            grand->right_ = child;
        }
    }

    /**
     * @brief Perform a right rotation around a given parent and child.
     *
     * After rotation:
     *   - `child` takes the place of `dad` in the tree.
     *   - The right subtree of `child` becomes the left subtree of `dad`.
     *   - Parent pointers are updated accordingly.
     *
     * @tparam T                 The type stored in the Red-Black Tree nodes.
     * @param[in] child          Pointer to the left child of `dad` which will become the new parent.
     * @param[in,out] dad        Pointer to the node being rotated down (its left child is `child`).
     *                           After rotation, `dad` becomes the right child of `child`.
     * @param[in,out] grand      Pointer to the parent of `dad` before rotation. After rotation,
     *                           `grand`’s appropriate child pointer is updated to point to `child`.
     */
    void RightRotate(RBNode<T> *child, RBNode<T> *dad, RBNode<T> *grand) {
        RBNode<T> *grandson = child->right_;

        dad->left_ = grandson;
        if (grandson) { grandson->parent_ = dad; }

        dad->parent_ = child;
        child->right_ = dad;

        child->parent_ = grand;
        if (!grand) {
            root_ = child;
        } else if (grand->right_ == dad) {
            grand->right_ = child;
        } else {
            grand->left_ = child;
        }
    }
    /// \}
};

#endif