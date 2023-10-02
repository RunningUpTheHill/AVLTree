#include "AVLTree.h"

// Helper Functions
int AVLTree::getBalanceFactor(AVLTree::Student* root) {
    // if root is null, return balance factor of 0
    if (root == nullptr) {
        return 0;
    }
    // return balance factor as height of left subtree - height of right subtree
    return ((root->left ? root->left->height : 0) - (root->right ? root->right->height : 0));
}

AVLTree::Student* AVLTree::rotateLeft(AVLTree::Student* root) {
    // rotate the tree if the tree has a right-right rotation
    Student* gcNode = root->right->left;
    Student* newRoot = root->right;
    newRoot->left = root;
    root->right = gcNode;
    // update the height of the nodes within the tree after this rotation
    root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
    newRoot->height = 1 + std::max(newRoot->left ? newRoot->left->height : 0, newRoot->right ? newRoot->right->height : 0);
    return newRoot;
}

AVLTree::Student* AVLTree::rotateRight(AVLTree::Student* root) {
    // rotate the tree if the tree has a left-left rotation
    Student* gcNode = root->left->right;
    Student* newRoot = root->left;
    newRoot->right = root;
    root->left = gcNode;
    // update the height of the nodes within the tree after this rotation
    root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
    newRoot->height = 1 + std::max(newRoot->left ? newRoot->left->height : 0, newRoot->right ? newRoot->right->height : 0);
    return newRoot;
}

AVLTree::Student* AVLTree::rotateLeftRight(AVLTree::Student* root) {
    // rotate the tree if the tree has a left-right rotation
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}

AVLTree::Student* AVLTree::rotateRightLeft(AVLTree::Student* root) {
    // rotate the tree if the tree has a right-left rotation
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}

AVLTree::Student* AVLTree::insertHelper(AVLTree::Student* root, const string& _name, const string& gatorID) {
    // if root is null, create a node as the root
    if (root == nullptr) {
        return new Student(_name, gatorID);
    }
    // if gatorID value of the new student is less than the root student's gatorID, check left branch of the student root node
    else if (stoi(gatorID) < stoi(root->ID)) {
        root->left = insertHelper(root->left, _name, gatorID);
    }
    // if gatorID value of new student is greater than the root student's gatorID, then check right branch
    else if (stoi(gatorID) > stoi(root->ID)) {
        root->right = insertHelper(root->right, _name, gatorID);
    }

    // update height of the node
    root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);

    // if the tree is right heavy
    if (getBalanceFactor(root) <= -2) {
        // if the right subtree is left heavy
        if (getBalanceFactor(root->right) >= 1) {
            return rotateRightLeft(root);
        }
        // right subtree is right heavy
        else {
            return rotateLeft(root);
        }
    }
    // if the tree is left heavy
    else if (getBalanceFactor(root) >= 2) {
        // if the left subtree is right heavy
        if (getBalanceFactor(root->left) <= -1) {
            return rotateLeftRight(root);
        }
        // if the left subtree is left heavy
        else {
            return rotateRight(root);
        }
    }
    return root;
}

string AVLTree::searchIDHelper(AVLTree::Student* root, const string& gatorID) {
    // root is null, so ID is not found
    if (root == nullptr || !regex_match(gatorID, valid_id)) {
        return "unsuccessful";
    }
    // if ID is equal to the ID of the root, return the name of the root
    if (stoi(gatorID) == stoi(root->ID)) {
        return root->name;
    }
        // if ID is greater than ID of the root, traverse the right subtree of the root
    else if (stoi(gatorID) > stoi(root->ID)) {
        return searchIDHelper(root->right, gatorID);
    }
        // if ID is less than ID of the root, traverse the left subtree of the root
    else {
        return searchIDHelper(root->left, gatorID);
    }
}

