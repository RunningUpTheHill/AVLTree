#include "AVLTree.h"

int AVLTree::getBalanceFactor(AVLTree::Student* root) {
    if (root == nullptr) {
        return 0;
    }
    return ((root->left ? root->left->height : 0) - (root->right ? root->right->height : 0));
}

AVLTree::Student* AVLTree::rotateLeft(AVLTree::Student* root) {
    // rotate the tree if the tree has a right-right rotation
    Student* gcNode = root->right->left;
    Student* newRoot = root->right;
    newRoot->left = root;
    root->right = gcNode;
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
        auto* temp = insertHelper(root->left, _name, gatorID);
        root->left = temp;
        temp->parent = root;
    }
    // if gatorID value of new student is greater than the root student's gatorID, then check right branch
    else if (stoi(gatorID) > stoi(root->ID)) {
        auto* temp = insertHelper(root->right, _name, gatorID);
        root->right = temp;
        temp->parent = root;
    }

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

void AVLTree::insert(const string& _name, const string& gatorID) {
    if (searchIDHelper(this->rootNode, gatorID) == "unsuccessful") {
        this->rootNode = insertHelper(this->rootNode, _name, gatorID);
        cout << "successful" << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

string AVLTree::searchIDHelper(AVLTree::Student* root, const string& gatorID) {
    if (root == nullptr) {
        return "unsuccessful";
    }
    if (stoi(gatorID) == stoi(root->ID)) {
        return root->name;
    }
    else if (stoi(gatorID) > stoi(root->ID)) {
        return searchIDHelper(root->right, gatorID);
    }
    else {
        return searchIDHelper(root->left, gatorID);
    }
}

void AVLTree::searchID(const string& gatorID) {
    string result = searchIDHelper(this->rootNode, gatorID);
    cout << result << endl;
}

string AVLTree::searchNameHelper(AVLTree::Student *root, const string& _name) {
    string result;
    if (root == nullptr) {
        return "";
    }
    if (root->name == _name) {
        result = root->ID + " ";
    }
    string leftTree = searchNameHelper(root->left, _name);
    string rightTree = searchNameHelper(root->right, _name);
    return result + leftTree + rightTree;
}

void AVLTree::searchName(const string& _name) {
    string nameList = searchNameHelper(this->rootNode, _name);
    if (nameList.empty()) {
        cout << "unsuccessful" << endl;
    }
    else {
        stringstream s(nameList);
        string name;
        while (s >> name) {
            cout << name << endl;
        }
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
    return left + inorder + right;
}

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

void AVLTree::printInorder() {
    stringstream s(InorderHelper(this->rootNode));
    string final;
    string name;
    while (getline(s, name, ',')) {
        final += name + ", ";
    }
    cout << final.substr(0, final.length()-2) << endl;
}

string AVLTree::PreorderHelper(AVLTree::Student* root) {
    string preorder;
    if (root == nullptr) {
        return "";
    }
    preorder = root->name + ",";
    string left = PreorderHelper(root->left);
    string right = PreorderHelper(root->right);
    return preorder + left + right;
}

void AVLTree::printPreorder() {
    stringstream s(PreorderHelper(this->rootNode));
    string final;
    string name;
    while (getline(s, name, ',')) {
        final += name + ", ";
    }
    cout << final.substr(0, final.length()-2) << endl;
}

string AVLTree::PostorderHelper(AVLTree::Student* root) {
    string postorder;
    if (root != nullptr) {
        string left = PostorderHelper(root->left);
        string right = PostorderHelper(root->right);
        postorder = root->name + ",";
        return left + right + postorder;
    }
    else {
        return "";
    }
}

void AVLTree::printPostorder() {
    stringstream s(PostorderHelper(this->rootNode));
    string final;
    string name;
    while (getline(s, name, ',')) {
        final += name + ", ";
    }
    cout << final.substr(0, final.length()-2) << endl;
}

int AVLTree::LevelCountHelper(Student* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

void AVLTree::printLevelCount() {
    cout << LevelCountHelper(this->rootNode) << endl;
}

AVLTree::Student *AVLTree::inorderSuccessor(AVLTree::Student *root) {
    auto* temp = root;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return temp;
}

AVLTree::Student* AVLTree::removeIDHelper(AVLTree::Student* root, const string& gatorID) {
    if (root == nullptr) {
        return nullptr;
    }
    if (stoi(gatorID) < stoi(root->ID)) {
        root->left = removeIDHelper(root->left, gatorID);
    }
    else if (stoi(gatorID) > stoi(root->ID)) {
        root->right = removeIDHelper(root->right, gatorID);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
        }
        else if ((root->left == nullptr && root->right != nullptr) || (root->left != nullptr && root->right == nullptr)) {
            auto* temp = root->left ? root->left : root->right;
            *root = *temp;
            delete temp;
        }
        else {
            auto* successor = inorderSuccessor(root->right);
            root->name = successor->name;
            root->ID = successor->ID;
            root->right = removeIDHelper(root->right, successor->ID);
        }
    }

    if (root == nullptr) {
        return root;
    }

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

void AVLTree::remove(const string& gatorID) {
    if (searchIDHelper(this->rootNode, gatorID) == "unsuccessful") {
        cout << "unsuccessful" << endl;
    }
    else {
        cout << "successful" << endl;
        this->rootNode = removeIDHelper(this->rootNode, gatorID);
    }
}

string AVLTree::removeInorderHelper(AVLTree::Student* root, int n) {
    vector<string> ID;
    string gatorID;
    stringstream s(IDInorderHelper(root));
    while (s >> gatorID) {
        ID.push_back(gatorID);
    }
    if (ID.size() < n+1) {
        return "unsuccessful";
    }
    else {
        return ID.at(n);
    }
}

void AVLTree::removeInorder(int n) {
    string gatorID = removeInorderHelper(this->rootNode, n);
    if (gatorID == "unsuccessful") {
        cout << "unsuccessful" << endl;
    }
    else {
        this->rootNode = removeIDHelper(this->rootNode, gatorID);
        cout << "successful" << endl;
    }
}
