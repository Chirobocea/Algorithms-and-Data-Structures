#include <iostream>

using namespace std;

struct node{
    int info;
    node *left, *right;
};

struct splayTree{
    node* root;

    splayTree(){ root = nullptr;}

    void insert(int x);
    static node* rightRotate(node* x);
    static node* leftRotate(node* x);
    node* splay(node* currentRoot, int info);
    int search(int info);
    void deleteNode(node* currentRoot, int info);

    void RSD();
    void RSD(node* currentRoot, int level, int dir);
};

void splayTree::insert(int x) {
    node* newNode = new node;
    newNode->info = x;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (root == nullptr){
        root = newNode;
        return;
    }

    node* pointer_prev = nullptr;
    node* pointer = root;
    int direction = 0;

    while(pointer != nullptr){
        pointer_prev = pointer;
        if (x <= pointer->info){
            pointer = pointer->left;
            direction = -1;
        }else{
            pointer = pointer->right;
            direction = 1;
        }
    }

    if (direction < 0) {
        pointer_prev->left = newNode;
    } else {
        pointer_prev->right = newNode;
    }

    //TODO add a splay
    root = splay(root, x);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
node* splayTree::rightRotate(node* x) {
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
node* splayTree::leftRotate(node* x) {
    node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// This function brings the info at
// currentRoot if info is present in tree.
// If info is not present, then it
// brings the last accessed item at
// currentRoot. This function modifies the
// tree and returns the new currentRoot
node* splayTree::splay(node* currentRoot, int info) {
    // Base cases: currentRoot is NULL or
    // info is present at currentRoot
    if (currentRoot == nullptr || currentRoot->info == info)
        return currentRoot;

    // info lies in left subtree
    if (currentRoot->info > info)
    {
        // info is not in tree, we are done
        if (currentRoot->left == nullptr) return currentRoot;

        // Zig-Zig (Left Left)
        if (currentRoot->left->info > info)
        {
            // First recursively bring the
            // info as currentRoot of left-left
            currentRoot->left->left = splay(currentRoot->left->left, info);

            // Do first rotation for currentRoot,
            // second rotation is done after else
            currentRoot = rightRotate(currentRoot);
        }
        else if (currentRoot->left->info < info) // Zig-Zag (Left Right)
        {
            // First recursively bring
            // the info as currentRoot of left-right
            currentRoot->left->right = splay(currentRoot->left->right, info);

            // Do first rotation for currentRoot->left
            if (currentRoot->left->right != nullptr)
                currentRoot->left = leftRotate(currentRoot->left);
        }

        // Do second rotation for currentRoot
        return (currentRoot->left == nullptr) ? currentRoot : rightRotate(currentRoot);
    }
    else // info lies in right subtree
    {
        // info is not in tree, we are done
        if (currentRoot->right == nullptr) return currentRoot;

        // Zag-Zig (Right Left)
        if (currentRoot->right->info > info)
        {
            // Bring the info as currentRoot of right-left
            currentRoot->right->left = splay(currentRoot->right->left, info);

            // Do first rotation for currentRoot->right
            if (currentRoot->right->left != nullptr)
                currentRoot->right = rightRotate(currentRoot->right);
        }
        else if (currentRoot->right->info < info)// Zag-Zag (Right Right)
        {
            // Bring the info as currentRoot of
            // right-right and do first rotation
            currentRoot->right->right = splay(currentRoot->right->right, info);
            currentRoot = leftRotate(currentRoot);
        }

        // Do second rotation for currentRoot
        return (currentRoot->right == nullptr) ? currentRoot : leftRotate(currentRoot);
    }
}

// The search function for Splay tree.
// Note that this function returns the
// new root of Splay Tree. If info is
// present in tree then, it is moved to root.
int splayTree::search(int info) {
    root = splay(root, info);
    if(info == root->info)
        cout<<"Valoarea a fost gasita: ";
    else
        cout<<"Valoarea nu exista in arbore!\nCea mai apropiata valoare este: ";
    return root->info;
}

// The delete function for Splay tree. Note that this function
// returns the new currentRoot of Splay Tree after removing the info
void splayTree::deleteNode(node* currentRoot, int info)
{
    node* temp;
    if (!currentRoot)
        return;

    // Splay the given info
    currentRoot = splay(currentRoot, info);

    // If info is not present, then
    // return currentRoot
    if (info != currentRoot->info) {
        root = currentRoot;
        return;
    }

    // If info is present
    // If left child of currentRoot does not exist
    // make currentRoot->right as currentRoot
    if (!currentRoot->left)
    {
        temp = currentRoot;
        currentRoot = currentRoot->right;
    }

        // Else if left child exits
    else
    {
        temp = currentRoot;

        /*Note: Since info == currentRoot->info,
        so after Splay(info, currentRoot->lchild),
        the tree we get will have no right child tree
        and maximum node in left subtree will get splayed*/
        // New currentRoot
        currentRoot = splay(currentRoot->left, info);

        // Make right child of previous currentRoot  as
        // new currentRoot's right child
        currentRoot->right = temp->right;
    }

    // free the previous currentRoot node, that is,
    // the node containing the info
    delete temp;

    // return currentRoot of the new Splay Tree
    root = currentRoot;

}

void splayTree::RSD() {
    RSD(root,0,0);
}

void splayTree::RSD(node* currentRoot, int level, int dir) {
    if (currentRoot != nullptr){
        for (int i=0; i<level; i++) cout<<" ";
        cout << currentRoot->info << (dir == -1 ? "left" : "") << (dir == 1 ? "right" : "") << endl;
        RSD(currentRoot->left, level + 1, -1);
        RSD(currentRoot->right, level + 1, 1);
    }
}

int main(){
    splayTree tree;
    tree.insert(100);
    tree.insert(50);
    tree.insert(200);
    tree.insert(40);
    tree.insert(30);
    tree.insert(20);

    tree.RSD();

    cout<<endl<<tree.search(50)<<endl<<endl;

    tree.RSD();

    cout<<endl;

    tree.RSD();

    tree.deleteNode(tree.root, 30);
    cout<<endl<<"Delet performed"<<endl<<endl;

    tree.RSD();

    return 0;
}