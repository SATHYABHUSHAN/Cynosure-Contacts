#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Contact {
public:
    std::string name;
    std::string phone;

    Contact(const std::string& n, const std::string& p) : name(n), phone(p) {}

    void display() const {
        std::cout << "Name: " << name << "\nPhone: " << phone << "\n";
    }
};

class AddressBook {
private:
    std::vector<Contact> contacts;
    std::string filename;

public:
    AddressBook(const std::string& file) : filename(file) {
        loadContacts();
    }

    void addContact(const std::string& name, const std::string& phone) {
        Contact newContact(name, phone);
        contacts.push_back(newContact);
        saveContacts();
    }

    void listContacts() const {
        for (const Contact& contact : contacts) {
            contact.display();
            std::cout << "-------------------\n";
        }
    }

    void saveContacts() {
        std::ofstream file(filename);

        if (file.is_open()) {
            for (const Contact& contact : contacts) {
                file << contact.name << "," << contact.phone << "\n";
            }
            file.close();
        } else {
            std::cerr << "Error: Unable to save contacts.\n";
        }
    }

    void loadContacts() {
        std::ifstream file(filename);

        if (file.is_open()) {
            contacts.clear();
            std::string line;
            while (getline(file, line)) {
                size_t commaPos = line.find(',');
                if (commaPos != std::string::npos) {
                    std::string name = line.substr(0, commaPos);
                    std::string phone = line.substr(commaPos + 1);
                    contacts.push_back(Contact(name, phone));
                }
            }
            file.close();
        } else {
            std::cerr << "Error: Unable to load contacts.\n";
        }
    }
};

int main() {
    AddressBook addressBook("contacts.txt");

    while (true) {
        std::cout << "Address Book Menu:\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. List Contacts\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, phone;
                std::cin.ignore(); // Clear the newline character from the buffer
                std::cout << "Enter name: ";
                std::getline(std::cin, name);
                std::cout << "Enter phone number: ";
                std::getline(std::cin, phone);
                addressBook.addContact(name, phone);
                break;
            }
            case 2:
                addressBook.listContacts();
                break;
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
