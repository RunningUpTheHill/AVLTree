#include "AVLTree.h"
#include <regex>

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){
    AVLTree tree;
    regex space = regex("\\s");
    regex name = regex("^[A-Za-z\\s]+$");
    regex id = regex("^[0-9]{8}$");

    string count;
    getline(cin, count);

    for (int i = 0; i < stoi(count); i++) {
        string line;
        getline(cin, line);

        string command;
        string NAME;
        string ID;
        istringstream s(line);
        s >> command;

        auto it = find(tree.validMethods.begin(), tree.validMethods.end(), command);

        if (it == tree.validMethods.end()) {
            cout << "unsuccessful" << endl;
            continue;
        }
        else {
            if (command == "insert") {
                getline(s, command, '"');
                getline(s, NAME, '"');
                getline(s, ID);
                ID = regex_replace(ID, space, "");
                if (!regex_match(NAME, name) || !regex_match(ID, id)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                else {
                    tree.insert(NAME, ID);
                }
            }
            else if (command == "remove") {
                getline(s, ID);
                ID = regex_replace(ID, space, "");
                if (!regex_match(ID, id)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                else {
                    tree.remove(ID);
                }
            }
            else if (command == "search") {
                if (find(line.begin(), line.end(), '"') == line.end()) {
                    s >> ID;
                    if (!regex_match(ID, id)) {
                        cout << "unsuccessful" << endl;
                        continue;
                    }
                    else {
                        tree.searchID(ID);
                    }
                }
                else {
                    getline(s, command, '"');
                    getline(s, NAME, '"');
                    if (!regex_match(NAME, name)) {
                        cout << "unsuccessful" << endl;
                        continue;
                    }
                    else {
                        tree.searchName(NAME);
                    }
                }
            }
            else if (command == "removeInorder") {
                string N;
                s >> N;
                tree.removeInorder(stoi(N));
            }
            else if (command == "printInorder") {
                tree.printInorder();
            }
            else if (command == "printPreorder") {
                tree.printPreorder();
            }
            else if (command == "printPostorder") {
                tree.printPostorder();
            }
            else {
                tree.printLevelCount();
            }
        }
    }

	return 0;
}

