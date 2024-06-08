#include <bits/stdc++.h>
#include "trees.h"


Node::Node(int value, bool is_red, Node* parent, Node* root){
    this->value = value;
    this->is_red = is_red;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
    this->root = root;
}


void print_tree_util(Node* root, int space){
	if(root == NULL){
        return;
    }

	space += 5;

	print_tree_util(root->right, space);

	std::cout << std::endl;
	for(int i = 5; i < space; i++){
        std::cout << " ";
    }
	std::cout << root->value << "\n";

	print_tree_util(root->left, space);
}


void print_tree(Node* root){
	print_tree_util(root, 0);
}


/**
 * *************** Binary Search Tree ***************
 */
BST::BST(){
    this->root = nullptr;
}


Node* BST::insert_value_rec(Node* node, int value){
    if(node == nullptr){
        Node* new_node = new Node(value);
        return new_node;
    }
    if(value < node->value){
        node->left = insert_value_rec(node->left, value);
    }
    else if(value > node->value){
        node->right = insert_value_rec(node->right, value);
    }

    return node;
}


void BST::insert_value(int value){
    this->root = insert_value_rec(this->root, value);
}


Node* BST::min_value_node(Node* node){
    Node* current = node;
    while(current && current->left != nullptr){
        current = current->left;
    }
    return current;
}


