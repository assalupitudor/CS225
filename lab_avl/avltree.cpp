/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::changeHeight(Node*& subroot) {
    subroot->height = std::max(heightOrNeg1(subroot->right), heightOrNeg1(subroot->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* x = t->right;
    t->right = x->left;
    x->left = t;
    //change height of original node before updating
    changeHeight(t);
    changeHeight(x);
    t = x;
    
    

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* x = t->left;
    t->left = x->right;
    x->right = t;
    //change height of original node before updating
    changeHeight(t);
    changeHeight(x);
    t = x;
    

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    //check where the imbalace is
    if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) < -1) {
        int left_tree_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        //check if it is in the left tree, if it is not in the left tree then it must be in the right tree
        if (left_tree_balance == -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    } else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) > 1) {
        int right_tree_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (right_tree_balance == 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }
    changeHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
    

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * current_node = subtree;
            Node * iop = subtree->left;
            while (iop->right) {
              current_node = iop;
              iop = iop->right;
            }
            swap(subtree, iop);
            Node * temp = iop;
            current_node->right = iop->left;
            delete temp;
        } else {
            /* one-child remove */
            // your code here
            if (!subtree->left && subtree->right) {
              Node * temp = subtree;
              subtree = subtree->right;
              delete temp;
            } else if (subtree->left && !subtree->right) {
              Node * temp = subtree;
              subtree = subtree->left;
              delete temp;
            }
        }
        // your code here
    }
}
