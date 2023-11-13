#include <iostream>
using namespace std;

class Ingredient {
private:
    char* name = nullptr;
    int qty = 0;
public:
    Ingredient() {
    }
    Ingredient(const char* name, int qty) {
        if (name != nullptr) {
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
        }
        if (qty > 0) {
            this->qty = qty;
        }
    }
    Ingredient (const Ingredient& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        qty = other.qty;
    }
    ~Ingredient() {
        delete[] name;
    }
    Ingredient& operator=(const Ingredient& other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        qty = other.qty;
        return *this;
    }
    friend ostream& operator<< (ostream& out, const Ingredient& i) {
        if (i.name != nullptr) {
            out << i.name << " " << i.qty << "\n";
        }
        else {
            out << "This item doesn't have a name yet!\n";
        }
        return out;
    }
    const char* getName() const {
        return name;
    }
};

class Stock {
private:
    Ingredient* ingredients = nullptr;
    int size = 0;
public:   
    Stock() {}
    Stock(const Stock& other) {
        size = other.size;
        ingredients = new Ingredient[size];
        for (int i = 0; i < size; i++) {
            ingredients[i] = other.ingredients[i];
        }
    }
    ~Stock() {
        if (ingredients != nullptr) {
            delete[] ingredients;
        }
    }
    void push(const Ingredient& i) {
        // pushing an item with a null name
        // will segfault
        //
        // not sure why but whatever
        if (i.getName() == nullptr) {
            return;
        }
        Ingredient* temp = new Ingredient[size + 1];
        for (int j = 0; j < size; j++) {
            temp[j] = ingredients[j];
        }
        temp[size] = i;
        delete[] ingredients;
        ingredients = temp;
        size++;
    }
    friend ostream& operator<< (ostream& ost, const Stock& stock) {
        if (stock.ingredients != nullptr) {
            if (stock.size > 0) {
                for (int i = 0; i < stock.size; i++) {
                    ost << stock.ingredients[i] << " ";
                }
                ost << "\n";
            }
        } 
        return ost;
    }
};

int main() {
    Ingredient i1("flour", 100);
    Ingredient i2("tomatoes", 50);
    cout << i1 << " " << i2;
    cout << "\n";
    cout << i2 << "\n";
    Ingredient i3;
    cout << i3;
    Stock stock;
    stock.push(i1);
    cout << stock;
    stock.push(i2);
    cout << stock;
    stock.push(i3);
    cout << stock;
    return 0;
}