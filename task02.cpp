
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

vector<Contact> contacts;
const string FILE_NAME = "contacts.txt";

// Load contacts from file
void loadContacts() {
    contacts.clear();
    ifstream file(FILE_NAME);
    Contact c;

    while (getline(file, c.name) &&
        getline(file, c.phone) &&
        getline(file, c.email)) {
        contacts.push_back(c);
    }

    file.close();
}

// Save contacts to file
void saveContacts() {
    ofstream file(FILE_NAME);

    for (const Contact& c : contacts) {
        file << c.name << '\n';
        file << c.phone << '\n';
        file << c.email << '\n';
    }

    file.close();
}

// Add a new contact
void addContact() {
    Contact c;

    cout << "Enter name: ";
    getline(cin, c.name);

    cout << "Enter phone number: ";
    getline(cin, c.phone);

    cout << "Enter email: ";
    getline(cin, c.email);

    contacts.push_back(c);
    saveContacts();

    cout << "Contact added successfully!\n";
}

// View all contacts
void viewContacts() {
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }

    for (int i = 0; i < (int)contacts.size(); i++) {
        cout << "\nContact " << i + 1 << '\n';
        cout << "Name: " << contacts[i].name << '\n';
        cout << "Phone: " << contacts[i].phone << '\n';
        cout << "Email: " << contacts[i].email << '\n';
    }
}

// Search contact by name
void searchContact() {
    string searchName;
    cout << "Enter name to search: ";
    getline(cin, searchName);

    bool found = false;

    for (const Contact& c : contacts) {
        if (c.name == searchName) {
            cout << "\nName: " << c.name << '\n';
            cout << "Phone: " << c.phone << '\n';
            cout << "Email: " << c.email << '\n';
            found = true;
        }
    }

    if (!found) {
        cout << "Contact not found.\n";
    }
}

// Update a contact by name
void updateContact() {
    string searchName;
    cout << "Enter name to update: ";
    getline(cin, searchName);

    for (Contact& c : contacts) {
        if (c.name == searchName) {
            cout << "Enter new name: ";
            getline(cin, c.name);

            cout << "Enter new phone number: ";
            getline(cin, c.phone);

            cout << "Enter new email: ";
            getline(cin, c.email);

            saveContacts();
            cout << "Contact updated successfully!\n";
            return;
        }
    }

    cout << "Contact not found.\n";
}

// Delete a contact by name
void deleteContact() {
    string searchName;
    cout << "Enter name to delete: ";
    getline(cin, searchName);

    for (int i = 0; i < (int)contacts.size(); i++) {
        if (contacts[i].name == searchName) {
            contacts.erase(contacts.begin() + i);
            saveContacts();

            cout << "Contact deleted successfully!\n";
            return;
        }
    }

    cout << "Contact not found.\n";
}

int main() {
    loadContacts();

    int choice;

    do {
        cout << "\n===== CONTACT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            addContact();
            break;

        case 2:
            viewContacts();
            break;

        case 3:
            searchContact();
            break;

        case 4:
            updateContact();
            break;

        case 5:
            deleteContact();
            break;

        case 6:
            cout << "Thank you for using Contact Management System!\n";
            break;

        default:
            cout << "Invalid choice. Please select 1 to 6.\n";
        }

    } while (choice != 6);

    return 0;
}
