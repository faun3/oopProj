#include <iostream>
using namespace std;

class Parser {
private:
    static string cmdOptions;
public:
    void showMenu() {
        cout << cmdOptions;
    }
};

class Ingredient {};

class Order {};

string Parser::cmdOptions = "\nWelcome!\nYou can look at the menu using \"menu\".\nCheck out our currently available ingredients using \"stock\".\nAdd items to your order with \"order add <item name> <item quanitity>\".\nSee your current order using \"order show\".\nShow this screen again by typing the \"help\" command.\n\n";

int main() 
{
    Parser cmdLineParser;
    cmdLineParser.showMenu();
    return 0;
}