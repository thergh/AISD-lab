#ifndef TREES_H
#define TREES_H


/**
 * Represents a node of a binary tree
 */
class Node{
public:
	int value;
    bool is_red;
	Node* left;
    Node* right;
    Node* parent;
    Node* root;

	Node(int value, bool is_red = true, Node* parent = nullptr, Node* root = nullptr);
};


/**
 * Prints a binary tree
 */
void print_tree(Node* root);


/**
 * Represents a binary search tree
 */
class BST{
public:
    Node* root;
    int comps_count = 0;
    int ptr_operations_count = 0;

    BST();
    void insert_value(int value);
    void delete_value(int value);
    int height();

private:
    Node* insert_value_rec(Node* current, int value);
    Node* delete_value_rec(Node* current, int value);
    Node* min_value_node(Node* node);
    int height_rec(Node* node);
};


/**
 * Represents a red black tree
 */
class RBT{
public:
    Node* root;
    int comps_count;
    int ptr_operations_count;
    
    RBT();
    void insert_value(int value);
    void delete_value(int value);
    int height();
    
private:
    Node* min_value_node(Node* node);
    Node* delete_value_rec(Node* node, int value);
    void fix_insert(Node* k);
    void right_rotation(Node* node);
    void left_rotation(Node* node);
    int height_rec(Node* node);
};


/**
 * Represents a binary search tree
 */
class ST{
public:
    Node* root;
    int comps_count;
    int ptr_operations_count;
    
    ST();
    void insert_value(int value);
    void delete_value(int value);
    int height();
    
private:
    void splay(Node* node);
    void right_rotate(Node* node);
    void left_rotate(Node* node);
    Node* find_max(Node* node);
    Node* find_node(int value);
    int height_rec(Node* node);
};


#endif
