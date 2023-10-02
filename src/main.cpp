#include "AVLTree.h"
#include <regex>

int main(){
    AVLTree tree;
    // creates a regex object that checks for spaces
    regex space = regex("\\s");

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

        // check if the command is spelled correctly or matches one of the valid commands in vector
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
                cout << tree.insert(NAME, ID, "insert") << endl;
            }
            else if (command == "remove") {
                getline(s, ID);
                ID = regex_replace(ID, space, "");
                cout << tree.remove(ID, "remove") << endl;
            }
            else if (command == "search") {
                // check if the original user input contained the " delimiter

                //if no " delimiter, searching for ID
                if (find(line.begin(), line.end(), '"') == line.end()) {
                    s >> ID;
                    cout << tree.searchID(ID, "search") << endl;
                }
                // " delimiter is found, search for name
                else {
                    getline(s, command, '"');
                    getline(s, NAME, '"');
                    cout << tree.searchName(NAME, "search");
                }
            }
            else if (command == "removeInorder") {
                string N;
                s >> N;
                cout << tree.removeInorder(stoi(N), "removeInorder") << endl;
            }
            else if (command == "printInorder") {
                cout << tree.printInorder() << endl;
            }
            else if (command == "printPreorder") {
                cout << tree.printPreorder() << endl;
            }
            else if (command == "printPostorder") {
                cout << tree.printPostorder() << endl;
            }
            else {
                cout << tree.printLevelCount() << endl;
            }
        }
    }
	return 0;
}
