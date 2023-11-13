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
        if (other.name != nullptr && strlen(other.name) > 0) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            qty = other.qty;
        }
        else {
            name = nullptr;
            qty = 0;
        }
    }
    ~Ingredient() {
        delete[] name;
    }
    Ingredient& operator=(const Ingredient& other) {
        if (this != &other) {
            delete[] name;
            if (other.name != nullptr && strlen(other.name) > 0) {
                name = new char[strlen(other.name) + 1];
                strcpy(name, other.name);
            }
            else name = nullptr;
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

class MenuItem {
private:
    Ingredient* ingredients = nullptr;
    int size = 0;
    string name = "";
public:
    MenuItem () {}
    MenuItem(string name, Ingredient* ingredients, int size) {
        this->name = name;
        if (ingredients != nullptr && size > 0) {
            this->ingredients = new Ingredient[size];
            for (int i = 0; i < size; i++) {
                this->ingredients[i] = ingredients[i];
            }
            this->size = size;
        }
        else {
            this->ingredients = nullptr;
            this->size = 0;
        }
    }
    MenuItem(const MenuItem& other) {
        if (other.ingredients != nullptr) {
            size = other.size;
            ingredients = new Ingredient[size];
            for (int i = 0; i < size; i++) {
                ingredients[i] = other.ingredients[i];
            }
        }
    }
    ~MenuItem() {
        if (ingredients != nullptr) {
            delete[] ingredients;
        }
    }
    // TODO:
    // all copy assignment operators should check if other.array is nullptr
    // if it's not, deep copy the array
    // if it is, set this.array to nullptr to avoid double frees
    MenuItem& operator=(MenuItem& other) {
        if (this != &other) {
            if (other.name != "") {
                this->name = other.name;
            }
            else this->name = "";
            delete[] ingredients;
            size = other.size;
            if (other.ingredients != nullptr) {
                ingredients = new Ingredient[size];
                for (int i = 0; i < size; i++) {
                    ingredients[i] = other.ingredients[i];
                }
            }
            else ingredients = nullptr;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const MenuItem& m) {
        if (m.ingredients != nullptr) {
            out << "Menu item - " << m.name << ":\n";
            for (int i = 0; i < m.size; i++) {
                out << m.ingredients[i];
            }
            out << "\n";
        }
        else {
            out << "This item doesn't have any ingredients yet!\n";
        }
        return out;
    }
};

class Stock {
private:
    Ingredient* ingredients = nullptr;
    int size = 0;
public:   
    Stock() {}
    Stock(const Stock& other) {
        if (other.size > 0) {
            size = other.size;
        }
        if (other.ingredients != nullptr) {
            ingredients = new Ingredient[size];
            for (int i = 0; i < size; i++) {
                ingredients[i] = other.ingredients[i];
            }
        }
        else ingredients = nullptr;
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
                ost << "Stock:\n";
                for (int i = 0; i < stock.size; i++) {
                    ost << stock.ingredients[i];
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
    Ingredient i4("ham", 60);
    // cout << i1 << " " << i2;
    // cout << "\n";
    // cout << i2 << "\n";
    Ingredient i3;
    // cout << i3;
    
    // Stock stock;
    // stock.push(i1);
    // cout << stock;
    // stock.push(i2);
    // cout << stock;
    // stock.push(i3);
    // cout << stock;

    // including a default constructed object in this array leads to a segfault
    // no idea why -- yes idea why
    // the copy constructor was wrong
    // (if other.array was nullptr it still allocated memory instead of setting this.array to nullptr)

    Ingredient stuff[] = {i1, i2, i3};
    MenuItem m2("Pizza", stuff, 3);
    cout << m2;
    
    return 0;
}