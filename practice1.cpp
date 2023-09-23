#include <iostream>
#include <fstream>
using namespace std;


/////////////////////////////////////////////////////////////////////
struct Footbolist {
    string surname = "";
    string role = "";
    short age = 0;
    short games_count = 0;
    int goal_count = 0;
};
/////////////////////////////////////////////////////////////////////
void PrintFootbolist(Footbolist* footbolist) {
    cout << "surname: " << footbolist->surname << " role: " << footbolist->role << 
        " age: " << footbolist->age << " games count: " << footbolist->games_count << 
        " goal count: " << footbolist->goal_count << endl;
}
/////////////////////////////////////////////////////////////////////
void BestForward(Footbolist* footbolist, int n) {
    Footbolist bestForward = footbolist[0];
    for (int i = 0; i < n; i++) {
        if (1.0f*(footbolist+i)->goal_count / (footbolist+i)->games_count >
            1.0f*(&bestForward)->goal_count / (&bestForward)->games_count) bestForward = footbolist[i];
    }
    PrintFootbolist(&bestForward);
}
bool isLessThanFiveGames(Footbolist* footbolist) {
    return footbolist->games_count < 5;
}
void LessThanFiveGames(Footbolist* footbolist, int n) {
    for (int i = 0; i < n; i++) 
        if (isLessThanFiveGames(footbolist + i)) 
            PrintFootbolist(footbolist + i);
}
/////////////////////////////////////////////////////////////////////
bool SameFootbolist(Footbolist footbolist1, Footbolist footbolist2) {
    return (&footbolist1)->surname == (&footbolist2)->surname &&
        (&footbolist1)->role == (&footbolist2)->role &&
        (&footbolist1)->age == (&footbolist2)->age &&
        (&footbolist1)->games_count == (&footbolist2)->games_count &&
        (&footbolist1)->goal_count == (&footbolist2)->goal_count;
}
int FindFootbolist(Footbolist* footbolist, int n, Footbolist footbolist0) {
    for (int i = 0; i < n; i++) if (SameFootbolist(footbolist[i], footbolist0)) return i;
    return -1;
}
Footbolist SetFootbolist() {
    Footbolist footbolist;
    cout << "Footbolist's surname: ";
    cin >> (&footbolist)->surname;
    cout << "Footbolist's role: ";
    cin >> (&footbolist)->role;
    cout << "Footbolist's age: ";
    cin >> (&footbolist)->age;
    cout << "Footbolist's games count: ";
    cin >> (&footbolist)->games_count;
    cout << "Footbolist's goal count: ";
    cin >> (&footbolist)->goal_count;
    return footbolist;
}
/////////////////////////////////////////////////////////////////////
Footbolist * ImportFootbolists(fstream* FFile, string filename, int * n){
    Footbolist* footbolist;
    (*FFile).open(filename);
    *FFile >> *n;
    footbolist = new Footbolist[*n];
    for (int i = 0; i < *n; i++) {
        *FFile >> (footbolist + i)->surname >> (footbolist + i)->role >>
            (footbolist + i)->age >> (footbolist + i)->games_count >> 
            (footbolist + i)->goal_count;
    }
    (*FFile).close();
    return footbolist;
}
void ExportFootbolists(fstream* FFile, string filename, Footbolist* footbolist, int n) {
    (*FFile).open(filename, ofstream::out | ofstream::trunc);
    (*FFile) << n << " ";
    for (int i = 0; i < n; i++) {
        (*FFile) << (footbolist + i)->surname << " " << (footbolist + i)->role << " " <<
            (footbolist + i)->age << " " << (footbolist + i)->games_count << " " <<
            (footbolist + i)->goal_count;
    }
    (*FFile).close();
}
/////////////////////////////////////////////////////////////////////
Footbolist* AddFootbolist(Footbolist* footbolist, int* n, Footbolist footbolist0) {
    Footbolist* newfootbolist = new Footbolist[((*n)+1)];
    for (int i = 0; i < *n; i++) {
        *(newfootbolist + i) = *(footbolist + i);
    }
    *(newfootbolist + *n) = footbolist0;
    (*n)++;
    return newfootbolist;
}
Footbolist* RemoveFootbolist(Footbolist* footbolist, int* n, Footbolist footbolist0) {
    if (*n > 0) {
        int k = FindFootbolist(footbolist, *n, footbolist0);
        if (k == -1) {
            cout << "Error! Requested footbolist can't be found" << endl;
            return footbolist;
        }
        else {
            int i;
            Footbolist* newfootbolist = new Footbolist[(*n) - 1];
            for (i = 0; i < k; i++) {
                *(newfootbolist + i) = *(footbolist + i);
            }
            for (i = k + 1; i < *n; i++) {
                *(newfootbolist + i - 1) = *(footbolist + i);
            }
            (*n)--;
            return newfootbolist;
        }
    }
    else return footbolist;
}
/////////////////////////////////////////////////////////////////////
void FillFootbolists(Footbolist* footbolist, int n) {
    for (int i = 0; i < n; i++) {
        *(footbolist + i) = SetFootbolist();
    }
}
/////////////////////////////////////////////////////////////////////
void PrintAll(Footbolist* footbolist, int n) {
    cout << n << endl;
    for (int i = 0; i < n; i++) PrintFootbolist(footbolist + i);
}

void Menu(fstream* FFile, string filename) {
    cout << "0 for help" << endl;
    while (true) {
        int command = 0;
        cin >> command;
        if (command == 0) cout << "0 - help\n1 - new array\n2 - continue with existing\n3 - exit" << endl;
        else if (command == 3) {
            break;
        }
        else{
            int n = 0;
            if (command == 1) {
                cout << "Enter count: ";
                cin >> n;
                Footbolist* footbolist = new Footbolist[n];
                FillFootbolists(footbolist, n);
                ExportFootbolists(FFile, filename, footbolist, n);
                delete[] footbolist;
            }
            else if (command == 2) {
                int i = 0;
                Footbolist* footbolist = ImportFootbolists(FFile, filename, &n);
                cout << "0 for help" << endl;
                while (true) {
                    cin >> command;
                    if (command == 0) cout << "0 - help\n1 - add footbolist\n2 - remove footbolist\n3 - find best forward\n4 - show all less than 5 games footbolist\n5 - print all\n6 - go back" << endl;
                    else if (command == 1) footbolist = AddFootbolist(footbolist, &n, SetFootbolist());
                    else if (command == 2) footbolist = RemoveFootbolist(footbolist, &n, SetFootbolist());
                    else if (command == 3) BestForward(footbolist, n);
                    else if (command == 4) LessThanFiveGames(footbolist, n);
                    else if (command == 5) PrintAll(footbolist, n);
                    else if (command == 6) {
                        break;
                    }
                    else cout << "Unknown command" << endl;
                    ExportFootbolists(FFile, filename, footbolist, n);
                }
                delete[] footbolist;
            }
            else cout << "Unknown command" << endl;
        } 
    }
}
int main()
{
    fstream FFile;
    Menu(&FFile, "practice1.txt");
}
