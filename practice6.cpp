#include <iostream>
#include <string>
using namespace std;

struct t_tree {
    int info;
    t_tree* left;
    t_tree* right;
};
typedef t_tree* ptree;

ptree formTree()
{
    ptree t;
    string info;
    cin >> info;
    if (info == "x")
        return NULL;
    t = new t_tree;
    t->info = stoi(info);
    t->left = formTree();
    t->right = formTree();
    return t;
}
void freeTree(ptree t) {
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        delete t;
    }
}
void displayTLR(ptree tree)             //прямий обхід
{
    if (tree != NULL)
    {
        cout << tree->info << " ";
        displayTLR(tree->left);
        displayTLR(tree->right);
    }
}
void displayLTR(ptree tree)             //симетричний обхід
{
    if (tree != NULL)
    {
        displayLTR(tree->left);
        cout << tree->info << " ";
        displayLTR(tree->right);
    }
}
void displayLRT(ptree tree)             //зворотній обхід
{
    if (tree != NULL)
    {
        displayLRT(tree->left);
        displayLRT(tree->right);
        cout << tree->info << " ";
    }
}
int amountOfEqual(ptree tree, int info) {
    if (tree == NULL) return 0;
    else if (tree->info == info)
        return amountOfEqual(tree->left, info) +
        amountOfEqual(tree->right, info) + 1;
    else return amountOfEqual(tree->left, info) +
        amountOfEqual(tree->right, info);
}

int main(){
    ptree t = NULL;
    string command;
    int info;
    while (true) {
        cout << "0 for help" << endl;
        cin >> command;
        if (command == "0") cout << "0 - help\n1 - new tree\n2 - continue with existing\nx - exit" << endl;
        else if (command == "1") {
            freeTree(t);
            cout << "Imput elements (x - end of branch): ";
            t = formTree();
        }
        else if (command == "2") {
            while (true) {
                cout << "0 for help" << endl;
                cin >> command;
                if (command == "0") cout << "0 - help\n1 - display tree TopLeftRight\n2 - display tree LeftTopRight\n3 - display tree LeftRightTop\n4 - amount of equal to definite number\n5 - go back\nx - exit" << endl;
                else if (command == "1") { displayTLR(t); cout << endl; }
                else if (command == "2") { displayLTR(t); cout << endl; }
                else if (command == "3") { displayLRT(t); cout << endl; }
                else if (command == "4") {
                    cout << "Enter the number to compare: ";
                    cin >> info;
                    cout << amountOfEqual(t, info) << endl;
                }
                else if (command == "5") break;
                else if (command != "x") cout << "Unknown command" << endl;
                if (command == "x") break;
            }
        }
        else if (command != "x") cout << "Unknown command" << endl;
        if (command == "x") break;
    }
    freeTree(t);
}
