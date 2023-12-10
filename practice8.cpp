#include <iostream>
using namespace std;

struct ae_tree {        //arithmetic expression tree
    char symbol;
    ae_tree* left = NULL;
    ae_tree* right = NULL;
};
typedef ae_tree* ptree_ae;

struct t_tree {
    int info;
    t_tree* left = NULL;
    t_tree* right = NULL;
};
typedef t_tree* ptree;

//////////////////////////////////////////////////

ptree_ae FormAETree(string ae, int* i = NULL) {
    if (i == NULL) {
        i = new int;
        *i = 0;
    }
    ptree_ae tae = new ae_tree;
    tae->symbol = ae[*i];
    if (ae[*i] == '+' || ae[*i] == '-' || ae[*i] == '*' || ae[*i] == '/') {
        (*i)++;
        tae->left = FormAETree(ae, i);
        tae->right = FormAETree(ae, i);
        (*i)--;
    }
    (*i)++;
    return tae;
}

void displayTLR_AE(ptree_ae ae_tree)
{
    if (ae_tree != NULL)
    {
        cout << ae_tree->symbol;
        displayTLR_AE(ae_tree->left);
        displayTLR_AE(ae_tree->right);
    }
}
void displayLTR_AE(ptree_ae ae_tree)
{
    if (ae_tree != NULL)
    {
        if (ae_tree->symbol == '*' || ae_tree->symbol == '/') {
            if (ae_tree->left->symbol == '+' || ae_tree->left->symbol == '-'
                || ae_tree->left->symbol == '*' || ae_tree->left->symbol == '/') {
                cout << '(';
                displayLTR_AE(ae_tree->left);
                cout << ')';
            }
            else displayLTR_AE(ae_tree->left);
        }
        else displayLTR_AE(ae_tree->left);
        cout << ae_tree->symbol;
        if (ae_tree->symbol == '*' || ae_tree->symbol == '/') {
            if (ae_tree->right->symbol == '+' || ae_tree->right->symbol == '-'
                || ae_tree->right->symbol == '*' || ae_tree->right->symbol == '/') {
                cout << '(';
                displayLTR_AE(ae_tree->right);
                cout << ')';
            }
            else displayLTR_AE(ae_tree->right);
        }
        else displayLTR_AE(ae_tree->right);
    }
}

//////////////////////////////////////////////////

int main()
{
    string str = "";
    cout << "Enter arithmetic expression using prefix entry: ";
    cin >> str;
    ptree_ae ae_tree = FormAETree(str);
    displayTLR_AE(ae_tree);
    cout << endl;
    displayLTR_AE(ae_tree);
    cout << endl;
}
