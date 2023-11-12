#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// STUFF THAT WORKS
// - parsing the first letter of user input
// 
// WHAT NEEDS TO WORK
// - command line tool to add a menu item to the current order (with quanity)
// - create a MenuItem using Ingredients
// - push a MenuItem to the Menu
// - check if a string matches the name of a MenuItem in the Menu (used for the Order)
// - print the Order
// - add stuff to the Order



class Ingredient {
private:
    char* name = nullptr;
    int qty = 0;
public:
    Ingredient() {};
    Ingredient (const char* name, int qty) {
        if (name != nullptr) {
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
        }
        if (qty > 0) this->qty = qty;
    }
    Ingredient(const Ingredient& other) {
        if (this != &other) {
            if (other.name != nullptr && strlen(other.name) > 0) {
                this->name = new char[strlen(other.name) + 1];
                strcpy(this->name, other.name);
            }
            this->qty = other.qty;
        }
    }
    Ingredient& operator=(const Ingredient& other) {
        if (this != &other) {
            if (other.name != nullptr && strlen(other.name) > 0)
            delete[] this->name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
        this->qty = other.qty;
        return *this;
    }
    ~Ingredient() {
        // you don't need to do this for char arrays I guess?
        // leaving this in gets me a double free error for some reason

        // if (this->name != nullptr) {
        //     delete[] this->name;
        // }
    }
    const char* getName() {
        return this->name;
    }
    int getQty() {
        return this->qty;
    }
    
    void setQty(int newQty) {
        if (newQty > 0) {
            this->qty = newQty;
        }
        // throw something about negative quanitites here
        else throw new exception;
    }

    friend ostream& operator<<(ostream& ost, Ingredient& ing) {
        ost << "\n----------\n";
        ost << "Ingredient " << ing.name << ". Kilos in stock: " << ing.qty;
        ost << "\n----------\n";
        return ost;
    }
};

class MenuItem {
private:
    string menuItemName = "";
    Ingredient* ingredientsNeeded = nullptr;
    int ingredientsNeededLen = 0;
public:
    MenuItem() {}
    MenuItem(string name, Ingredient* ingNeeded, int ingNeededLen) {
        if (name != "" && name.size() > 0) {
            this->menuItemName = name;
        }
        if (ingNeeded != nullptr && ingNeededLen > 0) {
            this->ingredientsNeeded = new Ingredient[ingNeededLen];
            this->ingredientsNeededLen = ingNeededLen;
            for (int i = 0; i < this->ingredientsNeededLen; i++) {
                this->ingredientsNeeded[i] = ingNeeded[i];
            }
        }
    }
    MenuItem(const MenuItem& menuItm) {
        if (menuItm.menuItemName != "" && menuItm.menuItemName.size() > 0) {
            this->menuItemName = menuItm.menuItemName;
        }
        if (menuItm.ingredientsNeeded != nullptr && menuItm.ingredientsNeededLen > 0) {
            this->ingredientsNeededLen = menuItm.ingredientsNeededLen;
            this->ingredientsNeeded = new Ingredient[this->ingredientsNeededLen];
            for (int i = 0; i < this->ingredientsNeededLen; i++) {
                this->ingredientsNeeded[i] = menuItm.ingredientsNeeded[i];
            }
        }
    }
    MenuItem& operator= (const MenuItem& other) {
        if (this != &other) {
            delete[] this->ingredientsNeeded;
            this->ingredientsNeededLen = other.ingredientsNeededLen;
            this->ingredientsNeeded = new Ingredient[this->ingredientsNeededLen];
            for (int i = 0; i < this->ingredientsNeededLen; i++) {
                this->ingredientsNeeded[i] = other.ingredientsNeeded[i];
            }
        }
        return *this;
    }
    ~MenuItem() {
        if (this->ingredientsNeeded != nullptr && this->ingredientsNeededLen > 0) {
            delete[] this->ingredientsNeeded;
        }
    }
    string getMenuItemName() {
        return this->menuItemName;
    }
    friend ostream& operator<<(ostream& ost, MenuItem mi) {
        if (mi.menuItemName != "") {
            ost << mi.menuItemName << "\n";
        }
        else {
            ost << "This menu item doesn't seem to have a name yet!\n";
        }
        return ost;
    }

};

class Menu {
private:
    MenuItem* menuItems = nullptr;
    int menuLength = 0;
public:
    Menu() {}
    Menu(const Menu& other) {
        if (other.menuItems != nullptr && other.menuLength > 0) {
            delete[] this->menuItems;
            this->menuItems = nullptr;
            this->menuLength = other.menuLength;
            this->menuItems = new MenuItem[this->menuLength];
            for (int i = 0; i < this->menuLength; i++) {
                this->menuItems[i] = other.menuItems[i];
            }
        }
    }
    ~Menu() {
        if (menuItems != nullptr && menuLength > 0) {
            delete[] menuItems;
        }
    }
    friend ostream& operator<<(ostream& ost, Menu menu){
        if (menu.menuItems != nullptr && menu.menuLength != 0) {
            ost << "Our menu includes:\n";
            for (int i = 0; i < menu.menuLength; i++) {
                ost << "-----\n" << menu.menuItems[i] << "-----\n";
            }
        }
        else {
            ost << "\n-----" << "\nThere doesn't seem to be anything on the menu just yet!\n-----\n";
        }
        return ost;
    }
    int getMenuLen() {
        return this->menuLength;
    }
    // const MenuItem*& getMenu() {
    // }
    // strange error here if string isn't ::'d to std
    bool isInMenu(std::string itemName) {
        if (this->menuItems == nullptr || this->menuLength == 0) return false;
        else {
            for (int i = 0; i < this->menuLength; i++) {
                if (this->menuItems[i].getMenuItemName() == itemName) {
                    return true;
                }
            }
            return false;
        }
    }
    void push(MenuItem mit) {
        if (this->isInMenu(mit.getMenuItemName())) return;
        MenuItem* newMenuItems = new MenuItem[this->menuLength + 1];
        
        for (int i = 0; i < this->menuLength; i++) {
            //TODO: need a copy constructor for pretty much everything
            newMenuItems[i] = this->menuItems[i];
        }
        newMenuItems[this->menuLength] = mit;
        this->menuLength++;
        delete[] this->menuItems;
        this->menuItems = newMenuItems;
        newMenuItems = nullptr;
    }
};

class Stock {
private:
    Ingredient* ingredients = nullptr;
    int ingredientsLen = 0;
public:
    Stock() {
        this->ingredients = nullptr;
        this->ingredientsLen = 0;
    }
    Stock(const Stock& other) {
        if (other.ingredients != nullptr && other.ingredientsLen > 0) {
            delete[] this->ingredients;
            this->ingredientsLen = other.ingredientsLen;
            this->ingredients = new Ingredient[ingredientsLen];
            for (int i = 0; i < this->ingredientsLen; i++) {
                this->ingredients[i] = other.ingredients[i];
            }
        }
    }
    ~Stock() {
        if (this->ingredients != nullptr) {
            delete[] ingredients;
        }
    }
    void push(Ingredient ing) {
        // check by name if the element is already present in the list
        if (this->ingredients != nullptr && this->ingredientsLen != 0) {
            for (int i = 0; i < this->ingredientsLen; i++) {
                if (strcmp(this->ingredients[i].getName(), ing.getName()) == 0) {
                    //if yes, add the qty to the already existing qty
                    this->ingredients[i].setQty(this->ingredients[i].getQty() + ing.getQty());
                    // then return
                    return;
                }
            }
        }
        // if the element is not present in the array, we push it onto the array
        Ingredient* newIng = new Ingredient[this->ingredientsLen + 1];
        for (int i = 0; i < this->ingredientsLen; i++) {
            newIng[i] = this->ingredients[i];
        }
        newIng[ingredientsLen] = ing;
        this->ingredientsLen++;
        delete[] this->ingredients;
        this->ingredients = newIng;
        newIng = nullptr;
    }
    friend ostream& operator<<(ostream& ost, Stock& stock) {
        ost << "\n";
        ost << "Current stocks are:\n";
        for (int i = 0; i < stock.ingredientsLen; i++) {
            ost << stock.ingredients[i] << " ";
        }
        ost << "\n";
        return ost;
    }
};

class Order {
private:
    MenuItem* currentlyOrdered = nullptr;
    int currentOrderLen = 0;
public:
    void addToOrder(MenuItem menuItem, int itemQty) {
        // user input needs to be sanitized
        // qty should not be negative
        // the name of the item should be in the menu
        MenuItem* newOrder = new MenuItem[currentOrderLen + 1];
        for (int i = 0; i < currentOrderLen; i++) {
            newOrder[i] = currentlyOrdered[i];
        }
        newOrder[currentOrderLen] = menuItem;
    }
};

class Parser {
private:
    static string cmdOptions;
    bool running = true;
    // cheap trick to add a dynamically allocated field in this class too
    // not implemented yet, will be pretty useless even when it's done 
    std::string* commandHistory = nullptr;
    int commandHistoryLen = 0;
    int MAX_HISTORY = 100;
    Menu menuInstance;
    Stock stockInstance;
public:
    Parser(Menu menu, Stock stock) {
        this->commandHistory = nullptr;
        this->commandHistoryLen = 0;
        this->running = true;
        this->menuInstance = menu;
        this->stockInstance = stock;
    }
    ~Parser () {}
    bool isRunning () {return running;}
    void showMenu() {
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
            showMenu();   
        }
        else if (firstWord == "stock") {
            // print stocks here
        }
        else if (firstWord == "quit") {
            running = false;
        }
        else if (firstWord == "order"){
            string secondWord;
            iss >> secondWord;
            if (secondWord == "show") {
                // print order here
            }
            else if (secondWord == "place") {
                // place the order here
            }
            else if (secondWord == "add") {
                string itemName;
                string itemQtyAsString;
                iss >> itemName >> itemQtyAsString;
                if (!menuInstance.isInMenu(itemName)) {
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

string Parser::cmdOptions = "\nWelcome!\nYou can look at the menu using \"menu\".\nCheck out our currently available ingredients using \"stock\".\nAdd items to your order with \"order add <item name> <item quanitity>\".\nSee your current order using \"order show\".\nPlace your order using \"order place\".\nShow this screen again by typing the \"help\" command.\nYou can leave the restaurant using the \"quit\" command.\n\n";

int main() 
{
    
    Ingredient tomato("Tomato", 10);
    Ingredient cheese("Cheese", 15);
    Ingredient dough("Dough", 20);
    Ingredient mushrooms("Mushrooms", 5);
    Ingredient ham("Ham", 25);
    Ingredient olives("Olives", 10);
    cout << tomato << " " << cheese << " " << dough;
    Stock stock;
    stock.push(tomato);
    stock.push(cheese);
    stock.push(dough);
    cout << stock;
    stock.push(tomato);
    Ingredient dough2("Dough", 100);
    stock.push(dough2);
    Ingredient marghNeeded[] = {tomato, cheese, dough};
    Ingredient qStagioni[] = {tomato, cheese, dough, ham, mushrooms, olives};
    MenuItem margherita("Margherita", marghNeeded, 3);
    MenuItem quattroStagioni("Quattro", qStagioni, 6);
    MenuItem test = quattroStagioni;
    cout << stock;
    cout << "\nMargherita Menu Item:\n";
    cout << margherita;
    cout << "\nQuattro Stagioni Menu Item:\n";
    cout << quattroStagioni;

    Menu menu;
    cout << menu;
    menu.push(margherita);
    menu.push(quattroStagioni);
    cout << menu;
    menu.push(margherita);
    cout << menu;

    Parser cmdLineParser(menu, stock);
    cmdLineParser.showMenu();
    while (cmdLineParser.isRunning()) {
        cmdLineParser.parseLine();
    }
    return 0;
}