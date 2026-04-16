#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

class Product {
public:
    string name;
    double price;
    int quantity;

    Product(string n, double p, int q) {
        name = n;
        price = p;
        quantity = q;
    }
};

class Order {
private:
    vector<Product> cart;
    string date;
    string status;
    string paymentMethod;
    int discountIndex;

public:
    void setDate(string d, int index) {
        date = d;
        discountIndex = index;
    }

    void setStatus(string s) {
        status = s;
    }

    void setPayment(string p) {
        paymentMethod = p;
    }

    void updateStatus(string s) {
        status = s;
    }

    void addProduct(string name, double price, int quantity, int index) {

        if (index == discountIndex) {
            price *= 0.9;
            cout << "Day discount applied!\n";
        }

        for (auto& p : cart) {
            if (p.name == name) {
                p.quantity += quantity;
                return;
            }
        }

        cart.push_back(Product(name, price, quantity));
    }

    void removeProduct(string name) {
        for (int i = 0; i < cart.size(); i++) {
            if (cart[i].name == name) {
                cart.erase(cart.begin() + i);
                cout << "Removed!\n";
                return;
            }
        }
        cout << "Not found!\n";
    }

    void changeQuantity(string name, int q) {
        for (auto& p : cart) {
            if (p.name == name) {
                p.quantity = q;
                cout << "Quantity updated!\n";
                return;
            }
        }
        cout << "Not found!\n";
    }

    double getTotal() {
        double total = 0;
        for (auto& p : cart) {
            total += p.price * p.quantity;
        }
        return total;
    }

    void show() {
        cout << "\n=== SILPO ORDER ===\n";
        cout << "Date: " << date << endl;
        cout << "Status: " << status << endl;
        cout << "Payment: " << paymentMethod << endl;

        double total = 0;

        for (auto& p : cart) {
            double sum = p.price * p.quantity;
            cout << p.name << " x" << p.quantity << " = $" << sum << endl;
            total += sum;
        }

        cout << "TOTAL: $" << total << endl;
    }

    void save() {
        ofstream f("silpo.txt");

        if (!f.is_open()) {
            cout << "Error saving file!\n";
            return;
        }

        f << date << endl;
        f << status << endl;
        f << paymentMethod << endl;

        for (auto& p : cart) {
            f << p.name << " "
                << p.price << " "
                << p.quantity << endl;
        }

        f.close();
        cout << "Order saved successfully!\n";
    }

    void load() {
        ifstream f("silpo.txt");

        if (!f.is_open()) {
            cout << "File not found!\n";
            return;
        }

        cart.clear();

        getline(f, date);
        getline(f, status);
        getline(f, paymentMethod);

        string name;
        double price;
        int q;

        while (f >> name >> price >> q) {
            cart.push_back(Product(name, price, q));
        }

        f.close();
        cout << "Order loaded successfully!\n";
    }

    void processOrder() {
        cout << "\nProcessing payment...\n";

        updateStatus("Paid");
        show();
        this_thread::sleep_for(chrono::seconds(2));

        updateStatus("Packed");
        cout << "\nPacking...\n";
        show();
        this_thread::sleep_for(chrono::seconds(2));

        updateStatus("Shipped");
        cout << "\nShipping...\n";
        show();
        this_thread::sleep_for(chrono::seconds(2));

        updateStatus("Delivered");
        cout << "\nDelivered!\n";
        show();

        cout << "\n===========================================\n";
        cout << "        THANK YOU FOR SHOPPING AT SILPO \n";
        cout << "-------------------------------------------\n";
        cout << " Your order has been successfully delivered!\n";
        cout << " We truly appreciate your choice ❤\n";
        cout << "\n";
        cout << " Have a wonderful day and see you again! \n";
        cout << "===========================================\n";
        cout << "            END OF ORDER\n";
        cout << "===========================================\n";
    }
};

int main() {

    vector<string> items = { "Milk", "Bread", "Apple", "Cheese", "Juice" };
    vector<double> prices = { 2.5, 1.5, 0.8, 4.0, 2.0 };

    int day, month;
    char dot;

    cout << "Enter date (dd.mm): ";
    cin >> day >> dot >> month;

    int discountIndex = (day + month) % items.size();

    cout << "Discount today: " << items[discountIndex] << " (-10%)\n";

    Order order;
    order.setDate("date", discountIndex);
    order.setStatus("Pending");

    int choice;

    while (true) {
        cout << "\n=== SILPO MENU ===\n";
        cout << "1. Show products\n";
        cout << "2. Add products\n";
        cout << "3. Remove product\n";
        cout << "4. Change quantity\n";
        cout << "5. Show order / Pay\n";
        cout << "6. Apply promo\n";
        cout << "7. Save\n";
        cout << "8. Load\n";
        cout << "0. Exit\n";

        cout << "Choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            for (int i = 0; i < items.size(); i++) {
                cout << i + 1 << ". " << items[i]
                    << " - $" << prices[i];

                if (i == discountIndex) {
                    cout << " (-10%)";
                }
                cout << endl;
            }
        }

        else if (choice == 2) {
            int id, q;
            while (true) {
                cout << "\nEnter product number (0 to stop): ";
                cin >> id;
                if (id == 0) break;

                if (id >= 1 && id <= items.size()) {
                    cout << "Quantity: ";
                    cin >> q;
                    order.addProduct(items[id - 1], prices[id - 1], q, id - 1);
                }
                else {
                    cout << "Invalid!\n";
                }
            }
        }

        else if (choice == 3) {
            string name;
            cout << "Name: ";
            cin >> name;
            order.removeProduct(name);
        }

        else if (choice == 4) {
            string name;
            int q;
            cout << "Name: ";
            cin >> name;
            cout << "New quantity: ";
            cin >> q;
            order.changeQuantity(name, q);
        }

        else if (choice == 5) {
            order.show();

            char confirm;
            cout << "\nDo you want to pay? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {

                int pay;
                cout << "\n1. Card\n2. Cash\n3. Online\n";
                cout << "Choose payment: ";
                cin >> pay;

                if (pay == 1) order.setPayment("Card");
                else if (pay == 2) order.setPayment("Cash");
                else if (pay == 3) order.setPayment("Online");

                order.processOrder();
                break;
            }
        }

        else if (choice == 6) {
            string promo;
            cout << "Enter promo: ";
            cin >> promo;

            double total = order.getTotal();

            if (promo == "SALE10") {
                total *= 0.9;
                cout << "Promo -10% applied!\n";
            }
            else if (promo == "SALE20") {
                total *= 0.8;
                cout << "Promo -20% applied!\n";
            }
            else {
                cout << "Invalid promo!\n";
            }

            cout << "TOTAL WITH PROMO: $" << total << endl;
        }

        else if (choice == 7) {
            order.save();
        }

        else if (choice == 8) {
            order.load();
        }
    }

    return 0;
}