#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct todoItem {
    int id = 0; string content = ""; bool checked = 0;
};

void backButton(char& choice, int &i) {
    cout << endl << "<--[b]ack: "; cin >> choice;
    while (choice != 'b') {
        cout << "Push [b] to go back" << endl << "<--[b]ack: "; cin >> choice;
    }
    i = 1;
    system("cls");
}

void addButton(vector<todoItem>& item, char& choice, int &i) {
    if (i == 2) i = 1;
    if (choice == 'a') system("cls");
    todoItem itemAdd; int n = item.size();
    itemAdd.id = item.size() + 1;
    cout << "Add new content: "; cin.ignore(); getline(cin, itemAdd.content);
    item.push_back(itemAdd);
    system("cls");
    for (int i = 0; i < n; i++) {
        cout << "[";
        if (item[i].checked == 1) cout << "X";
        else cout << " ";
        cout << "] " << item[i].id << "." << item[i].content << endl;
    }
}

void showList(vector<todoItem>& item, char &choice, int& i) {
    system("cls");
    int n = item.size();
    if (n == 0) {
        cout << "Your todo list is empty!" << endl;
        addButton(item, choice, i); showList(item, choice, i); backButton(choice, i);
    }
    else {
        for (int i = 0; i < n; i++) {
            cout << "[";
            if (item[i].checked == 1) cout << "X"; else cout << " ";
            cout << "] " << item[i].id << "." << item[i].content << endl;
        }
    }
}

int cantFindId(int id, vector<todoItem>& item) {
    while (id > item.size() || id <= 0) {
        cout << "ID " << id << " don't exist! Please choose again: "; cin >> id;
    }
    return id;
}

void deleteButton(vector<todoItem>& item, char& choice, int& i) {
    system("cls");
    todoItem itemAdd; int id;
    if (choice != 'b') {
        showList(item, choice, i);
        cout << "ID: "; cin >> id;
        id = cantFindId(id, item);
        item.erase(item.begin() + id - 1);
        for (int i = id - 1; i < item.size(); i++) {
            item[i].id -= 1;
        }
        system("cls");
        showList(item, choice, i);
        if (choice != 'b') backButton(choice, i);
    }
}


int main()
{
    bool stop = 0; char choice; int i = 1; vector<todoItem>item;
    while (!stop) {
        cout << "Todo List Maker - 0.0.1" << endl << endl << "Choose your action" << endl << "[s]how Todo list" << endl << "[a]dd a new Todo" << endl;
        cout << "[c]omplete/[u]ndo a Todo" << endl << "[d]elete a Todo" << endl << "[q]uit" << endl << "Choice: ";
        if (i == 1) cin >> choice;
        switch (choice) {
        case 's':
            i = 2;
            showList(item, choice, i);
            if (choice != 'b') backButton(choice, i); break;
        case 'a':
            addButton(item, choice, i); showList(item, choice, i); backButton(choice, i); break;
        case 'c':
            showList(item, choice, i);
            if (choice != 'b') {
                int id;
                cout << "ID: "; cin >> id;
                id = cantFindId(id, item);
                item[id - 1].checked = 1;
                showList(item, choice, i); backButton(choice, i);
            }
            break;
        case 'u':
            showList(item, choice, i);
            if (choice != 'b') {
                int id;
                cout << "ID: "; cin >> id;
                id = cantFindId(id, item);
                item[id - 1].checked = 0;
                showList(item, choice, i); backButton(choice, i);
            }
            break;
        case 'd':
            showList(item, choice, i); deleteButton(item, choice, i);
            break;
        case 'q':
            stop = 1; break;
        default:
            i = 2;
            system("cls");
            cout << "Wrong button! Please go back and choose again!" << endl;
            backButton(choice, i);
        }
    }
    return 0;
}

