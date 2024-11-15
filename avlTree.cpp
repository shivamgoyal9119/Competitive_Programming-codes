#include<iostream>
using namespace std;

class avl_tree_node{
    public:
    int data, height;
    avl_tree_node *left, *right;

    avl_tree_node(int data){
        this->data = data;
        height = 1;
        left = right = NULL;
    }
};

int getHeight(avl_tree_node* root){
    if(root == NULL) return 0;
    int l = 0, r = 0;
    if(root->left != NULL) l = root->left->height;
    if(root->right != NULL) r = root->right->height;

    return 1 + max(l, r);
}

avl_tree_node* make_ll(avl_tree_node* root){
    avl_tree_node* root_left = root->left, *root_left_right = root_left->right;

    root_left->right = root;
    root->left = root_left_right;
    root->height = 1 + max(getHeight(root->right), getHeight(root_left_right));
    root_left->height = 1 + max(getHeight(root_left->left), getHeight(root_left->right));

    return root_left;
}

avl_tree_node* make_rr(avl_tree_node* root){
    avl_tree_node* root_right = root->right, *root_right_left = root_right->left;

    root_right->left = root;
    root->right = root_right_left;
    root->height = 1 + max(getHeight(root->left), getHeight(root_right_left));
    root_right->height = 1 + max(getHeight(root_right->left), getHeight(root_right->right));

    return root_right;
}

avl_tree_node* insert(avl_tree_node* root, int d){
    if(root == NULL) return new avl_tree_node(d);

    if(root->data < d) root->right = insert(root->right, d);
    else root->left = insert(root->left, d);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // * Balancing

    int height_diff = getHeight(root->left) - getHeight(root->right);
    
    if(height_diff > 1){
        if(root->left->data > d) // LL Rotation
            return make_ll(root);
        else{ // LR Rotation
            avl_tree_node* left_subtree = make_rr(root->left);
            root->left = left_subtree;
            return make_ll(root);
        }     
    }else if(height_diff < -1){
        if(root->right->data < d) // RR Rotation
            return make_rr(root);
        else{ // RL Rotation
            avl_tree_node* right_subtree = make_ll(root->right);
            root->right = right_subtree;
            return make_rr(root);
        }
    }

    return root;
}

void get_preorder_traversal(avl_tree_node *root){
    if(root == NULL) return;

    get_preorder_traversal(root->left);
    cout<<root->data<<"  ";
    get_preorder_traversal(root->right);
}

int main(){

    // AVL Tree
    // -> Duplicate elements are not allowed, because its also a advanced version of BST.

    // Insertion

    avl_tree_node *root = new avl_tree_node(21);
    root = insert(root, 26);
    root = insert(root, 30);
    root = insert(root, 9);
    root = insert(root, 4);
    root = insert(root, 14);
    root = insert(root, 28);

    get_preorder_traversal(root);





    return 0;
}