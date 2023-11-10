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
    int nameLength = 0;
    int qty = 0;
public:
    Ingredient() {};
    Ingredient (const char* name, int qty) {
        if (name != nullptr) {
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
            this->nameLength = strlen(name);
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

    friend ostream& operator<<(ostream& ost, Ingredient& ing) {
        ost << "\n----------\n";
        ost << "Ingredient " << ing.name << ". Kilos in stock: " << ing.qty;
        ost << "\n----------\n";
        return ost;
    }
};

class Order {};

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