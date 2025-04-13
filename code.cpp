#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Date {
    int month;
    int day;
    int year;
};

struct Account {
    int number;
    string name;
    int acct_no;
    float mobile_no;
    string street;
    string city;
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    Date lastpayment;
};

Account customer;
int tl, sl, ts;

void input();
void writefile();
void search();
void output();
void mainMenu();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    char ch;
    int n;
    cout << "   CUSTOMER BILLING SYSTEM:\n\n";
    cout << "===============================\n";
    cout << "1: Add account\n";
    cout << "2: Search account\n";
    cout << "3: Exit\n";
    cout << "===============================\n";
    cout << "Select an option: ";

    cin >> ch;
    switch (ch) {
        case '1':
            cout << "\nHow many customer accounts? ";
            cin >> n;
            for (int i = 0; i < n; ++i) {
                input();
                if (customer.payment > 0)
                    customer.acct_type = (customer.payment < 0.1 * customer.oldbalance) ? 'O' : 'D';
                else
                    customer.acct_type = (customer.oldbalance > 0) ? 'D' : 'C';
                customer.newbalance = customer.oldbalance - customer.payment;
                writefile();
            }
            mainMenu();
            break;
        case '2':
            search();
            mainMenu();
            break;
        case '3':
            cout << "\nA PROJECT BY Aahna, Akshat & Utkarsh\n";
            exit(0);
        default:
            cout << "\nInvalid option! Try again.\n";
            mainMenu();
    }
}

void input() {
    fstream file("bidur.dat", ios::in | ios::binary);
    file.seekg(0, ios::end);
    tl = file.tellg();
    sl = sizeof(Account);
    ts = tl / sl;
    file.seekg((ts - 1) * sl, ios::beg);
    file.read((char*)&customer, sizeof(customer));
    customer.number++;
    file.close();

    cout << "\nCustomer No: " << customer.number;
    cout << "\nAccount number: "; cin >> customer.acct_no;
    cout << "Name: "; cin >> customer.name;
    cout << "Mobile No: "; cin >> customer.mobile_no;
    cout << "Street: "; cin >> customer.street;
    cout << "City: "; cin >> customer.city;
    cout << "Old Balance: "; cin >> customer.oldbalance;
    cout << "Current Payment: "; cin >> customer.payment;
    cout << "Payment date (mm dd yyyy): ";
    cin >> customer.lastpayment.month >> customer.lastpayment.day >> customer.lastpayment.year;
}

void writefile() {
    ofstream file("bidur.dat", ios::binary | ios::app);
    file.write((char*)&customer, sizeof(customer));
    file.close();
}

void search() {
    fstream file("bidur.dat", ios::in | ios::binary);
    char ch;
    cout << "\nSearch by:\n1. Customer number\n2. Customer name\nChoice: ";
    cin >> ch;
    switch (ch) {
        case '1': {
            file.seekg(0, ios::end);
            tl = file.tellg();
            sl = sizeof(Account);
            ts = tl / sl;
            int n;
            do {
                cout << "\nEnter customer number: ";
                cin >> n;
                if (n <= 0 || n > ts) {
                    cout << "Invalid number!\n";
                } else {
                    file.seekg((n - 1) * sl, ios::beg);
                    file.read((char*)&customer, sizeof(customer));
                    output();
                }
                cout << "\nSearch again? (y/n): ";
                cin >> ch;
            } while (ch == 'y');
            break;
        }
        case '2': {
            string name;
            int found = 0;
            cout << "\nEnter customer name: ";
            cin >> name;
            file.seekg(0, ios::beg);
            while (file.read((char*)&customer, sizeof(customer))) {
                if (customer.name == name) {
                    output();
                    found = 1;
                    break;
                }
            }
            if (!found) {
                cout << "\nCustomer not found!\n";
            }
            break;
        }
        default:
            cout << "\nInvalid choice!\n";
    }
    file.close();
}

void output() {
    cout << fixed << setprecision(2);
    cout << "\nCustomer No: " << customer.number;
    cout << "\nName: " << customer.name;
    cout << "\nMobile No: " << customer.mobile_no;
    cout << "\nAccount No: " << customer.acct_no;
    cout << "\nStreet: " << customer.street;
    cout << "\nCity: " << customer.city;
    cout << "\nOld Balance: " << customer.oldbalance;
    cout << "\nPayment: " << customer.payment;
    cout << "\nNew Balance: " << customer.newbalance;
    cout << "\nPayment Date: " << customer.lastpayment.month << "/"
         << customer.lastpayment.day << "/" << customer.lastpayment.year;
    cout << "\nAccount Status: ";
    switch (customer.acct_type) {
        case 'C': cout << "CURRENT\n"; break;
        case 'O': cout << "OVERDUE\n"; break;
        case 'D': cout << "DELINQUENT\n"; break;
        default:  cout << "ERROR\n";
    }
}
