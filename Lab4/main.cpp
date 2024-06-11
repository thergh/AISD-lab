#include "trees.h"
#include <iostream>


int main(){
    ST* bst_tree = new ST();
    bst_tree->insert_value(15);
    bst_tree->insert_value(10);
	bst_tree->insert_value(17);
    bst_tree->insert_value(7);
    bst_tree->insert_value(16);
    bst_tree->insert_value(30);
    bst_tree->insert_value(25);
    bst_tree->insert_value(40);
    bst_tree->insert_value(60);
    print_tree(bst_tree->root);
    std::cout << "comps: " << bst_tree->comps_count << std::endl;
    std::cout << "ptr: " << bst_tree->ptr_operations_count << std::endl;
    
    std::cout << "height: " << bst_tree->height() << std::endl;

    bst_tree->delete_value(2121235);
    print_tree(bst_tree->root);
    std::cout << "comps: " << bst_tree->comps_count << std::endl;
    std::cout << "ptr: " << bst_tree->ptr_operations_count << std::endl;
    std::cout << "height: " << bst_tree->height() << std::endl;

    // RBT* rbt_tree = new RBT();
    // rbt_tree->insert_value(10);
    // rbt_tree->insert_value(18);
	// rbt_tree->insert_value(7);
    // rbt_tree->insert_value(15);
    // rbt_tree->insert_value(16);
    // rbt_tree->insert_value(30);
    // rbt_tree->insert_value(25);
    // rbt_tree->insert_value(40);
    // rbt_tree->insert_value(60);
    // print_tree(rbt_tree->root);
    // std::cout << "comps: " << rbt_tree->comps_count << std::endl;
    // std::cout << "ptr: " << rbt_tree->ptr_operations_count << std::endl;

    // rbt_tree->delete_value(10);
    // rbt_tree->delete_value(18);
    // print_tree(rbt_tree->root);
    // std::cout << "comps: " << rbt_tree->comps_count << std::endl;
    // std::cout << "ptr: " << rbt_tree->ptr_operations_count << std::endl;


    // ST* splay_tree = new ST();
    // splay_tree->insert_value(15);
    // splay_tree->insert_value(10);
	// splay_tree->insert_value(17);
    // splay_tree->insert_value(7);
    // splay_tree->insert_value(16);
    // splay_tree->insert_value(30);
    // splay_tree->insert_value(25);
    // splay_tree->insert_value(40);
    // splay_tree->insert_value(60);
    // print_tree(splay_tree->root);
    // std::cout << "comps: " << splay_tree->comps_count << std::endl;
    // std::cout << "ptr: " << splay_tree->ptr_operations_count << std::endl;

}