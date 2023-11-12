#include <iostream>
using namespace std;

class Parser {
private:
    static string cmdOptions;
    bool running = true;
public:
    bool isRunning () {return running;}
    void showMenu() {
        cout << cmdOptions;
    }
    void parseLine() {
        string userInput;
        getline(cin, userInput);
        string firstWord = userInput.substr(0, userInput.find(" "));
        if (firstWord == "help") {
            showMenu();   
        }
        else if (firstWord == "quit") {
            running = false;
        }
        // cout << "\n" << firstWord << '\n';
    }
};

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
    ~Ingredient() {
        if (this->name != nullptr) {
            delete[] this->name;
        }
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
    char* menuItemName = nullptr;
    Ingredient* ingredientsNeeded = nullptr;
    int ingredientsNeededLen = 0;
public:
    MenuItem() {}
    MenuItem(char* name, Ingredient* ingNeeded, int ingNeededLen) {
        this->menuItemName = new char[strlen(name) + 1];
        strcpy(this->menuItemName, name);
        if (ingNeeded != nullptr && ingNeededLen > 0) {
            this->ingredientsNeeded = new Ingredient[ingNeededLen];
            this->ingredientsNeededLen = ingNeededLen;
            for (int i = 0; i < this->ingredientsNeededLen; i++) {
                this->ingredientsNeeded[i] = ingNeeded[i];
            }
        }
    }
    MenuItem(const MenuItem& menuItm) {
        if (menuItm.menuItemName != nullptr) {
            this->menuItemName = new char[strlen(menuItm.menuItemName) + 1];
            strcpy(this->menuItemName, menuItm.menuItemName);
        }
        if (menuItm.ingredientsNeeded != nullptr && menuItm.ingredientsNeededLen > 0) {
            this->ingredientsNeededLen = menuItm.ingredientsNeededLen;
            this->ingredientsNeeded = new Ingredient[this->ingredientsNeededLen];
            for (int i = 0; i < this->ingredientsNeededLen; i++) {
                this->ingredientsNeeded[i] = menuItm.ingredientsNeeded[i];
            }
        }
    }
    void printItemAndNecessaries() {}
    friend ostream& operator<<(ostream& ost, MenuItem mi) {
        if (mi.menuItemName != nullptr) {
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
    friend ostream& operator<<(ostream& ost, Menu menu){
        if (menu.menuItems != nullptr && menu.menuLength != 0) {
            for (int i = 0; i < menu.menuLength; i++) {
                ost << "\n-----\n" << menu.menuItems[i] << "\n-----\n";
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
    const MenuItem*& getMenu() {
    }
    bool isInMenu(string itemName) {
        if (this->menuItems == nullptr) return false;
        else {

        }
    }
};

class Stock {
private:
    Ingredient* ingredients = nullptr;
    int ingredientsLen = 0;
public:
    void push(Ingredient ing) {
        if (this->ingredients != nullptr && this->ingredientsLen != 0) {
            for (int i = 0; i < this->ingredientsLen; i++) {
                if (strcmp(this->ingredients[i].getName(), ing.getName()) == 0) {
                    this->ingredients[i].
                }
            }
        }
        Ingredient* newIng = new Ingredient[ingredientsLen + 1];
        for (int i = 0; i < ingredientsLen; i++) {
            newIng[i] = this->ingredients[i];
        }
        newIng[ingredientsLen] = ing;
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

string Parser::cmdOptions = "\nWelcome!\nYou can look at the menu using \"menu\".\nCheck out our currently available ingredients using \"stock\".\nAdd items to your order with \"order add <item name> <item quanitity>\".\nSee your current order using \"order show\".\nShow this screen again by typing the \"help\" command.\nYou can leave the restaurant using the \"quit\" command.\n\n";

int main() 
{
    Parser cmdLineParser;
    cmdLineParser.showMenu();
    while (cmdLineParser.isRunning()) {
        cmdLineParser.parseLine();
    }
    Ingredient tomato("Tomato", 10);
    cout << tomato;
    return 0;
}