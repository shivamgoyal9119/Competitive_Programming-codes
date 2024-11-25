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

/* ************************************************************************************* */

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

    cout<<root->data<<"  ";
    get_preorder_traversal(root->left);
    get_preorder_traversal(root->right);
}

/* ************************************************************************************* */

int get_min_ele(avl_tree_node* root){
    if(root == NULL) return INT_MAX;
    int ans = root->data;
    ans = min(ans, get_min_ele(root->left));
    ans = min(ans, get_min_ele(root->right));
    return ans;
}

avl_tree_node* get_balance_node(avl_tree_node* root){
    int h = getHeight(root->left), h2 = getHeight(root->right);
    if(h-h2 >= -1 && h-h2 <= 1) return root;

    if(h > h2){ // LL or LR
        int l_h = getHeight(root->left->left), l_h2 = getHeight(root->left->right);
        if(l_h >= l_h2) // LL
            return make_ll(root);
        else{ // LR
            avl_tree_node* left_sub_tree = make_rr(root->left);
            root->left = left_sub_tree;
            // root->height = 1 + max(getHeight(root->left), getHeight(root->right));
            return make_ll(root);
        }
    }else{ // RR or RL
        int r_h = getHeight(root->right->left), r_h2 = getHeight(root->right->right);
        if(r_h > r_h2){ // RL
            avl_tree_node* right_sub_tree = make_ll(root->right);
            root->right = right_sub_tree;
            // root->height = 1 + max(getHeight(root->left), getHeight(root->right));
            return make_rr(root);
        }else // RR
            return make_rr(root);
    }
}

avl_tree_node* delete_(avl_tree_node* root, int t){
    if(root->data == t){
        if(root->left == NULL && root->right == NULL) return NULL;
        else if(root->left == NULL && root->right != NULL) return root->right;
        else if(root->left != NULL && root->right == NULL) return root->left;

        int min_ele = get_min_ele(root->right);
        root->data = min_ele;
        root->right = delete_(root->right, min_ele);
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return get_balance_node(root);
    }

    if(root->data > t){
        root->left = delete_(root->left, t);
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return get_balance_node(root);
    }else{
        root->right = delete_(root->right, t);
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return get_balance_node(root);
    }
}

/* ************************************************************************************* */

int main(){

    // AVL Tree
    // -> Duplicate elements are not allowed, because its also a advanced version of BST.

    // --- Fully Tested ---

    // Insertion
    avl_tree_node *root = new avl_tree_node(21);
    root = insert(root, 26);
    root = insert(root, 30);
    root = insert(root, 9);
    root = insert(root, 4);
    root = insert(root, 14);
    root = insert(root, 28);

    get_preorder_traversal(root);
    cout<<endl;

    // Deletion
    root = delete_(root, 21);
    get_preorder_traversal(root);


    return 0;
}
