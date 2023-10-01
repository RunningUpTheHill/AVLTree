#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class AVLTree {
private:
    // base class to encapsulate data for student information, stored privately in the tree class
    struct Student {
        string name;
        string ID;
        int height;
        Student* parent;
        Student* left;
        Student* right;
        Student(string _name, string data) : name(std::move(_name)), ID(std::move(data)), height(1), parent(nullptr), left(nullptr), right(nullptr) {}
    };
    Student* rootNode = nullptr;

    // functions to balance the tree
    static int getBalanceFactor(Student* root);
    static Student* rotateLeft(Student* root);
    static Student* rotateRight(Student* root);
    static Student* rotateLeftRight(Student* root);
    static Student* rotateRightLeft(Student* root);

    //helper methods for the public functions, so that client wouldn't be able to see private information from the class in the main interface
    Student* insertHelper(Student* root, const string& _name, const string& gatorID);
    Student* inorderSuccessor(Student* root);
    Student* removeIDHelper(Student* root, const string& gatorID);
    string searchIDHelper(Student* root, const string& gatorID);
    string searchNameHelper(Student* root, const string& _name);
    string InorderHelper(Student* root);
    string IDInorderHelper(Student* root);
    string PreorderHelper(Student* root);
    string PostorderHelper(Student* root);
    static int LevelCountHelper(Student* root);
    string removeInorderHelper(Student* root, int n);

public:
    vector<string> validMethods {"insert", "remove", "search", "printInorder", "printPreorder", "printPostorder", "printLevelCount", "removeInorder"};
    // public methods to be used by the client in main interface
    void insert(const string& _name, const string& gatorID);
    void remove(const string& gatorID);
    void searchID(const string& gatorID);
    void searchName(const string& _name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int n);
};


