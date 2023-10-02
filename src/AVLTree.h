#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <regex>
using namespace std;

class AVLTree {
private:
    // base class to encapsulate data for student information, stored privately in the tree class
    struct Student {
        string name;
        string ID;
        int height;
        Student* left;
        Student* right;
        Student(string _name, string data) : name(std::move(_name)), ID(std::move(data)), height(1), left(nullptr), right(nullptr) {}
    };
    Student* rootNode = nullptr;

    // creates a regex object that checks for characters beginning to end containing A-Z, a-z, and spaces
    regex valid_name = regex("^[A-Za-z\\s]+$");
    // creates a regex object that checks for numbers 0-9 that has a length of 8
    regex valid_id = regex("^[0-9]{8}$");

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
    // vector of valid commands that calls the public functions
    vector<string> validMethods {"insert", "remove", "search", "printInorder", "printPreorder", "printPostorder", "printLevelCount", "removeInorder"};
    // public methods to be used by the client in main interface
    string insert(const string& _name, const string& gatorID, const string& method);
    string remove(const string& gatorID, const string& method);
    string searchID(const string& gatorID, const string& method);
    string searchName(const string& _name, const string& method);
    string printInorder();
    string printPreorder();
    string printPostorder();
    int printLevelCount();
    string removeInorder(int n, const string& method);
};


