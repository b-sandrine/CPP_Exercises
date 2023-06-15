#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;
#define CLEAR_COMMAND "clear"

int main()
{
    cout << "\t\t\t\t ********************* WELCOME TO HR SYSTEM *********************" << endl
         << endl;
    cout << "type `help` to see all commands available" << endl;
    string commandLine = "";

    while (true)
    {
        cout << "\nconsole > ";
        getline(cin, commandLine);

        istringstream iss(commandLine);
        vector<string> commands;
        string command = "";

        while (iss >> command)
        {
            if (command == "add")

            {
                ofstream writeFile("Locations.txt", ios::app);

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
            }
            else if (command == "record")
            {
                ofstream writeFile("Locations.txt", ios::app);
                string disease = "";
                cout << "Enter a new disease: ";
                cin >> disease;
                writeFile << disease << endl;
                writeFile.close();
                cout << "Successfully written in file";
            }
            else if (command == "list")
            {
                ifstream readFile("Locations.txt");
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
            else if (command == "clear")
            {
                system("clear");
            }
            else
            {
                cout << "Invalid command";
            }
        }
    }
}