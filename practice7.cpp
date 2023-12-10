#include <iostream>
using namespace std;

enum Group {
    A,
    B,
    C,
    D
};
Group SetGroup(int a) {
    switch (a) {
    case 0: return A;
    case 1: return B;
    case 2: return C;
    case 3: return D;
    default:return A;
    }
}
void OutputGroup(Group group) {
    switch (group) {
    case 0: cout << "A"; break;
    case 1: cout << "B"; break;
    case 2: cout << "C"; break;
    default:cout << "D"; break;
    }
}
struct Student {
    string name = "";
    Group group = SetGroup(0);
    double successRate = 0.0;
};
Student SetStudent() {
    Student student;
    cout << "\Student's name: ";
    cin >> (&student)->name;
    string a = "";
    while (a == "") {
        cout << "Students's group: ";
        cin >> a;
        if (a == "A") (&student)->group = SetGroup(0);
        else if (a == "B") (&student)->group = SetGroup(1);
        else if (a == "C") (&student)->group = SetGroup(2);
        else if (a == "D") (&student)->group = SetGroup(3);
        else {
            cout << "WRONG!!!\n";
            a = "";
        }
    }
    cout << "Student's successRate: ";
    cin >> (&student)->successRate;
    return student;
}
void OutputStudent(Student student) {
    cout << "\Student's name: " << (&student)->name << endl;
    cout << "Students's group: ";
    OutputGroup((&student)->group);
    cout << "\nStudent's successRate: " << (&student)->successRate << endl;
}
bool StudentsAreEqual(Student s1, Student s2) {
    if (
        s1.group == s2.group &&
        s1.name == s2.name &&
        s1.successRate == s2.successRate)
        return true;
    else return false;
}
struct t_tree {
    Student student;
    t_tree* left = NULL;
    t_tree* right = NULL;
};
typedef t_tree* ptree;

//////////////////////////////////////////////////

void insertInSearchTree(ptree* tree, Student student)
{
    if (*tree == NULL) {
        *tree = new t_tree;
        (*tree)->student = student;
    }
    else {
        if (student.successRate > (*tree)->student.successRate)
            insertInSearchTree(&((*tree)->left), student);
        else
            insertInSearchTree(&((*tree)->right), student);
    } 
}

bool deleteFromSearchTree(ptree* tree, Student student)
{
    if (*tree == NULL) return false;
    else if (StudentsAreEqual((*tree)->student, student)) {
        if ((*tree)->left == NULL) {
            if ((*tree)->right == NULL) {
                delete* tree;
                *tree = NULL;
                return true;
            }
            else {
                ptree tree_ = (*tree)->right;
                (*tree)->student = (*tree)->right->student;
                (*tree)->left = (*tree)->right->left;
                (*tree)->right = (*tree)->right->right;
                delete tree_;
                return true;
            }
        }
        else {
            if ((*tree)->right == NULL) {
                ptree tree_ = (*tree)->left;
                (*tree)->student = tree_->student;
                (*tree)->left = tree_->left;
                (*tree)->right = tree_->right;
                delete tree_;
                return true;
            }
            else {
                ptree * tree_ = &(*tree)->left;
                while ((*tree_)->right != NULL) tree_ = &(*tree_)->right;
                (*tree)->student = (*tree_)->student;
                return deleteFromSearchTree(tree_, (*tree_)->student);
            }
        }
    }
    else {
        if ((*tree)->left == NULL && (*tree)->right == NULL) return false;
        else {
            if (deleteFromSearchTree(&((*tree)->left), student)) return true;
            else if (deleteFromSearchTree(&((*tree)->right), student)) return true;
            else return false;
        }
    }
}

ptree formIdeallyBalanced(int n)
{
    ptree tree = NULL;
    if (n <= 0) return NULL;
    for (int i = 1; i <= n; i++) {
        cout << "Student number " << i << ":\n";
        insertInSearchTree(&tree, SetStudent());
    }
    return tree;
}

void freeTree(ptree t) {
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        delete t;
    }
}

void displayLTR(ptree tree)
{
    if (tree != NULL)
    {
        displayLTR(tree->left);
        OutputStudent(tree->student);
        cout << endl;
        displayLTR(tree->right);
    }
}

void displayStudentsLowerGradeThan(ptree tree, double successRate) { //a function that displays information about students who have a score lower than specified in the parameter
    if (tree != NULL)
    {
        if (tree->student.successRate < successRate) {
            displayStudentsLowerGradeThan(tree->left, successRate);
            OutputStudent(tree->student);
            cout << endl;
            displayLTR(tree->right);
        }
        else {
            displayStudentsLowerGradeThan(tree->right, successRate);
        }
    }
}


//////////////////////////////////////////////////

int main()
{
    int n;
    cout << "Enter count: ";
    cin >> n;
    ptree tree = formIdeallyBalanced(n);
    int command = 0;
    cout << "Enter command (1 - insert, 2 - delete, 3 - printall, 4 - printstudentslowerthan, any other key - exit): ";
    while (true) {
        cin >> command;
        if (command == 1) {
            insertInSearchTree(&tree, SetStudent());
            n++;
        }
        else if (command == 2) {
            if (n <= 0) {
                cout << "Number of students is too low!" << endl;
                continue;
            }
            Student s = SetStudent();
            if (deleteFromSearchTree(&tree, s)) {
                cout << "Successfully deleted" << endl;
                n--;
            }
            else cout << "Student was not found" << endl;
        }
        else if (command == 3) {
            if (n <= 0) {
                cout << "Number of students is too low!" << endl;
                continue;
            }
            displayLTR(tree);
        }
        else if (command == 4) {
            if (n <= 0) {
                cout << "Number of students is too low!" << endl;
                continue;
            }
            cout << "Input required grade: ";
            double successRate = 0.0;
            cin >> successRate;
            displayStudentsLowerGradeThan(tree, successRate);
        }
        else break;
        cout << "Enter command (1 - insert, 2 - delete, 3 - printall, 4 - printstudentslowerthan, any other key - exit): ";
    }
    freeTree(tree);
}
