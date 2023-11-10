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

class Ingredient {};

class Order {};

string Parser::cmdOptions = "\nWelcome!\nYou can look at the menu using \"menu\".\nCheck out our currently available ingredients using \"stock\".\nAdd items to your order with \"order add <item name> <item quanitity>\".\nSee your current order using \"order show\".\nShow this screen again by typing the \"help\" command.\nYou can leave the restaurant using the \"quit\" command.\n\n";

int main() 
{
    Parser cmdLineParser;
    cmdLineParser.showMenu();
    while (cmdLineParser.isRunning()) {
        cmdLineParser.parseLine();
    }
    return 0;
}