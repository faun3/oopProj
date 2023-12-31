#include <iostream>
#include <sstream> // for istringstream -- might not be needed
#include <string>
using namespace std;

class Ingredient {
private:
    char* name = nullptr;
    int qty = 0;
public:
    Ingredient() {
    }
    // this was changed
    Ingredient(const char* name, int qty) {
        if (name != nullptr && strlen(name) > 0) {
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
        }
        if (qty > 0) {
            this->qty = qty;
        }
    }
    // this was also changed to reflect the change
    // in the constructor above
    Ingredient (const Ingredient& other) {
        if (other.name != nullptr && strlen(other.name) > 0) {
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
        if (other.qty > 0) {
            this->qty = other.qty;
        }
    }
    ~Ingredient() {
        delete[] name;
    }
    // this was also changed to reflect the changes in the copy constructor
    Ingredient& operator=(const Ingredient& other) {
        if (this != &other) {
            delete[] name;
            if (other.name != nullptr && strlen(other.name) > 0) {
                this->name = new char[strlen(other.name) + 1];
                strcpy(this->name, other.name);
            }
            if (other.qty > 0) {
                this->qty = other.qty;
            }
        }
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
    void setName(char* newName) {
        if (newName == nullptr || strlen(newName) == 0) {
            throw new runtime_error("Name cannot be empty!");
        }
        else {
            delete[] this->name;
            this->name = new char[strlen(newName) + 1];
            strcpy(this->name, newName);
        }
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
    friend istream& operator>> (istream& is, Ingredient& i) {
        cout << "\nIngredient quantity: ";
        string uhOh;
        is >> uhOh;
        try {
            int parsedValue = stoi(uhOh);
            if (parsedValue > 0) {
                i.qty = parsedValue;
            }
            else i.qty = 0;
        }
        catch (invalid_argument) {
            cout << "\nQuantity should be a positive integer! The provided value was replaced with 0.\n";
            i.qty = 0;
        }
        
        cout << "\nIngredient name: ";
        // consume the newline character in the buffer so we can read our ingredient name
        getline(is, uhOh);
        getline(is, uhOh);
        if (uhOh.size() > 0) {
            i.name = new char[uhOh.size() + 1];
            strcpy(i.name, uhOh.data());
        }
        else {
            cout << "\nIngredient name cannot be empty! The provided name was replaced with an empty string.\n";
        }

        return is;
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
        if (name != "") {
            this->name = name;
        }
        else this->name = "";
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
        if (other.name != "") {
            this->name = other.name;
        }
        else this->name = "";
        if (other.ingredients != nullptr && other.size > 0) {
            this->ingredients = new Ingredient[other.size];
            for (int i = 0; i < other.size; i++) {
                this->ingredients[i] = other.ingredients[i];
            }
            this->size = other.size;
        }
        else {
            this->ingredients = nullptr;
            this->size = 0;
        }
    }
    ~MenuItem() {
        if (this->ingredients != nullptr) {
            delete[] this->ingredients;
        }
    }
    MenuItem& operator=(MenuItem& other) {
        if (this != &other) {
            if (this->ingredients != nullptr) {
                delete[] this->ingredients;
            }
            if (other.name != "") {
                this->name = other.name;
            }
            else this->name = "";
            if (other.ingredients != nullptr && other.size > 0) {
                this->ingredients = new Ingredient[other.size];
                for (int i = 0; i < other.size; i++) {
                    this->ingredients[i] = other.ingredients[i];
                }
                this->size = other.size;
            }
            else {
                this->ingredients = nullptr;
                this->size = 0;
            }
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
    friend istream& operator>>(istream& in, MenuItem& m) {
        string buffer;
        cout << "\nMenu item name: ";
        in >> buffer;
        if (buffer != "" && buffer.size() > 0) {
            m.name = buffer;
        }
        else {
            cout << "\nMenu item name cannot be empty! Menu item name reset to an empty string.";
            m.name = "";
        }
        cout << "\nNr of ingredients: ";
        in >> buffer;
        try {
            int ingArrLen = stoi(buffer);
            if (ingArrLen > 0) {
                m.size = ingArrLen;
                delete[] m.ingredients;
                m.ingredients = new Ingredient[m.size];
                cout << "\nIngredients: ";
                for (int i = 0; i < m.size; i++) {
                    Ingredient temp;
                    in >> temp;
                    m.ingredients[i] = temp;
                }
            }
            else {
                cout << "\nMenu items should have a positive integer nr of ingredients! Nr of ingredients was reset to 0";
                m.size = 0;
                delete[] m.ingredients;
                m.ingredients = nullptr;
            }
        }
        catch (invalid_argument) {
            cout << "\nMenu items should have a positive integer nr of ingredients! Nr of ingredients was reset to 0";
        }
        return in;
    }
    string getName() {
        return name;
    }
    Ingredient* getIngredients() {
        return this->ingredients;
    }
    int getSize() {
        return this->size;
    }
    void setName(string newName) {
        if (newName == "" || newName.size() == 0) {
            throw new runtime_error("Name cannot be empty!");
        }
        this->name = newName;
    }
    // TODO: setSize
    void setSize(int newSize) {
        if (newSize <= 0 || newSize > this->size) {
            throw new runtime_error("Size must be a positive integer that is not larger than the current size!");
        }
        if (this->ingredients != nullptr) {
            Ingredient* temp = new Ingredient[newSize];
            for (int i = 0; i < newSize; i++) {
                temp[i] = this->ingredients[i];
            }
            delete[] this->ingredients;
            this->ingredients = temp;
            this->size = newSize;
        }
    }
    // TODO: setIngredients
    void setIngredients(int newSize, Ingredient* newIngredients) {
        if (newSize <= 0) {
            throw new runtime_error("Size must be a positive integer!");
        }
        if (newIngredients == nullptr) {
            throw new runtime_error("Ingredient array cannot be null!");
        }
        if (this->ingredients != nullptr) {
            delete[] this->ingredients;
        }
        this->ingredients = new Ingredient[newSize];
        for (int i = 0; i < newSize; i++) {
            this->ingredients[i] = newIngredients[i];
        }
        this->size = newSize;
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
    Menu(MenuItem* items, int size) {
        if (items != nullptr && size > 0) {
            this->size = size;
            this->items = new MenuItem[size];
            for (int i = 0; i < size; i++) {
                this->items[i] = items[i];
            }
        }
        else {
            this->items = nullptr;
            this->size = 0;
        }
    }
    Menu(const Menu& other) {
        if (other.items != nullptr && other.size > 0) {
            this->size = other.size;
            this->items = new MenuItem[other.size];
            for (int i = 0; i < other.size; i++) {
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
        if (this != &other) {
            if (this->items != nullptr) {
                delete[] items;
            }
            if (other.items != nullptr && other.size > 0) {
                this->size = other.size;
                this->items = new MenuItem[other.size];
                for (int i = 0; i < other.size; i++) {
                this->items[i] = other.items[i];
            }
            }
            else {
                this->items = nullptr;
                this->size = 0;
            }
        }
        return *this;
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
    int getByName (string menuItemName) {
        if (menuItemName == "") return -1;
        if (this->size <= 0 || this->items == nullptr) {
            return -1;
        }
        else {
            for (int i = 0; i < this->size; i++){
                if (this->items[i].getName() == menuItemName) {
                    return i;
                }
            }
        }
        return -1;
    }
    MenuItem getMenuItemByName(int idx) {
        if (idx != -1) {
            return this->items[idx];
        }
        else throw new runtime_error("Item is not in menu!");
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
    friend istream& operator>>(istream& in, Menu& m) {
        string buffer;
        cout << "\nNr of menu items: ";
        in >> buffer;
        try {
            int newSize = stoi(buffer);
            if (newSize > 0) {
                m.size = newSize;
                delete[] m.items;
                m.items = new MenuItem[m.size];
                for (int i = 0; i < m.size; i++) {
                    MenuItem temp;
                    in >> temp;
                    m.items[i] = temp;
                }
            }
            else {
                cout << "\nNr of menu items should be a positive integer! Nr of menu items was reset to 0";
                m.size = 0;
                delete[] m.items;
                m.items = nullptr;
            }
        }
        catch (invalid_argument) {
            cout << "\nNr of menu items should be a positive integer! Nr of menu items was reset to 0";
            m.size = 0;
            delete[] m.items;
            m.items = nullptr;
        }
        return in;
    }
    MenuItem* getItems() {
        return this->items;
    }
    void setItems(int newSize, MenuItem* newItems) {
        if (newSize <= 0) {
            throw new runtime_error("Size must be a positive integer!");
        }
        if (newItems == nullptr) {
            throw new runtime_error("Ingredient array cannot be null!");
        }
        if (this->items != nullptr) {
            delete[] this->items;
        }
        this->items = new MenuItem[newSize];
        for (int i = 0; i < newSize; i++) {
            this->items[i] = newItems[i];
        }
        this->size = newSize;
    }
    int getSize() {
        return this->size;
    }
    void setSize(int newSize) {
        if (newSize <= 0 || newSize > this->size) {
            throw new runtime_error("Size must be a positive integer that is not larger than the current size!");
        }
        if (this->items != nullptr) {
            MenuItem* temp = new MenuItem[newSize];
            for (int i = 0; i < newSize; i++) {
                temp[i] = this->items[i];
            }
            delete[] this->items;
            this->items = temp;
            this->size = newSize;
        }
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
    Order (int size, OrderItem* items) {
        if (size > 0 && items != nullptr) {
            this->size = size;
            this->items = new OrderItem[size];
            for (int i = 0; i < size; i++) {
                this->items[i] = items[i];
            }
        }
        else {
            this->items = nullptr;
            this->size = 0;
        }
    }
    Order(const Order& other) {
        if (other.size > 0 && other.items != nullptr) {
            this->size = other.size;
            this->items = new OrderItem[other.size];
            for (int i = 0; i < other.size; i++) {
                this->items[i] = other.items[i];
            }
        }
        else {
            this->items = nullptr;
            this->size = 0;
        }
    }
    ~Order () {
        if (this->items != nullptr) {
            delete[] this->items;
        }
    }
    Order& operator=(const Order& other) {
        if (this != &other) {
            if (this->items != nullptr) {
                delete[] this->items;
            }
            if (other.size > 0 && other.items != nullptr) {
                this->size = other.size;
                this->items = new OrderItem[other.size];
                for (int i = 0; i < other.size; i++) {
                    this->items[i] = other.items[i];
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
    friend istream& operator>> (istream& in, Order& o) {
        string buffer;
        cout << "\nNr of order items: ";
        in >> buffer;
        try {
            int orderSize = stoi(buffer);
            if (orderSize < 0) {
                throw new runtime_error("Nr of order items should be a positive integer!");
            }
            o.size = orderSize;
            delete[] o.items;
            o.items = new OrderItem[o.size];
            for (int i = 0; i < o.size; i++) {
                OrderItem temp;
                cout << "\nOrder item quantity: ";
                in >> buffer;
                try {
                    int orderItemQty = stoi(buffer);
                    if (orderItemQty < 0) {
                        throw new runtime_error("Order item quantity should be a positive integer!");
                    }
                    o.items[i].qty = orderItemQty;
                    cout << "\nOrder item: ";
                    in >> temp.item;
                    o.items[i].item = temp.item;
                }
                catch (invalid_argument) {
                    throw new runtime_error("Order item quantity should be a positive integer!");
                }
                o.items[i] = temp;

            }
        }
        catch (invalid_argument) {
            throw new runtime_error("Nr of order items should be a positive integer!");
        }
        return in;
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
    void emptyOrder() {
        delete[] this->items;
        this->size = 0;
        this->items = nullptr;
    }
    void push(MenuItem& m, int qty) {
        if (m.getName() == "" || m.getIngredients() == nullptr || m.getSize() == 0) {
            return;
        }
        int isInOrders = this->isInOrders(m.getName());
        if (isInOrders != -1) {
            // this was hardcoded as qty++
            // which meant that if you said "order add Pizza 4"
            // and pizza already was in the order array
            // it would only increase its quantity by 1
            this->items[isInOrders].qty += qty;
        }
        else {
            OrderItem* temp = new OrderItem[this->size + 1];
            for (int i = 0; i < this->size; i++) {
                temp[i] = this->items[i];
            }
            OrderItem tempItem;
            tempItem.item = m;
            // this was hardcoded as 1 instead of qty
            // so if you typed "order add Pizza 4"
            // it always pushed 1 pizza into the order anyway
            tempItem.qty = qty;
            temp[this->size] = tempItem;
            this->size++;
            delete[] this->items;
            this->items = temp;
        }
    }
    int getSize() {
        return this->size;
    }
    void setSize(int newSize) {
        if (newSize < 0 || newSize > this->size) {
            throw new runtime_error("Size must be a positive integer that is not larger than the current size!");
        }
        if (this->items != nullptr) {
            OrderItem* temp = new OrderItem[newSize];
            for (int i = 0; i < newSize; i++) {
                temp[i] = this->items[i];
            }
            delete[] this->items;
            this->items = temp;
            this->size = newSize;
        }
    }
    OrderItem* getItems() {
        return this->items;
    }
    void setItems(int newSize, OrderItem* newItems) {
        if (newSize <= 0) {
            throw new runtime_error("Size must be a positive integer!");
        }
        if (newItems == nullptr) {
            throw new runtime_error("Ingredient array cannot be null!");
        }
        delete[] this->items;
        this->items = new OrderItem[newSize];
        for (int i = 0; i < newSize; i++) {
            this->items[i] = newItems[i];
        }
        this->size = newSize;
    }
};

class Stock {
private:
    Ingredient* ingredients = nullptr;
    int size = 0;
public:   
    Stock() {}
    Stock(Ingredient* ingredients, int size) {
        if (ingredients != nullptr && size > 0) {
            this->size = size;
            this->ingredients = new Ingredient[size];
            for (int i = 0; i < size; i++) {
                this->ingredients[i] = ingredients[i];
            }
        }
        else {
            this->ingredients = nullptr;
            this->size = 0;
        }
    }
    Stock(const Stock& other) {
        if (other.ingredients != nullptr && other.size > 0) {
            this->size = other.size;
            this->ingredients = new Ingredient[other.size];
            for (int i = 0; i < other.size; i++) {
                this->ingredients[i] = other.ingredients[i];
            }
        }
        else {
            this->ingredients = nullptr;
            this->size = 0;
        }
    }
    ~Stock() {
        if (ingredients != nullptr) {
            delete[] ingredients;
        }
    }
    Stock& operator=(Stock& other) {
        if (this != &other) {
            if (ingredients != nullptr) {
                delete[] ingredients;
            }
            if (other.ingredients != nullptr && other.size > 0) {
                this->size = other.size;
                this->ingredients = new Ingredient[other.size];
                for (int i = 0; i < other.size; i++) {
                    this->ingredients[i] = other.ingredients[i];
                }
            }
            else {
                this->ingredients = nullptr;
                this->size = 0;
            }
        }
        return *this;
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
    friend istream& operator>>(istream& in, Stock& s) {
        string buffer;
        cout << "\nNr of ingredients in stock: ";
        in >> buffer;
        try {
            int stockSize = stoi(buffer);
            if (stockSize < 0) {
                throw new runtime_error("Nr of ingredients in stock should be a positive integer!");
            }
            s.size = stockSize;
            delete[] s.ingredients;
            s.ingredients = new Ingredient[stockSize];
            for (int i = 0; i < s.size; i++) {
                Ingredient temp;
                cout << "\nIngredient: ";
                in >> temp;
                s.ingredients[i] = temp;
            }
        }
        catch (invalid_argument) {
            throw runtime_error("Nr of ingredients in stock should be a positive integer!");
        }
        return in;
    }
    Ingredient* getIngredients() {
        return this->ingredients;
    }
    void setIngredients(int newSize, Ingredient* newIngredients) {
        if (newSize <= 0) {
            throw new runtime_error("Size must be a positive integer!");
        }
        if (newIngredients == nullptr) {
            throw new runtime_error("Ingredient array cannot be null!");
        }
        delete[] this->ingredients;
        this->ingredients = new Ingredient[newSize];
        for (int i = 0; i < newSize; i++) {
            this->ingredients[i] = newIngredients[i];
        }
        this->size = newSize;
    }
    int getSize() {
        return this->size;
    }
    void setSize(int newSize) {
        if (newSize <= 0 || newSize > this->size) {
            throw new runtime_error("Size must be a positive integer that is not larger than the current size!");
        }
        if (this->ingredients != nullptr) {
            Ingredient* temp = new Ingredient[newSize];
            for (int i = 0; i < newSize; i++) {
                temp[i] = this->ingredients[i];
            }
            delete[] this->ingredients;
            this->ingredients = temp;
            this->size = newSize;
        }
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
                cout << "\n" << "Currently checking order item: " << order.getItems()[i].item.getName();
                // here we're looping through ingredients

                // check for a match
                // if the ingredient is in the order
                // but it's not in stock -- the order fails
                // if the ingredient is in the order AND in stock
                // and the orderQty (Ingredient.qty * OrderItem.qty) is less than Stock.Ingredient.qty
                // the order goes through
                // fail fallthrough
                bool found = false;
                for (int k = 0; k < this->size; k++) {
                    cout << "\n" << "Currently checking order item ingredient: " << order.getItems()[i].item.getIngredients()[j].getName() << " against " << this->ingredients[k].getName();
                    if (strcmp(order.getItems()[i].item.getIngredients()[j].getName(), this->ingredients[k].getName()) == 0) {
                        found = true;
                        if (order.getItems()[i].item.getIngredients()[j].getQty() * order.getItems()[i].qty <= this->ingredients[k].getQty()) {
                            cout << "\n";
                            cout << "Reducing quantity of " << this->ingredients[k].getName();
                            copy.ingredients[k].setQty(copy.ingredients[k].getQty() - order.getItems()[i].item.getIngredients()[j].getQty() * order.getItems()[i].qty);
                            cout << "\n" << "Reducing qty by " << order.getItems()[i].item.getIngredients()[j].getQty() * order.getItems()[i].qty;
                            cout << "\n";
                            cout << "Quantity was changed to: " << copy.ingredients[k].getQty();

                            
                        }
                        else {
                            cout << "\n" << "Should throw exception\n";
                            string offendingItem = ingredients[k].getName();
                            string message = "\nNot enough stock! " + offendingItem + " is not in stock in the desired quanity\n";
                            throw new runtime_error(message);
                        }
                    }
                }
                if (!found) {
                    string message = "\nWe don't have that ingredient in stock!\n";
                    throw new runtime_error(message);
                }
            }
        }
        return copy;
    }
};

class Parser {
private:
    static string cmdOptions;
    bool running = true;
    const int MAX_COMMANDS = 20;
    int commandCount = 0;
    Menu menuInstance;
    Stock stockInstance;
    Order orderInstance;
public:
    Parser(Menu menu, Stock stock, Order order) {
        this->running = true;
        this->menuInstance = menu;
        this->stockInstance = stock;
        this->orderInstance = order;
    }
    bool isRunning () {
        return running;
    }
    void showCommands() {
        cout << cmdOptions;
    }
    void parseLine() {
        if (commandCount >= MAX_COMMANDS) {
            cout << "\nYou've reached the maximum number of commands! Please leave the restaurant!\n";
            running = false;
            return;
        }
        commandCount++;
        string userInput;
        getline(cin, userInput);
        istringstream iss(userInput);
        // string firstWord = userInput.substr(0, userInput.find(" "));
        string firstWord;
        iss >> firstWord;
        if (firstWord == "help") {
            showCommands();   
        }
        else if (firstWord == "menu") {
            cout << this->menuInstance;
        }
        else if (firstWord == "stock") {
            cout << this->stockInstance;
        }
        else if (firstWord == "quit") {
            running = false;
        }
        else if (firstWord == "order"){
            string secondWord;
            iss >> secondWord;
            if (secondWord == "show") {
                cout << this->orderInstance;
            }
            else if (secondWord == "place") {
                try {
                    Stock copy = this->stockInstance.reduceStock(this->orderInstance);
                    if (this->orderInstance.getItems() != nullptr) {
                        cout << "\nYour order is being prepared!\n";
                        // dangerous line below
                        this->stockInstance = copy;
                        this->orderInstance.emptyOrder();
                    }
                    else {
                        cout << "\nYour order is empty! Please add at least one item before ordering!\n";
                    }
                }
                // this was being caught with & instead of *
                // which caused a runtime error uncaught bug
                catch (runtime_error* e) {
                    cout << e->what();
                    this->orderInstance.emptyOrder();
                }
            }
            else if (secondWord == "empty") {
                cout << "Order was cleared!\n";
                this->orderInstance.emptyOrder();
            }
            else if (secondWord == "add") {
                string itemName;
                string itemQtyAsString;
                // iss >> itemName >> itemQtyAsString;
                cout << "\nWhat is the name of the item you want to order? ";
                getline(cin, itemName);
                cout << "\nHow many would you like? ";
                // consume newline
                getline(cin, itemQtyAsString);
                iss >> itemQtyAsString;
                int menuItemPos = menuInstance.getByName(itemName);
                if (menuItemPos == -1) {
                        cout << "We don't serve that item!\n";
                        return;
                }
                int itemQty;
                try {
                itemQty = stoi(itemQtyAsString);
                    if (itemQty <= 0) {
                        cout << "\nNothing to be added! Try using a positive, integer quantity!\n";
                    }
                    else {
                        cout << "\nYou added " << itemName << " " << itemQty << " times.\n";
                        MenuItem toPush = this->menuInstance.getItems()[menuItemPos];
                        this->orderInstance.push(toPush, itemQty);
                    }
                    
                }
                catch (invalid_argument) {
                    cout << "\nNothing to be added! Try using a positive, integer quantity!\n";
                    itemQty = 0;
                }
            }
        }
    }
};

string Parser::cmdOptions = "\nWelcome!\nYou can look at the menu using \"menu\".\nCheck out our currently available ingredients using \"stock\".\nAdd items to your order with \"order add\".\nSee your current order using \"order show\".\nRemove all items from your current order using \"order empty\".\nPlace your order using \"order place\".\nShow this screen again by typing the \"help\" command.\nYou can leave the restaurant using the \"quit\" command.\n\n";

int main() 
{
    Ingredient i1("flour", 100);
    Ingredient i2("tomatoes", 50);
    Ingredient i4("ham", 60);
    Ingredient i5("cheese", 40);
    Ingredient i6("olives", 15);
    Ingredient i7("pineapple", 10);
    
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

    Ingredient stuff[] = {i1, i2, i4};
    Ingredient stuff2[] = {i1, i2, i5, i6, i7};
    MenuItem m2("Pizza", stuff, 3);
    MenuItem m3("Hawaii", stuff2, 5);
    Menu menu;
    menu.push(m3);
    menu.push(m2);

    Order order;
    order.push(m3, 1);
    order.push(m3, 1);
    order.push(m2, 1);

    Parser parser(menu, stock, order);
    parser.showCommands();
    while (parser.isRunning()) {
        parser.parseLine();
    }

    return 0;
}