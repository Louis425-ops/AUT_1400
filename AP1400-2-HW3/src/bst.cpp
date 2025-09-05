#include "bst.h"
#include <iostream>

Node::Node(int value, Node* left, Node* right): value(value), left(left), right(right){

}

Node::Node(): value(0), left(nullptr), right(nullptr){

}

Node::Node(const Node& node): value(node->value), left(node->left), right(node->right){

}



Node*& BST::get_root(){
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func){

}

/*
size_t BST::length(Node*& root){
    Node*& root = get_root();
    if(root == nullptr) return 0;
    // if(root->left == nullptr && root->right == nullptr){
        // return 1
    // }
    Node*& left = root->left;

    return 1 + length(root->left) + length(root->right);
}
*/

size_t BST::length(){
    
}
