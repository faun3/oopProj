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
    string getName() {
        return name;
    }
    const Ingredient* getIngredients() {
        return ingredients;
    }
    int getSize() {
        return size;
    }
};

class Menu {
private:
    MenuItem* items = nullptr;
    int size = 0;
public:
    Menu() {}
    Menu(const Menu& other) {
        if (other.items != nullptr && other.size > 0) {
            // TODO:
            // all copy constructor steps should be the following
            // 1. check if other.array is nullptr
            //  1.1 if yes, set this.array to nullptr and this.size to 0
            // 1.2 if no, deep copy the array and size into this
            this->size = other.size;
            delete[] this->items;
            this->items = nullptr;
            this->items = new MenuItem[size];
            for (int i = 0; i < size; i++) {
                this->items[i] = other.items[i];
            }
        }
        else {
            this->items = nullptr;
            this->size = 0;
        }
    }
    ~Menu() {
        if (this->items != nullptr) {
            delete[] items;
        }
    }
    Menu& operator=(const Menu& other) {
        if (other.items != nullptr && other.size > 0) {
            size = other.size;
            delete[] items;
            items = new MenuItem[size];
            for (int i = 0; i < size; i++) {
                items[i] = other.items[i];
            }
        }
        else {
            this->items = nullptr;
            this->size = 0;
        }
    }
    bool isInMenu(string menuItemName) {
        // MenuItems with empty names are not included in any menu
        if (menuItemName == "") {
            return false;
        }
        // if the MenuItem array of our menu is null
        // or its length is 0
        // there's no items to search for
        if (this->size = 0 || this->items == nullptr) {
            return false;
        }
        for (int i = 0; i < this->size; i++) {
            if (this->items[i].getName() == menuItemName) {
                return true;
            }
        }
        return false;
    }
    void push(MenuItem& m) {
        // don't push anything if the menu item has an empty name, an empty ingredient list, or a null ingredient list

        // if (m.getName() == "" || m.getIngredients() == nullptr || m.getSize() == 0) {
        //     cout << "\nDEBUG ONLY: pushed MenuItem has an empty name, an empty ingredient list, or a null ingredient list\n";
        //     return;
        // }
        // don't push anything if the item already exists
        
        // if (this->isInMenu(m.getName())) {
        //     cout << "\nDEBUG ONLY: pushed MenuItem is already in the menu\n";
        //     return;
        // }
        MenuItem* temp = new MenuItem[this->size + 1];
        for (int i = 0; i < this->size; i++) {
            temp[i] = this->items[i];
        }
        temp[this->size] = m;
        delete[] this->items;
        this->items = temp;
        this->size++;
    }
    friend ostream& operator<<(ostream& out, const Menu& m) {
        if (m.items != nullptr && m.size > 0) {
            out << "Menu:\n";
            for (int i = 0; i < m.size; i++) {
                out << m.items[i];
            }
        }
        else {
            out << "This menu is empty!\n";
        }
        // FIXME:
        // don't forget to return ost when you overload <<
        // or you'll get a trace trap error :(
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
    Ingredient i5("cheese", 40);
    Ingredient i6("olives", 15);
    Ingredient i7("pineapple", 10);
    Ingredient i3;
    
    Stock stock;
    stock.push(i1);
    stock.push(i2);
    stock.push(i3);

    // including a default constructed object in this array leads to a segfault
    // no idea why -- yes idea why
    // the copy constructor was wrong
    // (if other.array was nullptr it still allocated memory instead of setting this.array to nullptr)

    Ingredient stuff[] = {i1, i2, i3};
    Ingredient stuff2[] = {i1, i2, i5, i6, i7};
    MenuItem m2("Pizza", stuff, 3);
    MenuItem m3("Hawaii", stuff2, 5);
    MenuItem m4;
    // cout << m4;
    MenuItem m5;
    // m5 = m4;
    // cout << m5;
    // m5 = m3;
    // cout << m5;
    Menu menu;
    cout << menu;
    menu.push(m3);
    cout << menu;
    menu.push(m2);
    cout << menu;
    menu.push(m4);
    cout << menu;
    return 0;
}