string AVLTree::InorderHelper(AVLTree::Student* root) {
    string inorder;
    if (root == nullptr) {
        return "";
    }
    string left = InorderHelper(root->left);
    inorder = root->name + ",";
    string right = InorderHelper(root->right);
    // the inorder traversal pattern of left->root->right
    return left + inorder + right;
}

string AVLTree::searchNameHelper(AVLTree::Student *root, const string& _name) {
    string result;
    // if root is null, return empty string
    if (root == nullptr || !regex_match(_name, valid_name)) {
        return "";
    }
    if (root->name == _name) {
        result = root->ID + " ";
    }
    string leftTree = searchNameHelper(root->left, _name);
    string rightTree = searchNameHelper(root->right, _name);
    // returns the search result in preorder traversal pattern, root->left->right
    return result + leftTree + rightTree;
}

// same functionality as InorderHelper but used to sort the ID of the tree in order as a helper function for removeInorder
string AVLTree::IDInorderHelper(AVLTree::Student* root) {
    string inorder;
    if (root == nullptr) {
        return "";
    }
    string left = IDInorderHelper(root->left);
    inorder = root->ID + " ";
    string right = IDInorderHelper(root->right);
    return left + inorder + right;
}

string AVLTree::PreorderHelper(AVLTree::Student* root) {
    string preorder;
    if (root == nullptr) {
        return "";
    }
    preorder = root->name + ",";
    string left = PreorderHelper(root->left);
    string right = PreorderHelper(root->right);
    // preorder traversal pattern of root->left->right
    return preorder + left + right;
}

string AVLTree::PostorderHelper(AVLTree::Student* root) {
    string postorder;
    if (root != nullptr) {
        // create strings in order of left->right->root for postorder traversal pattern
        string left = PostorderHelper(root->left);
        string right = PostorderHelper(root->right);
        postorder = root->name + ",";
        return left + right + postorder;
    }
    else {
        return "";
    }
}

int AVLTree::LevelCountHelper(Student* root) {
    // if root is null, the level is 0
    if (root == nullptr) {
        return 0;
    }
    // level of an AVL tree is the same as its height
    return root->height;
}

AVLTree::Student *AVLTree::inorderSuccessor(AVLTree::Student *root) {
    auto* temp = root;
    // while there exists a left child of the node, traverse left
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    // return the leftmost node
    return temp;
}

AVLTree::Student* AVLTree::removeIDHelper(AVLTree::Student* root, const string& gatorID) {
    // root is null, no removal needed
    if (root == nullptr) {
        return nullptr;
    }
    // ID is less than ID of the root, recursively check the removal ID on the left subtree
    if (stoi(gatorID) < stoi(root->ID)) {
        root->left = removeIDHelper(root->left, gatorID);
    }
        // ID is greater than ID of the root, recursively check the removal ID on the right subtree
    else if (stoi(gatorID) > stoi(root->ID)) {
        root->right = removeIDHelper(root->right, gatorID);
    }
    else {
        // if root node has no children, set root node to nullptr
        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
        }
            // if root node has one child, set the root node's properties equal to its child's properties and delete the child
        else if ((root->left == nullptr && root->right != nullptr) || (root->left != nullptr && root->right == nullptr)) {
            auto* temp = root->left ? root->left : root->right;
            *root = *temp;
            delete temp;
        }
            // root node has two children
        else {
            // find the inorder successor of the node to be deleted
            auto* successor = inorderSuccessor(root->right);
            // change the root node's name and ID to be the inorder successor's ID and name
            root->name = successor->name;
            root->ID = successor->ID;
            // recursively check and delete inorder successor node
            root->right = removeIDHelper(root->right, successor->ID);
        }
    }

    // the node has been removed, return the new root node
    if (root == nullptr) {
        return root;
    }

    // updating height of the nodes
    root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);

    if (getBalanceFactor(root) <= -2) {
        if (getBalanceFactor(root->right) >= 1) {
            return rotateRightLeft(root);
        }
        else {
            return rotateLeft(root);
        }
    }
    else if (getBalanceFactor(root) >= 2) {
        if (getBalanceFactor(root->left) <= -1) {
            return rotateLeftRight(root);
        }
        else {
            return rotateRight(root);
        }
    }
    return root;
}

