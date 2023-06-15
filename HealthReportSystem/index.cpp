#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    cout << "\t\t\t\t ********************* WELCOME TO HR SYSTEM *********************" << endl
         << endl;
    cout << "type `help` to see all commands available" << endl;
    string command = "";

    while (true)
    {
        cout << "\nconsole > ";
        cin >> command;
        if (command == "add")
        {
            int choice = 0;
            cout << "All operations to perform \n\t 1. Add new location \n\t 2. View all locations\n";
            cout << "Enter your choice: ";
            cin >> choice;
            ofstream writeFile("Locations.txt", ios::app);
            ifstream readFile("Locations.txt");

            switch (choice)
            {
            case 1:
                if (writeFile.is_open())
                {
                    string location = "";
                    cout << "Enter a new location: ";
                    cin >> location;
                    writeFile << location << endl;
                    writeFile.close();
                    cout << "Successfully written in file";
                }
                else
                {
                    cout << "Failed to open a file";
                }
                break;

            case 2:
                if (readFile.is_open())
                {
                    string line = "";
                    int index = 0;
                    while (getline(readFile, line))
                    {
                        cout << ++index << ". " << line << endl;
                    }
                    readFile.close();
                    cout << "Successfully read from file";
                }
                else
                {
                    cout << "Failed to open file for reading" << endl;
                }
                break;

            default:
                cout << "Invalid choice";
                break;
            }
        }
        else if (command == "record")
        {
            cout << "Choose to record";
        }
        else if (command == "list")
        {
            cout << "Choose to list";
        }
        else if (command == "delete")
        {
            cout << "Choose to delete";
        }
        else if (command == "help")
        {
            cout << "add \t\t To add a location" << endl;
            cout << "record \t\t To record a new disease record" << endl;
            cout << "list \t\t To view all existing locations" << endl;
            cout << "delete \t\t To delete existing location" << endl;
            cout << "exit \t\t To exit" << endl;
        }
        else if (command == "exit")
        {
            exit(0);
        }
        else
        {
            cout << "Invalid command";
        }
    }
}