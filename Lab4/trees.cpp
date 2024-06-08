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
	if(root == nullptr){
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
    this->comps_count ++;
    if(value < node->value){
        this->ptr_operations_count += 1;
        node->left = insert_value_rec(node->left, value);
    }
    else if(value > node->value){
        this->ptr_operations_count += 1;
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
        this->comps_count++;
        this->ptr_operations_count ++;
    }
    return current;
}


Node* BST::delete_value_rec(Node* root, int value){
    if(root == nullptr){
        this->comps_count ++;
        return root;
    }
        
    if(value < root->value){
        root->left = delete_value_rec(root->left, value);

        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else if(value > root->value){
        root->right = delete_value_rec(root->right, value);

        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else{
        if(root->left == nullptr){
            Node* temp = root->right;
            free(root);
            
            this->comps_count ++;
            this->ptr_operations_count ++;

            return temp;
        }
        else if(root->right == nullptr){
            Node* temp = root->left;
            free(root);

            this->comps_count ++;
            this->ptr_operations_count ++;

            return temp;
        }

        Node* temp = min_value_node(root->right);
        root->value = temp->value;
        root->right = delete_value_rec(root->right, temp->value);

        this->ptr_operations_count += 3;
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
    this->ptr_operations_count += 2;

    if(child->left != nullptr){
        child->left->parent = node;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    child->parent = node->parent;
    this->ptr_operations_count ++;

    if(node->parent == nullptr){
        this->root = child;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else if(node == node->parent->left){
        node->parent->left = child;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else{
        node->parent->right = child;
        this->ptr_operations_count ++;
    }

    child->left = node;
    node->parent = child;
    this->ptr_operations_count += 2;
}


void RBT::right_rotation(Node* node){
    Node* child = node->left;
    node->left = child->right;
    this->ptr_operations_count += 2;

    if(child->right != nullptr){
        child->right->parent = node;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    child->parent = node->parent;
    this->ptr_operations_count ++;

    if(node->parent == nullptr){
        this->root = child;
        this->ptr_operations_count ++;
        this->comps_count ++;
    }
    else if(node == node->parent->right){
        node->parent->right = child;
        this->ptr_operations_count ++;
        this->comps_count ++;
    }
    else{
        node->parent->left = child;
        this->ptr_operations_count ++;
        this->comps_count ++;
    }

    child->right = node;
    node->parent = child;
    this->ptr_operations_count += 2;
}


void RBT::fix_insert(Node* node_x){
    while(node_x != this->root && node_x->parent->is_red){
        this->comps_count ++;

        if(node_x->parent == node_x->parent->parent->left){
            this->comps_count ++;
            Node* node_y = node_x->parent->parent->right;
            this->ptr_operations_count ++;

            if(node_y && node_y->is_red){
                node_x->parent->is_red = false;
                node_y->is_red = false;
                node_x->parent->parent->is_red = true;
                node_x = node_x->parent->parent;
                this->comps_count ++;
                this->ptr_operations_count ++;
            }
            else{
                if(node_x == node_x->parent->right){
                    node_x = node_x->parent;
                    left_rotation(node_x);
                    this->comps_count ++;
                    this->ptr_operations_count ++;
                }
                node_x->parent->is_red = false;
                node_x->parent->parent->is_red = true;
                right_rotation(node_x->parent->parent);
            }
        }
        else{
            Node* node_y = node_x->parent->parent->left;
            this->ptr_operations_count ++;
            if(node_y && node_y->is_red){
                node_x->parent->is_red = false;
                node_y->is_red = false;
                node_x->parent->parent->is_red = true;
                node_x = node_x->parent->parent;
                this->comps_count ++;
                this->ptr_operations_count ++;
            }
            else{
                if(node_x == node_x->parent->left){
                    node_x = node_x->parent;
                    right_rotation(node_x);
                    this->comps_count ++;
                    this->ptr_operations_count ++;
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
    this->ptr_operations_count ++;

    while(current != nullptr){
        this->comps_count ++;
        parent = current;
        if(new_node->value < current->value){
            current = current->left;
            this->ptr_operations_count ++;
            this->comps_count ++;
        }
        else{
            current = current->right;
            this->ptr_operations_count ++;
        }
    }

    new_node->parent = parent;
    this->ptr_operations_count ++;

    if(parent == nullptr){
        root = new_node;
        this->comps_count ++;
    }
    else if(new_node->value < parent->value){
        parent->left = new_node;
        this->ptr_operations_count ++;
        this->comps_count ++;
    }
    else{
        parent->right = new_node;
        this->ptr_operations_count ++;
    }

    if(new_node->parent == nullptr){
        new_node->is_red = false;
        this->comps_count ++;
        return;
    }

    if(new_node->parent->parent == nullptr){
        this->comps_count ++;
        return;
    }

    fix_insert(new_node);
}


Node* RBT::delete_value_rec(Node* node, int value){
    if(node == nullptr)
    this->comps_count ++;
        return node;

    if(value < node->value){
        node->left = delete_value_rec(node->left, value);
        this->comps_count ++;
        this->ptr_operations_count ++;
        return node;
    }
    else if(value > node->value){
        node->right = delete_value_rec(node->right, value);
        this->comps_count ++;
        this->ptr_operations_count ++;
        return node;
    }

    if(node->left == nullptr){
        Node* temp = node->right;
        delete node;
        this->comps_count ++;
        this->ptr_operations_count ++;
        return temp;
    }
    else if(node->right == nullptr){
        Node* temp = node->left;
        delete node;
        this->comps_count ++;
        this->ptr_operations_count ++;
        return temp;
    }

    Node* succParent = node;
    Node* succ = node->right;
    this->ptr_operations_count += 2;

    while(succ->left != nullptr){
        succParent = succ;
        succ = succ->left;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }

    node->value = succ->value;
    this->ptr_operations_count ++;

    if(succParent->left == succ){
        succParent->left = succ->right;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else{
        succParent->right = succ->right;
        this->ptr_operations_count ++;
    }
    
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
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else{
        Node* temp = root;
        Node* parent = nullptr;
        this->ptr_operations_count += 2;

        while (temp != nullptr){
            this->comps_count ++;
            parent = temp;
            this->ptr_operations_count ++;

            if(value < temp->value){
                temp = temp->left;
                this->comps_count ++;
                this->ptr_operations_count ++;
            }
            else if(value > temp->value){
                temp = temp->right;
                this->comps_count ++;
                this->ptr_operations_count ++;
            }
            else{
                delete newNode;
                splay(temp);
                this->comps_count ++;
                this->ptr_operations_count ++;
                return;
            }
        }

        newNode->parent = parent;
        this->ptr_operations_count ++;

        if(value < parent->value){
            parent->left = newNode;
            this->comps_count ++;
            this->ptr_operations_count ++;
        }
        else{
            parent->right = newNode;
            this->ptr_operations_count ++;
        }
        splay(newNode);
    }
}


void ST::right_rotate(Node* y){
    Node* x = y->left;
    y->left = x->right;
    this->ptr_operations_count += 2;

    if(x->right != nullptr){
        x->right->parent = y;
        this->comps_count++;
        this->ptr_operations_count ++;
    }

    x->parent = y->parent;
    this->ptr_operations_count ++;

    if(y->parent == nullptr){
        root = x;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else if(y == y->parent->right){
        y->parent->right = x;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else{
        y->parent->left = x;
        this->ptr_operations_count ++;
    }

    x->right = y;
    y->parent = x;
    this->ptr_operations_count += 2;
}


void ST::left_rotate(Node* y){
    Node* x = y->right;
    y->right = x->left;
    this->ptr_operations_count += 2;

    if(x->left != nullptr){
        x->left->parent = y;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }

    x->parent = y->parent;
    this->ptr_operations_count ++;

    if(y->parent == nullptr){
        root = x;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else if(y == y->parent->left){
        y->parent->left = x;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    else{
        y->parent->right = x;
        this->ptr_operations_count ++;
    }

    x->left = y;
    y->parent = x;
    this->ptr_operations_count += 2;
}


void ST::splay(Node* x){
    while(x->parent != nullptr){
        if(x->parent->parent == nullptr){
            this->comps_count ++;

            if(x->parent->left == x){
                right_rotate(x->parent);
                this->comps_count ++;
            }
            else{
                left_rotate(x->parent);
            }
        }
        else if(x->parent->left == x && x->parent->parent->left == x->parent){
            this->comps_count ++;
            right_rotate(x->parent->parent);
            right_rotate(x->parent);
        }
        else if(x->parent->right == x && x->parent->parent->right == x->parent){
            this->comps_count ++;
            left_rotate(x->parent->parent);
            left_rotate(x->parent);
        }
        else if(x->parent->left == x && x->parent->parent->right == x->parent){
            this->comps_count ++;
            right_rotate(x->parent);
            left_rotate(x->parent);
        }
        else{
            this->comps_count ++;
            left_rotate(x->parent);
            right_rotate(x->parent);
        }
    }
}


Node* ST::find_node(int value){
    Node* temp = root;
    this->ptr_operations_count ++;

    while(temp != nullptr){
        if(value < temp->value){
            temp = temp->left;
            this->comps_count ++;
            this->ptr_operations_count ++;
        }
        else if(value > temp->value){
            temp = temp->right;
            this->comps_count ++;
            this->ptr_operations_count ++;
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
        this->comps_count ++;
        this->ptr_operations_count ++;
    }
    return node;
}


void ST::delete_value(int value){
    Node* node = find_node(value);
    if(node == nullptr){
        this->comps_count ++;
        return;
    }

    splay(node);

    Node* leftSubtree = root->left;
    Node* rightSubtree = root->right;
    this->ptr_operations_count += 2;

    if(leftSubtree){
        leftSubtree->parent = nullptr;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }

    if(rightSubtree){
        rightSubtree->parent = nullptr;
        this->comps_count ++;
        this->ptr_operations_count ++;
    }

    delete root;

    if(leftSubtree){
        root = leftSubtree;
        Node* maxNode = find_max(root);
        splay(maxNode);
        root->right = rightSubtree;

        this->comps_count ++;
        this->ptr_operations_count ++;

        if(rightSubtree){
            rightSubtree->parent = root;
            this->comps_count ++;
            this->ptr_operations_count ++;
        }
    }
    else{
        root = rightSubtree;
        this->ptr_operations_count ++;
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