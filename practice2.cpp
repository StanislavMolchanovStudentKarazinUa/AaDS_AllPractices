#include <iostream>
using namespace std;

enum Role {
    Goalkeeper,
    Defender,
    Midfielder,
    Forward
};
Role SetRole() {
    string a = "";
    while (true) {
        cout << "Footbolist's role: ";
        cin >> a;
        if (a == "Goalkeeper") return Goalkeeper;
        else if (a == "Defender") return Defender;
        else if (a == "Midfielder") return Midfielder;
        else if (a == "Forward") return Forward;
        else cout << "WRONG!!!\n";
    }
}
Role SetRole(int a) {
    switch (a) {
    case 0: return Goalkeeper;
    case 1: return Defender;
    case 2: return Midfielder;
    case 3: return Forward;
    default:
        cout << "Error!\n";
        return Forward;
    }
}
void OutputRole(Role role) {
    switch (role) {
    case 0: cout << "Goalkeeper"; break;
    case 1: cout << "Defender"; break;
    case 2: cout << "Midfielder"; break;
    default: cout << "Forward"; break;
    }
}

struct Footbolist {
    string surname = "";
    Role role = Forward;
    short age = 0;
    short games_count = 0;
    int goal_count = 0;
};
Footbolist SetFootbolist() {
    Footbolist footbolist;
    cout << "\nFootbolist's surname: ";
    cin >> (&footbolist)->surname;
    (&footbolist)->role = SetRole();
    cout << "Footbolist's age: ";
    cin >> (&footbolist)->age;
    cout << "Footbolist's games count: ";
    cin >> (&footbolist)->games_count;
    cout << "Footbolist's goal count: ";
    cin >> (&footbolist)->goal_count;
    return footbolist;
}

struct tnode {
    Footbolist footbolist;
    tnode* next = NULL;
};
typedef tnode* pnode;

/////////////////////////////////////////////////////////////////////

pnode formLIFO_1(int n) {
    pnode head = NULL, cur;
    Footbolist footbolist;
    while (n > 0) {
        footbolist = SetFootbolist();
        n--;
        cur = new tnode;
        cur->footbolist = footbolist;
        cur->next = head;
        head = cur;
    }
    return head;
}
void formLIFO_2(int n, pnode * p) {
    pnode head = NULL, cur;
    Footbolist footbolist;
    while (n > 0) {
        footbolist = SetFootbolist();
        n--;
        cur = new tnode;
        cur->footbolist = footbolist;
        cur->next = head;
        head = cur;
    }
    *p = head;
}

/////////////////////////////////////////////////////////////////////

pnode formFIFO_1(int n) {
    pnode head = NULL; 
    pnode * cur = &head;
    Footbolist footbolist;
    while (n > 0) {
        footbolist = SetFootbolist();
        n--;
        *cur = new tnode;
        (*cur)->footbolist = footbolist;
        cur = &(*cur)->next;
    }
    return head;
}
void formFIFO_2(int n, pnode * p) {
    pnode head = NULL;
    pnode* cur = &head;
    Footbolist footbolist;
    while (n > 0) {
        footbolist = SetFootbolist();
        n--;
        *cur = new tnode;
        (*cur)->footbolist = footbolist;
        cur = &(*cur)->next;
    }
    *p = head;
}

/////////////////////////////////////////////////////////////////////

void free(pnode p) {
    if (p != NULL) {
        free(p->next);
        delete p;
    }
}

/////////////////////////////////////////////////////////////////////

void PrintFootbolist(pnode footbolist) {
    cout << "surname: " << footbolist->footbolist.surname 
            << " role: ";
    OutputRole(footbolist->footbolist.role);
    cout << " age: "
        << footbolist->footbolist.age << " games count: " 
        << footbolist->footbolist.games_count <<
        " goal count: " << footbolist->footbolist.goal_count << endl;
}
void PrintAll(pnode footbolist) {
    PrintFootbolist(footbolist);
    if (footbolist->next != NULL) PrintAll(footbolist->next);
}

/////////////////////////////////////////////////////////////////////

pnode BestForward(pnode footbolist, pnode bestForward) {
    if (1.0f*footbolist->footbolist.goal_count / footbolist->footbolist.games_count >
       1.0f*bestForward->footbolist.goal_count / bestForward->footbolist.games_count) 
        bestForward = footbolist;
    if (footbolist->next == NULL) return bestForward;
    else return BestForward(footbolist->next, bestForward);
}
bool isLessThanFiveGames(pnode footbolist) {
    return footbolist->footbolist.games_count < 5;
}
void LessThanFiveGames(pnode footbolist) {
    if (isLessThanFiveGames(footbolist))
        PrintFootbolist(footbolist);
    if (footbolist->next != NULL) LessThanFiveGames(footbolist->next);
}

/////////////////////////////////////////////////////////////////////

int main()
{
    int n = 0;
    pnode footbolist = NULL;
    int command = 0;
    while (true) {
        cout << "0 for help" << endl;
        cin >> command;
        if (command == 0) cout << "0 - help\n1 - new list\n2 - continue with existing\n3 - exit" << endl;
        else if (command == 3) {
            break;
        }
        else {
            if (command == 1) {
                cout << "Enter count: ";
                cin >> n;
                if (n < 1) {
                    cout << "n must be bigger than 0" << endl;
                    continue;
                }
                cout << "1 - LIFO_1; 2 - LIFO_2; 3 - FIFO_1; 4 - FIFO_2" << endl;
                cin >> command;
                if (command == 1) footbolist = formLIFO_1(n);
                else if (command == 2) formLIFO_2(n, &footbolist);
                else if (command == 3) footbolist = formFIFO_1(n);
                else if (command == 4) formFIFO_2(n, &footbolist);
                else cout << "Unknown command" << endl;
            }
            else if (command == 2) {
                if (footbolist == NULL) {
                    cout << "n must be bigger than 0" << endl;
                    continue;
                }
                int i = 0;
                cout << "0 for help" << endl;
                while (true) {
                    cin >> command;
                    if (command == 0) cout << "0 - help\n1 - find best forward\n2 - show all less than 5 games footbolist\n3 - print all\n4 - go back" << endl;
                    else if (command == 1) PrintFootbolist(BestForward(footbolist, footbolist));
                    else if (command == 2) LessThanFiveGames(footbolist);
                    else if (command == 3) PrintAll(footbolist);
                    else if (command == 4) break;
                    else cout << "Unknown command" << endl;
                }
                
            }
            else cout << "Unknown command" << endl;
        }
    }
    free(footbolist);
}
