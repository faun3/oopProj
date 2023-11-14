#include <iostream>
using namespace std;

// TODO:
// TODO:
// Reimplement Parser as a controller class
// Think of a solution for parsing multi-word named menu items from user input
// FIXME:
// FIXME:
// reduceStocks() doesn't really do anything, it needs to be fixed



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
    // objects with null names ALWAYS compare to false
    // but they don't compare false against themselves
    friend bool operator==(const Ingredient& left, const Ingredient& right) {
        if (&left != &right) {
        if (left.name != nullptr && right.name != nullptr) {
            if (strcmp(left.name, right.name) == 0 && left.qty == right.qty) return true;
            else return false;
        }
        else return false;
        }
        else return true;
    }
    const char* getName() {
        return name;
    }
    int getQty() const {
        return qty;
    }
    void setQty(int newQty) {
        if (newQty < 0) {
            throw new runtime_error("Quantity cannot be negative!");
        }
        else this->qty = newQty;
    }
    Ingredient operator+(int extraQty) {
		if (extraQty > 0) {
			Ingredient res = *this;
			res.qty += extraQty;
			return res;
		}
	}
    Ingredient& operator++() {
        this->qty++;
        return *this;
    }
    
    Ingredient operator++(int) {
        Ingredient temp = *this;
        this->qty++;
        return temp;
    }

    Ingredient& operator--() {
        if (this->qty >= 1) {
            this->qty--;
            return *this;
        }
        else {
            throw runtime_error("Stock is already 0!");
        }
    }

    Ingredient operator--(int) {
        if (this->qty >= 1) {
            Ingredient temp = *this;
            this->qty--;
            return temp;
        }
        else {
            throw runtime_error("Stock is already 0!");
        }
    }
    explicit operator int() {
        return this->qty;
    }
    bool operator!() {
        return !(this->qty);
    }
    bool operator>(const Ingredient& other) {
        return this->qty > other.qty;
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
    string getName() const{
        return name;
    }
    Ingredient* getIngredients() {
        return this->ingredients;
    }
    int getSize() {
        return this->size;
    }
    Ingredient operator[](int at) {
        if (at >= 0 && at < this->size) {
            return this->ingredients[at];
        }
        else throw runtime_error("Invalid index!");
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
        if (this->size <= 0 || this->items == nullptr) {
            return false;
        }
        else {
            for (int i = 0; i < this->size; i++) {
                if (this->items[i].getName() == menuItemName) {
                    return true;
                }
            }
            return false;
        }
    }
    void push(MenuItem& m) {
        // don't push anything if the menu item has an empty name, an empty ingredient list, or a null ingredient list

        if (m.getName() == "" || m.getIngredients() == nullptr || m.getSize() == 0) {
            // cout << "\nDEBUG ONLY: pushed MenuItem has an empty name, an empty ingredient list, or a null ingredient list\n";
            return;
        }
        // don't push anything if the item already exists
        
        if (this->isInMenu(m.getName())) {
            // cout << "\nDEBUG ONLY: pushed MenuItem is already in the menu\n";
            return;
        }
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

struct OrderItem
{
    MenuItem item;
    int qty;
};

class Order {
private:
    OrderItem* items = nullptr;
    int size = 0;
public:
    Order() {}
    Order(const Order& other) {
        if (other.items != nullptr && other.size > 0) {
            size = other.size;
            delete[] items;
            items = new OrderItem[size];
            for (int i = 0; i < size; i++) {
                items[i] = other.items[i];
            }
        }
        else {
            items = nullptr;
            size = 0;
        }
    }
    ~Order () {
        if (this->items != nullptr) {
            delete[] this->items;
        }
    }
    Order& operator=(const Order& other) {
        if (this != &other) {
            if (other.items != nullptr && other.size > 0) {
                size = other.size;
                delete[] items;
                items = new OrderItem[size];
                for (int i = 0; i < size; i++) {
                    items[i] = other.items[i];
                }
            }
            else {
                this->items = nullptr;
                this->size = 0;
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Order& o) {
        if (o.items != nullptr && o.size > 0) {
            out << "Order:\n";
            for (int i = 0; i < o.size; i++) {
                out << o.items[i].item.getName() << " " << o.items[i].qty << "\n";
            }
        }
        else {
            out << "This order is empty!\n";
        }
        return out;
    }
    // -1 for not found
    // index of item in array otherwise
    int isInOrders(string itemName) {
        if (itemName == "") {
            return -1;
        }
        if (this->size <= 0 || this->items == nullptr) {
            return -1;
        }
        else {
            for (int i = 0; i < this->size; i++) {
                if (this->items[i].item.getName() == itemName) {
                    return i;
                }
            }
            return -1;
        }
    }
    void push(MenuItem& m) {
        if (m.getName() == "" || m.getIngredients() == nullptr || m.getSize() == 0) {
            return;
        }
        int isInOrders = this->isInOrders(m.getName());
        if (isInOrders != -1) {
            this->items[isInOrders].qty++;
        }
        else {
            OrderItem* temp = new OrderItem[this->size + 1];
            for (int i = 0; i < this->size; i++) {
                temp[i] = this->items[i];
            }
            OrderItem tempItem;
            tempItem.item = m;
            tempItem.qty = 1;
            temp[this->size] = tempItem;
            this->size++;
            delete[] this->items;
            this->items = temp;
        }
    }
    int getSize() {
        return this->size;
    }
    OrderItem* getItems() {
        return this->items;
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
    void push(Ingredient& i) {
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
    Ingredient* getIngredients() {
        return this->ingredients;
    }
    int findByName(const char* name) {
        if (name == nullptr) {
            return -1;
        }
        else {
            if (this->ingredients == nullptr || this->size == 0) {
                return -1;
            }
            else {
                for (int i = 0; i < this->size; i++){
                    if (strcmp(this->ingredients[i].getName(), name) == 0) {
                        return i;
                    }
                }
            }
        }
    }
    // untested spaghetti code
    Stock reduceStock(Order& order) {
        Stock copy = *this;
        for (int i = 0; i < order.getSize(); i++) {
            // here we're looping through OrderItems
            for (int j = 0; j < order.getItems()[i].item.getSize(); j++) {
                // here we're looping through ingredients

                // check for a match
                // if the ingredient is in the order
                // but it's not in stock -- the order fails
                // if the ingredient is in the order AND in stock
                // and the orderQty (Ingredient.qty * OrderItem.qty) is less than Stock.Ingredient.qty
                // the order goes through
                // fail fallthrough
                for (int k = 0; k < this->size; k++) {
                    if (order.getItems()[i].item.getIngredients()[j].getName() == this->ingredients[k].getName()) {
                        if (order.getItems()[i].item.getIngredients()[j].getQty() * order.getItems()[i].qty > this->ingredients[k].getQty()) {
                            string offendingItem = ingredients[k].getName();
                            string message = "Not enough stock! " + offendingItem + " is not in stock in the desired quanity\n";
                            throw new runtime_error(message);
                        }
                        else {
                            copy.ingredients[k].setQty(copy.ingredients[k].getQty() - order.getItems()[i].item.getIngredients()[j].getQty() * order.getItems()[i].qty);
                        }
                    }
                }
            }
        }
        return copy;
    }
};

int main() 
{
    Ingredient i1("flour", 100);
    Ingredient i2("tomatoes", 50);
    Ingredient i4("ham", 60);
    Ingredient i5("cheese", 40);
    Ingredient i6("olives", 15);
    Ingredient i7("pineapple", 10);
    Ingredient i8("nothing", 0);
    Ingredient i9("nothing", 0);
    Ingredient i3;
    
    Ingredient si1("flour", 1000);
    Ingredient si2("tomatoes", 500);
    Ingredient si3("ham", 600);
    Ingredient si4("cheese", 400);
    Ingredient si5("olives", 150);
    Ingredient si6("pineapple", 100);
    Ingredient si7("beans", 60);
    
    Stock stock;
    stock.push(si1);
    stock.push(si2);
    stock.push(si3);
    stock.push(si4);
    stock.push(si5);
    stock.push(si6);
    cout << stock;

    // including a default constructed object in this array leads to a segfault
    // no idea why -- yes idea why
    // the copy constructor was wrong
    // (if other.array was nullptr it still allocated memory instead of setting this.array to nullptr)

    Ingredient stuff[] = {i1, i2, i4};
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
    menu.push(m3);
    menu.push(m2);
    cout << menu;

    Order order;
    order.push(m3);
    order.push(m3);
    order.push(m2);
    cout << order;

    // removing the ingredients works, copying into stock doesn't 
    cout << stock;
    
    cout << "\n";
    cout << order.getItems()[0].item.getIngredients()[0].getName();
    cout << "\n";

    cout << stock.getIngredients()[0].getName();
    cout << "\n";

    cout << order.getItems()[0].item.getIngredients()[0].getQty();
    cout << "\n";

    cout << order.getItems()[0].qty;
    cout << "\n";
    
    stock.getIngredients()[0].setQty(stock.getIngredients()[0].getQty() - order.getItems()[0].item.getIngredients()[0].getQty() * order.getItems()[0].qty);

    cout << stock.getIngredients()[0].getQty();
    cout << "\n";

    Stock newStock = stock.reduceStock(order);
    cout << "\n";
    cout << newStock;
    cout << "\n";

    return 0;
}