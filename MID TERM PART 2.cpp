#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Item {
private:
    int id;
    string name;
    int quantity;
    double price;

public:
    Item(int id, string name, int quantity, double price) :
        id(id), name(name), quantity(quantity), price(price) {}

    int getId() { return id; }
    string getName() { return name; }
    int getQuantity() { return quantity; }
    double getPrice() { return price; }

    void setName(string name) { this->name = name; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setPrice(double price) { this->price = price; }

    void display() {
        cout << "ID:         " << id << endl;
        cout << "Name:       " << name << endl;
        cout << "Quantity:   " << quantity << endl;
        cout << "Price:      " << setprecision(2) << price << endl;
    }

    void displayTableRow() {
        cout << setw(5) << id << setw(20) << name << setw(10) << quantity << setw(10) << setprecision(2) << price << endl;
    }
};

int main() {
    vector<Item> inventory;
    int nextItemId = 1;
    int choice;

    do {
        cout << "\nInventory Management System\n";
        cout << "1. Add Item\n";
        cout << "2. Update Item\n";
        cout << "3. Remove Item\n";
        cout << "4. Display All Items\n";
        cout << "5. Search Item\n";
        cout << "6. Sort Items (Not Implemented)\n";
        cout << "7. Display Low Stock Items\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string name;
                int quantity;
                double price;
                cout << "Enter item name: ";
                getline(cin, name);
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter price: ";
                cin >> price;
                cin.ignore();
                inventory.push_back(Item(nextItemId++, name, quantity, price));
                cout << "Item added successfully with ID: " << nextItemId - 1 << endl;
                break;
            }
            case 2: {
                int itemId;
                cout << "Enter the ID of the item to update: ";
                cin >> itemId;
                cin.ignore();

                bool found = false;
                for (auto& item : inventory) {
                    if (item.getId() == itemId) {
                        cout << "Found item: " << item.getName() << endl;

                        string newName;
                        cout << "Enter new name (leave blank to keep): ";
                        getline(cin, newName);
                        if (!newName.empty()) {
                            item.setName(newName);
                        }

                        int newQuantity;
                        cout << "Enter new quantity (-1 to keep): ";
                        cin >> newQuantity;
                        if (newQuantity != -1) {
                            item.setQuantity(newQuantity);
                        }

                        double newPrice;
                        cout << "Enter new price (-1 to keep): ";
                        cin >> newPrice;
                        if (newPrice != -1) {
                            item.setPrice(newPrice);
                        }

                        cout << "Item with ID " << itemId << " updated successfully.\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Item with ID " << itemId << " not found.\n";
                }
                break;
            }
            case 3: {
                int itemId;
                cout << "Enter the ID of the item to remove: ";
                cin >> itemId;
                bool removed = false;
                for (size_t i = 0; i < inventory.size(); ++i) {
                    if (inventory[i].getId() == itemId) {
                        cout << "Removed item: " << inventory[i].getName() << endl;
                        inventory.erase(inventory.begin() + i);
                        cout << "Item with ID " << itemId << " has been removed from the inventory.\n";
                        removed = true;
                        break;
                    }
                }
                if (!removed) {
                    cout << "Item with ID " << itemId << " not found.\n";
                }
                cin.ignore();
                break;
            }
            case 4: {
                cout << "\n--- Inventory ---\n";
                cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
                cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
                for (auto& item : inventory) {
                    item.displayTableRow();
                }
                cout << "-------------------\n";
                break;
            }
            case 5: {
                int itemId;
                cout << "Enter the ID of the item to search for: ";
                cin >> itemId;
                bool found = false;
                for (auto& item : inventory) {
                    if (item.getId() == itemId) {
                        cout << "\n--- Item Details ---\n";
                        item.display();
                        cout << "----------------------\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Item with ID " << itemId << " not found.\n";
                }
                cin.ignore();
                break;
            }
            case 6:
                cout << "Sorting functionality is not implemented in this version.\n";
                break;
            case 7: {
                cout << "\n--- Low Stock Items (Quantity <= 5) ---\n";
                cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << endl;
                cout << setfill('-') << setw(35) << "" << setfill(' ') << endl;
                bool foundLowStock = false;
                for (auto& item : inventory) {
                    if (item.getQuantity() <= 5) {
                        cout << setw(5) << item.getId() << setw(20) << item.getName() << setw(10) << item.getQuantity() << endl;
                        foundLowStock = true;
                    }
                }
                if (!foundLowStock) {
                    cout << "No items with low stock.\n";
                }
                cout << "--------------------------------------\n";
                break;
            }
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}