Node* BST::delete_value_rec(Node* root, int value){
    if(root == nullptr)
        return root;

    if(value < root->value){
        root->left = delete_value_rec(root->left, value);
    }
    else if(value > root->value){

        root->right = delete_value_rec(root->right, value);
    }
    else{
        if(root->left == nullptr){
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == nullptr){
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = min_value_node(root->right);
        root->value = temp->value;
        root->right = delete_value_rec(root->right, temp->value);
    }
    return root;
}


void BST::delete_value(int value){
    delete_value_rec(this->root, value);
}


int BST::height_rec(Node* node){
    if(node == nullptr){
        return 0;
    }
    else{
        int height_left = height_rec(node->left);
        int height_right = height_rec(node->right);
 
        if(height_left > height_right){
            return height_left + 1;
        }
        else{
            return height_right + 1;
        }
    }
}


int BST::height(){
    return height_rec(this->root);
}


/**
 * *************** Red Black Tree ***************
 */
RBT::RBT(){
    root = nullptr;
}


void RBT::left_rotation(Node* node){
    Node* child = node->right;
    node->right = child->left;

    if(child->left != nullptr){
        child->left->parent = node;
    }
    child->parent = node->parent;

    if(node->parent == nullptr){
        this->root = child;
    }
    else if(node == node->parent->left){
        node->parent->left = child;
    }
    else{
        node->parent->right = child;
    }

    child->left = node;
    node->parent = child;
}


void RBT::right_rotation(Node* node){
    Node* child = node->left;
    node->left = child->right;

    if(child->right != nullptr){
        child->right->parent = node;
    }
    child->parent = node->parent;

    if(node->parent == nullptr){
        this->root = child;
    }
    else if(node == node->parent->right){
        node->parent->right = child;
    }
    else{
        node->parent->left = child;
    }

    child->right = node;
    node->parent = child;
}


void RBT::fix_insert(Node* node_x){
    while(node_x != this->root && node_x->parent->is_red){
        if(node_x->parent == node_x->parent->parent->left){
            Node* node_y = node_x->parent->parent->right;
            if(node_y && node_y->is_red){
                node_x->parent->is_red = false;
                node_y->is_red = false;
                node_x->parent->parent->is_red = true;
                node_x = node_x->parent->parent;
            }
            else{
                if(node_x == node_x->parent->right){
                    node_x = node_x->parent;
                    left_rotation(node_x);
                }
                node_x->parent->is_red = false;
                node_x->parent->parent->is_red = true;
                right_rotation(node_x->parent->parent);
            }
        }
        else{
            Node* node_y = node_x->parent->parent->left;
            if(node_y && node_y->is_red){
                node_x->parent->is_red = false;
                node_y->is_red = false;
                node_x->parent->parent->is_red = true;
                node_x = node_x->parent->parent;
            }
            else{
                if(node_x == node_x->parent->left){
                    node_x = node_x->parent;
                    right_rotation(node_x);
                }
                node_x->parent->is_red = false;
                node_x->parent->parent->is_red = true;
                left_rotation(node_x->parent->parent);
            }
        }
    }
    this->root->is_red = false;
}



void RBT::insert_value(int value){
    Node* new_node = new Node(value);
    new_node->left = nullptr;
    new_node->right = nullptr;

    Node* parent = nullptr;
    Node* current = this->root;

    while(current != nullptr){
        parent = current;
        if(new_node->value < current->value){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }

    new_node->parent = parent;

    if(parent == nullptr){
        root = new_node;
    }
    else if(new_node->value < parent->value){
        parent->left = new_node;
    }
    else{
        parent->right = new_node;
    }

    if(new_node->parent == nullptr){
        new_node->is_red = false;
        return;
    }

    if(new_node->parent->parent == nullptr){
        return;
    }

    fix_insert(new_node);
}


Node* RBT::delete_value_rec(Node* node, int value){
    if(node == nullptr)
        return node;

    if(value < node->value){
        node->left = delete_value_rec(node->left, value);
        return node;
    }
    else if(value > node->value){
        node->right = delete_value_rec(node->right, value);
        return node;
    }

    if(node->left == nullptr){
        Node* temp = node->right;
        delete node;
        return temp;
    }
    else if(node->right == nullptr){
        Node* temp = node->left;
        delete node;
        return temp;
    }

    Node* succParent = node;
    Node* succ = node->right;
    while (succ->left != nullptr){
        succParent = succ;
        succ = succ->left;
    }

    node->value = succ->value;

    if(succParent->left == succ)
        succParent->left = succ->right;
    else
        succParent->right = succ->right;
    
    delete succ;
    return node;
}


void RBT::delete_value(int value){
    delete_value_rec(this->root, value);
}


Node* RBT::min_value_node(Node* node){
    Node* current = node;
    while(current && current->left != nullptr){
        current = current->left;
    }
    return current;
}


int RBT::height_rec(Node* node){
    if(node == nullptr){
        return 0;
    }
    else{
        int height_left = height_rec(node->left);
        int height_right = height_rec(node->right);
 
        if(height_left > height_right){
            return height_left + 1;
        }
        else{
            return height_right + 1;
        }
    }
}


int RBT::height(){
    return height_rec(this->root);
}


/**
 * *************** Splay Tree ***************
 */
ST::ST(){
    this->root = nullptr;
}


void ST::insert_value(int value){
    Node* newNode = new Node(value);
    if(root == nullptr){
        root = newNode;
    } else{
        Node* temp = root;
        Node* parent = nullptr;
        while (temp != nullptr){
            parent = temp;
            if(value < temp->value){
                temp = temp->left;
            } else if(value > temp->value){
                temp = temp->right;
            } else{
                delete newNode;
                splay(temp);
                return;
            }
        }
        newNode->parent = parent;
        if(value < parent->value){
            parent->left = newNode;
        } else{
            parent->right = newNode;
        }
        splay(newNode);
    }
}



void ST::right_rotate(Node* y){
    Node* x = y->left;
    y->left = x->right;
    if(x->right != nullptr){
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == nullptr){
        root = x;
    } else if(y == y->parent->right){
        y->parent->right = x;
    } else{
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void ST::left_rotate(Node* y){
    Node* x = y->right;
    y->right = x->left;
    if(x->left != nullptr){
        x->left->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == nullptr){
        root = x;
    } else if(y == y->parent->left){
        y->parent->left = x;
    } else{
        y->parent->right = x;
    }
    x->left = y;
    y->parent = x;
}


void ST::splay(Node* x){
    while (x->parent != nullptr){
        if(x->parent->parent == nullptr){
            if(x->parent->left == x){
                right_rotate(x->parent);
            } else{
                left_rotate(x->parent);
            }
        }
        else if(x->parent->left == x && x->parent->parent->left == x->parent){
            right_rotate(x->parent->parent);
            right_rotate(x->parent);
        }
        else if(x->parent->right == x && x->parent->parent->right == x->parent){
            left_rotate(x->parent->parent);
            left_rotate(x->parent);
        }
        else if(x->parent->left == x && x->parent->parent->right == x->parent){
            right_rotate(x->parent);
            left_rotate(x->parent);
        }
        else{
            left_rotate(x->parent);
            right_rotate(x->parent);
        }
    }
}


Node* ST::find_node(int value){
    Node* temp = root;
    while (temp != nullptr){
        if(value < temp->value){
            temp = temp->left;
        }
        else if(value > temp->value){
            temp = temp->right;
        }
        else{
            return temp;
        }
    }
    return nullptr;
}


Node* ST::find_max(Node* node){
    while(node->right != nullptr){
        node = node->right;
    }
    return node;
}


void ST::delete_value(int value){
    Node* node = find_node(value);
    if(node == nullptr) return;

    splay(node);

    Node* leftSubtree = root->left;
    Node* rightSubtree = root->right;
    if(leftSubtree) leftSubtree->parent = nullptr;
    if(rightSubtree) rightSubtree->parent = nullptr;

    delete root;

    if(leftSubtree){
        root = leftSubtree;
        Node* maxNode = find_max(root);
        splay(maxNode);
        root->right = rightSubtree;
        if(rightSubtree) rightSubtree->parent = root;
    }
    else{
        root = rightSubtree;
    }
}


int ST::height_rec(Node* node){
    if(node == nullptr){
        return 0;
    }
    else{
        int height_left = height_rec(node->left);
        int height_right = height_rec(node->right);
 
        if(height_left > height_right){
            return height_left + 1;
        }
        else{
            return height_right + 1;
        }
    }
}


int ST::height(){
    return height_rec(this->root);
}