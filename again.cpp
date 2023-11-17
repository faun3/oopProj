#include <iostream>
#include <sstream> // for istringstream -- might not be needed
using namespace std;

// TODO:
// TODO:
// Reimplement Parser as a controller class
// Think of a solution for parsing multi-word named menu items from user input



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
        
        // this is untested, don't push it 
        // TODO: add istream overloads to every single class
        // TODO: make all istream overloads revert back to default values if user input is invalid
        // example: is >> i.qty; if (i.qty < 0) { i.qty = 0; }
        
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
            // FIXME: copy constructors do not need to free any dynamically allocated memory
            // FIXME: check all copy constructors and remove any calls to delete[]
            // FIXME: we don't really need to delete[] anything because we are just now creating the object by copy
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
    // FIXME:
    // this assignment operator was broken
    // it didn't return anything and it didn't check for self assignment
    Menu& operator=(const Menu& other) {
        if (this != &other) {
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
    MenuItem* getItems() {
        return this->items;
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
    Stock& operator=(Stock& other) {
        if (this != &other) {
            if (other.ingredients != nullptr && other.size > 0) {
                delete[] this->ingredients;
                this->size = other.size;
                this->ingredients = new Ingredient[this->size];
                for (int i = 0; i < this->size; i++) {
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
                cout << "\n" << "Currently checking order item: " << order.getItems()[i].item.getName();
                // here we're looping through ingredients

                // check for a match
                // if the ingredient is in the order
                // but it's not in stock -- the order fails
                // if the ingredient is in the order AND in stock
                // and the orderQty (Ingredient.qty * OrderItem.qty) is less than Stock.Ingredient.qty
                // the order goes through
                // fail fallthrough
                for (int k = 0; k < this->size; k++) {
                    cout << "\n" << "Currently checking order item ingredient: " << order.getItems()[i].item.getIngredients()[j].getName() << " against " << this->ingredients[k].getName();
                    if (strcmp(order.getItems()[i].item.getIngredients()[j].getName(), this->ingredients[k].getName()) == 0) {
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
            }
        }
        return copy;
    }
};

class Parser {
private:
    static string cmdOptions;
    bool running = true;
    // cheap trick to add a dynamically allocated field in this class too
    // not implemented yet, will be pretty useless even when it's done 
    // string* commandHistory = nullptr;
    // int commandHistoryLen = 0;
    const int MAX_HISTORY = 100;
    Menu menuInstance;
    Stock stockInstance;
    Order orderInstance;
public:
    Parser(Menu menu, Stock stock, Order order) {
        // this->commandHistory = nullptr;
        // this->commandHistoryLen = 0;
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

string Parser::cmdOptions = "\nWelcome!\nYou can look at the menu using \"menu\".\nCheck out our currently available ingredients using \"stock\".\nAdd items to your order with \"order add <item name> <item quanitity>\".\nSee your current order using \"order show\".\nRemove all items from your current order using \"order empty\".\nPlace your order using \"order place\".\nShow this screen again by typing the \"help\" command.\nYou can leave the restaurant using the \"quit\" command.\n\n";

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
    // cout << stock;

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
    // cout << menu;

    Order order;
    order.push(m3, 1);
    order.push(m3, 1);
    order.push(m2, 1);
    // cout << order;

    // removing the ingredients works, copying into stock doesn't 
    // cout << stock;
    
    // cout << "\n";
    // cout << order.getItems()[0].item.getIngredients()[0].getName();
    // cout << "\n";

    // cout << stock.getIngredients()[0].getName();
    // cout << "\n";

    // if (strcmp(order.getItems()[0].item.getIngredients()[0].getName(), stock.getIngredients()[0].getName()) == 0) {
    //     cout << "\nThey're equal";
    // }
                            

    // cout << order.getItems()[0].item.getIngredients()[0].getQty();
    // cout << "\n";

    // cout << order.getItems()[0].qty;
    // cout << "\n";
    
    // stock.getIngredients()[0].setQty(stock.getIngredients()[0].getQty() - order.getItems()[0].item.getIngredients()[0].getQty() * order.getItems()[0].qty);

    // cout << stock.getIngredients()[0].getQty();
    // cout << "\n";

    // Stock newStock = stock.reduceStock(order);
    // cout << "\n";
    // cout << newStock;
    // cout << "\n";

    Parser parser(menu, stock, order);
    parser.showCommands();
    while (parser.isRunning()) {
        parser.parseLine();
    }

    Ingredient finTest;
    cin >> finTest;
    cout << finTest;

    return 0;
}