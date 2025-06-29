#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Global Variables (replacing the struct System)
string names[10];
string categories[10];
int quantities[10];
double prices[10];
int productcount = 0;

// Function Prototypes
void addproduct();
void updateproduct();
void removeproduct();
void displaybycategory();
void findlowstock(int threshold);
void applydiscount();
void listlowstock(int threshold);
double calculateinventoryvalue();
double forecastrevenue(double adjustment);
void searchproduct();

// Function Definitions
void addproduct() {
    if (productcount >= 10) {
        cout << "Inventory is full. Cannot add more products.\n";
        return;
    }
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, names[productcount]);
    cout << "Enter product category (e.g., electronics, groceries): ";
    getline(cin, categories[productcount]);
    cout << "Enter quantity of " << names[productcount] << ": ";
    cin >> quantities[productcount];
    cout << "Enter price of " << names[productcount] << ": ";
    cin >> prices[productcount];
    productcount++;
    cout << "Product added successfully.\n";
}

void listlowstock(int threshold) {
    cout << "\nList of all low stock items (Threshold: " << threshold << "):\n";
    bool found = false;
    for (int i = 0; i < productcount; i++) {
        if (quantities[i] < threshold) {
            cout << "Name: " << names[i]
                << ", Category: " << categories[i]
                << ", Quantity: " << quantities[i]
                << ", Price: " << prices[i] << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No low stock items found.\n";
    }
}

void updateproduct() {
    string targetname;
    cout << "Enter the product name to update: ";
    cin.ignore();
    getline(cin, targetname);
    for (int i = 0; i < productcount; i++) {
        if (names[i] == targetname) {
            cout << "Enter new quantity for " << names[i] << ": ";
            cin >> quantities[i];
            cout << "Enter new price for " << names[i] << ": ";
            cin >> prices[i];
            cout << "Product updated successfully.\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void removeproduct() {
    string targetname;
    cout << "Enter the product name to remove: ";
    cin.ignore();
    getline(cin, targetname);
    for (int i = 0; i < productcount; i++) {
        if (names[i] == targetname) {
            for (int j = i; j < productcount - 1; j++) {
                names[j] = names[j + 1];
                categories[j] = categories[j + 1];
                quantities[j] = quantities[j + 1];
                prices[j] = prices[j + 1];
            }
            productcount--;
            cout << "Product removed successfully.\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void displaybycategory() {
    string targetcategory;
    cout << "Enter the category to display: ";
    cin.ignore();
    getline(cin, targetcategory);
    bool found = false;
    for (int i = 0; i < productcount; i++) {
        if (categories[i] == targetcategory) {
            cout << "Product name: " << names[i] << ", Quantity: " << quantities[i]
                << ", Price: " << prices[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "No products found in this category.\n";
}

void findlowstock(int threshold) {
    cout << "Low stock items (Threshold: " << threshold << "):\n";
    bool found = false;
    for (int i = 0; i < productcount; i++) {
        if (quantities[i] < threshold) {
            cout << "Product name: " << names[i] << ", Quantity: " << quantities[i] << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No products found with low stock.\n";
    }
}

void applydiscount() {
    string targetcategory;
    double discount;
    cout << "Enter category for discount: ";
    cin.ignore();
    getline(cin, targetcategory);
    cout << "Enter discount percentage (e.g., 10 for 10%): ";
    cin >> discount;
    bool applied = false;
    for (int i = 0; i < productcount; i++) {
        if (categories[i] == targetcategory) {
            double originalPrice = prices[i];
            prices[i] -= prices[i] * (discount / 100);
            cout << "Price for " << names[i] << " after discount: " << prices[i]
                << " (Original: " << originalPrice << ")\n";
            applied = true;
        }
    }
    if (!applied) {
        cout << "No products found in category: " << targetcategory << "\n";
    }
}

double calculateinventoryvalue() {
    double totalvalue = 0;
    for (int i = 0; i < productcount; i++) {
        totalvalue += quantities[i] * prices[i];
    }
    return totalvalue;
}

double forecastrevenue(double adjustmentPercentage) {
    double totalRevenue = 0.0;
    for (int i = 0; i < productcount; i++) {
        double adjustedRevenue = (prices[i] * quantities[i]) * (1 + adjustmentPercentage / 100.0);
        totalRevenue += adjustedRevenue;
    }
    return totalRevenue;
}

void searchproduct() {
    string targetname;
    cout << "Enter the product name to search: ";
    cin.ignore();
    getline(cin, targetname);

    bool found = false;
    for (int i = 0; i < productcount; i++) {
        if (names[i] == targetname) {
            cout << "\nProduct found:\n";
            cout << "Name: " << names[i] << "\n";
            cout << "Category: " << categories[i] << "\n";
            cout << "Quantity: " << quantities[i] << "\n";
            cout << "Price: " << prices[i] << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Product not found in inventory.\n";
    }
}

int main() {
    system("color 80");
    cout << "\t=========================================================\n";
    cout << "\t - - - - Welcome to Retail Store Inventory System - - - -\n";
    cout << "\t=========================================================\n\n";
    int choice;
    do {
        cout << "\t\t\tMenu:\n";
        cout << "\t\t\t1. Add Product\n";
        cout << "\t\t\t2. Update Product\n";
        cout << "\t\t\t3. Remove Product\n";
        cout << "\t\t\t4. Display Inventory by Category\n";
        cout << "\t\t\t5. Find Low Stock Items\n";
        cout << "\t\t\t6. Apply Discount\n";
        cout << "\t\t\t7. Show all list of low Stock Items.\n";
        cout << "\t\t\t8. Calculate Inventory Value\n";
        cout << "\t\t\t9. Forecast Revenue\n";
        cout << "\t\t\t10. Searching products\n";
        cout << "\t\t\t11. Exit\n";
        cout << "\t\t\tEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            addproduct();
            break;
        case 2:
            system("cls");
            updateproduct();
            break;
        case 3:
            system("cls");
            removeproduct();
            break;
        case 4:
            system("cls");
            displaybycategory();
            break;
        case 5: {
            system("cls");
            int threshold;
            cout << "Enter low stock threshold: ";
            cin >> threshold;
            findlowstock(threshold);
            break;
        }
        case 6:
            system("cls");
            applydiscount();
            break;
        case 7: {
            system("cls");
            int threshold;
            cout << "Enter the low stock threshold: ";
            cin >> threshold;
            listlowstock(threshold);
            break;
        }
        case 8:
            system("cls");
            cout << "Total inventory value: " << calculateinventoryvalue() << "\n";
            break;
        case 9: {
            system("cls");
            cout << "\nSelect Season for Revenue Forecasting:\n";
            cout << "1. Holiday Season (+20%)\n";
            cout << "2. Off-Season (-10%)\n";
            cout << "3. Normal Season (0%)\n";
            cout << "Enter your choice: ";
            int seasonChoice;
            cin >> seasonChoice;
            double adjustment = 0.0;
            switch (seasonChoice) {
            case 1: adjustment = 20.0; break;
            case 2: adjustment = -10.0; break;
            case 3: adjustment = 0.0; break;
            default:
                cout << "Invalid choice. Defaulting to Normal Season (0%).\n";
                adjustment = 0.0;
                break;
            }
            double totalRevenue = forecastrevenue(adjustment);
            cout << fixed << setprecision(2);
            cout << "Total Forecasted Revenue (after adjustment): " << totalRevenue << "\n";
            break;
        }
        case 10:
            system("cls");
            searchproduct();
            break;
        case 11:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 11);
    system("pause");
    return 0;
}