string AVLTree::removeInorderHelper(AVLTree::Student* root, int n) {
    vector<string> ID;
    string gatorID;
    stringstream s(IDInorderHelper(root));
    // stores every ID in order into the vector
    while (s >> gatorID) {
        ID.push_back(gatorID);
    }
    // if the vector size is less than the N+1 position to be removed, the Nth position is out of range
    if (ID.size() < n+1) {
        return "unsuccessful";
    }
        // return the ID at Nth position to be removed
    else {
        return ID.at(n);
    }
}


// Actual member functions accessible to public
string AVLTree::insert(const string& _name, const string& gatorID, const string& method) {
    // if ID is not found, insert this new node
    if (searchIDHelper(this->rootNode, gatorID) == "unsuccessful" && regex_match(_name, valid_name) && regex_match(gatorID, valid_id) && method == "insert") {
        this->rootNode = insertHelper(this->rootNode, _name, gatorID);
        return "successful";
    }
    // if ID is found, ID is not unique, don't insert
    else {
        return "unsuccessful";
    }
}

string AVLTree::searchID(const string& gatorID, const string& method) {
    if (method == "search") {
        return searchIDHelper(this->rootNode, gatorID);
    }
    else {
        return "unsuccessful";
    }
}

string AVLTree::searchName(const string& _name, const string& method) {
    string nameList = searchNameHelper(this->rootNode, _name);
    // if the returned string from the helper function is empty, the name is not in the tree
    if (nameList.empty() || method != "search") {
        return "unsuccessful";
    }
    // creates a string stream object that contains the list of names and prints out each following by a new line in preorder pattern
    else {
        stringstream s(nameList);
        string final;
        string name;
        while (s >> name) {
            final += name + "\n";
        }
        return final;
    }
}

string AVLTree::printInorder() {
    stringstream s(InorderHelper(this->rootNode));
    string final;
    string name;
    // stores a line of names in order separated by ", "
    while (getline(s, name, ',')) {
        final += name + ", ";
    }
    // gets rid of the last ", " in the string
    return final.substr(0, final.length()-2);
}

string AVLTree::printPreorder() {
    stringstream s(PreorderHelper(this->rootNode));
    string final;
    string name;
    // stores a line of names in preorder separated by ", "
    while (getline(s, name, ',')) {
        final += name + ", ";
    }
    // gets rid of the last ", " in the string
    return final.substr(0, final.length()-2);
}

string AVLTree::printPostorder() {
    stringstream s(PostorderHelper(this->rootNode));
    string final;
    string name;
    // stores a line of names in postorder pattern separated by ", "
    while (getline(s, name, ',')) {
        final += name + ", ";
    }
    // gets rid of the last ", " in the string
    return final.substr(0, final.length()-2);
}

int AVLTree::printLevelCount() {
    return LevelCountHelper(this->rootNode);
}

string AVLTree::remove(const string& gatorID, const string& method) {
    // if ID is not found by the helper function, the node does not exist
    if (searchIDHelper(this->rootNode, gatorID) == "unsuccessful" && method == "remove") {
        return "unsuccessful";
    }
    // set the current root node equal to the new root node after removal of the node containing the ID
    else {
        this->rootNode = removeIDHelper(this->rootNode, gatorID);
        return "successful";
    }
}

string AVLTree::removeInorder(int n, const string& method) {
    // stores result from the helper function
    string gatorID = removeInorderHelper(this->rootNode, n);
    if (gatorID == "unsuccessful" || method != "removeInorder") {
        return "unsuccessful";
    }
    // call the removeID helper function
    else {
        this->rootNode = removeIDHelper(this->rootNode, gatorID);
        return "successful";
    }
}
