#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#define private public
#include "../src/AVLTree.h"

TEST_CASE("Command Errors", "[command]") {
    AVLTree tree;
    // incorrect command due to name including numbers "A11y"
    string fullCommand1 = "insert \"A11y\" 45679999";
    string command = fullCommand1.substr(0, 6);
    string NAME = fullCommand1.substr(8, 4);
    string ID = fullCommand1.substr(14, fullCommand1.length()-14);
    REQUIRE(tree.insert(NAME, ID, command) == "unsuccessful");

    // incorrect command due to gator ID not having 8 numbers
    string fullCommand2 = "insert \"Aye\" 457999";
    command = fullCommand2.substr(0, 6);
    NAME = fullCommand2.substr(8, 3);
    ID = fullCommand2.substr(13, fullCommand2.length()-13);
    REQUIRE(tree.insert(NAME, ID, command) == "unsuccessful");

    // incorrect command due to insert being spelled incorrectly
    string fullCommand3 = "inset \"Aye\" 45799329";
    command = fullCommand3.substr(0, 6);
    NAME = fullCommand3.substr(7, 3);
    ID = fullCommand3.substr(12, fullCommand3.length()-12);
    REQUIRE(tree.insert(NAME, ID, command) == "unsuccessful");

    // incorrect command due to removeInorder spelled incorrectly
    string fullCommand4 = "removeIorder 2";
    command = fullCommand4.substr(0, 13);
    int count = stoi(fullCommand4.substr( 13, fullCommand4.length()-13));
    REQUIRE(tree.removeInorder(count, command) == "unsuccessful");

    // incorrectly command due to search NAME, NAME containing numbers
    string fullCommand5 = "search \"H3110\"";
    command = fullCommand5.substr(0, 6);
    NAME = fullCommand5.substr(8, 5);
    REQUIRE(tree.searchName(NAME, command) == "unsuccessful");
}

TEST_CASE("Edge Cases", "[Edge]") {
    AVLTree tree;
    // edge case 1, inserting not unique gatorID
    tree.insert("Brandon", "12345678", "insert");
    REQUIRE(tree.insert("Brand", "12345678", "insert") == "unsuccessful");

    // edge case 2, removing node/ID that does not exist
    tree.insert("Brandon", "22345678", "insert");
    REQUIRE(tree.remove("12345677", "remove") == "unsuccessful");

    // edge case 3, removing (N+1)th Gator ID in order where N+1 is greater than the number of nodes in tree
    tree.insert("Brad", "23433343", "insert");
    REQUIRE(tree.removeInorder(3, "removeInorder") == "unsuccessful");
}

TEST_CASE("Rotations", "[Rotate]") {
    AVLTree tree;
    tree.insert("Brad", "00000003", "insert");
    tree.insert("Pitt", "00000002", "insert");
    tree.rootNode->left->left = new AVLTree::Student("BRUH", "00000001");
    // preorder traversal of a left heavy tree
    REQUIRE(tree.printPreorder() == "Brad, Pitt, BRUH");

    // rotate right
    tree.rootNode = AVLTree::rotateRight(tree.rootNode);
    REQUIRE(tree.printPreorder() == "Pitt, BRUH, Brad");

    tree.remove("00000001", "remove");
    tree.rootNode->right->right = new AVLTree::Student("BRUH", "00000005");
    // preorder traversal of a right heavy tree
    REQUIRE(tree.printPreorder() == "Pitt, Brad, BRUH");

    // rotate left
    tree.rootNode = AVLTree::rotateLeft(tree.rootNode);
    REQUIRE(tree.printPreorder() == "Brad, Pitt, BRUH");

    tree.remove("00000002", "remove");
    tree.rootNode->right->left = new AVLTree::Student("Pitt", "00000004");
    // postorder traversal of a right heavy tree with the right subtree being left heavy
    REQUIRE(tree.printPostorder() == "Pitt, BRUH, Brad");

    // rotate right-left
    tree.rootNode = AVLTree::rotateRightLeft(tree.rootNode);
    REQUIRE(tree.printPostorder() == "Brad, BRUH, Pitt");

    tree.remove("00000003", "remove");
    tree.remove("00000005", "remove");
    tree.insert("Brad", "00000001", "insert");
    tree.rootNode->left->right = new AVLTree::Student("BRUH", "00000002");
    // preorder traversal of a left heavy tree with the left subtree being right heavy
    REQUIRE(tree.printPreorder() == "Pitt, Brad, BRUH");

    // rotate left-right
    tree.rootNode = AVLTree::rotateLeftRight(tree.rootNode);
    REQUIRE(tree.printPreorder() == "BRUH, Brad, Pitt");
}

TEST_CASE("Removal", "[Remove]") {
    AVLTree tree;
    tree.insert("Brad", "00000006", "insert");
    tree.insert("Pitt", "00000002", "insert");
    tree.insert("Wolf oof", "00000009", "insert");
    tree.insert("Hey", "00000001", "insert");
    REQUIRE(tree.printInorder() == "Hey, Pitt, Brad, Wolf oof");

    // removal of a node with no child
    tree.remove("00000001", "remove");
    // after removing 1 from the tree, the in order traversal should be 2, 6, 9
    REQUIRE(tree.printInorder() == "Pitt, Brad, Wolf oof");

    tree.insert("Hey", "00000001", "insert");

    // removal of a node with 1 child
    tree.remove("00000002", "remove");
    // after removing 2 from the tree, the in order traversal should be 1, 6, 9
    REQUIRE(tree.printInorder() == "Hey, Brad, Wolf oof");

    // removal of a node with 2 children
    tree.remove("00000006", "remove");
    // after removing 6 from the tree, the in order traversal should be 2, 9
    REQUIRE(tree.printInorder() == "Hey, Wolf oof");
}

TEST_CASE("insert/removal/inorder", "[random]") {
    AVLTree tree;
    regex valid_id = regex("^[0-9]{8}$");
    string ID;
    // create a vector of expected output and actual output
    vector<string> expectedOutput, actualOutput;
    // iterate 1000 times
    for (int i = 0; i < 1000; i++) {
        // create a random gator ID
        int randomInput = 10000000 + rand() % 99999999;
        // cast random Gator ID to string
        string random = to_string(randomInput);
        // check if the random gator ID is a valid id and whether it is already in the expected output vector
        if (std::find(expectedOutput.begin(), expectedOutput.end(), random) == expectedOutput.end() && regex_match(random, valid_id)) {
            expectedOutput.push_back(random);
            tree.insert("rando", random, "insert");
        }
    }
    // push back the in order traversal of the tree into the actual output
    stringstream s(tree.IDInorderHelper(tree.rootNode));
    while (s >> ID) {
        actualOutput.push_back(ID);
    }

    // check if the expected output size is equal to actual output size
    REQUIRE(expectedOutput.size() == actualOutput.size());
    // sort the list of expected output and check if it matches the in order traversal of the actual output
    std::sort(expectedOutput.begin(), expectedOutput.end());
    REQUIRE(expectedOutput == actualOutput);
}