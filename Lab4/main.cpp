#include "trees.h"
#include <iostream>
int main(){
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

    // std::cout << "delete 16\n";
    // rbt_tree->delete_value(16);
    // print_tree(rbt_tree->root);

    ST* splay_tree = new ST();
    splay_tree->insert_value(15);
    splay_tree->insert_value(10);
	splay_tree->insert_value(17);
    splay_tree->insert_value(7);
    // splay_tree->insert_value(16);
    // splay_tree->insert_value(30);
    // splay_tree->insert_value(25);
    // splay_tree->insert_value(40);
    // splay_tree->insert_value(60);
    print_tree(splay_tree->root);
    // std::cout << splay_tree->root->value << std::endl;

    // std::cout << "delete 16\n";
    splay_tree->delete_value(15);
    splay_tree->delete_value(10);
    // splay_tree->delete_value(17);
    // splay_tree->delete_value(7);
    print_tree(splay_tree->root);

    // splay_tree->insert_value(15);
    // splay_tree->insert_value(10);
	// splay_tree->insert_value(17);
    // splay_tree->insert_value(7);
    // print_tree(splay_tree->root);
	return 0;
}