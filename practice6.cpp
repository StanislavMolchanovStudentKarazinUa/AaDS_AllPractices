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

int main(){

}
