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
    cout << "type `help` then press Enter key" << endl;
    string commandLine = "";

    while (true)
    {
        cout << "\nconsole > ";
        getline(cin, commandLine);

        istringstream iss(commandLine);
        vector<string> commands;
        string command = "";

        int rows = 5, cols = 3;
        vector<vector<string>> words(rows, vector<string>(cols));

        while (iss >> command)
        {
            commands.push_back(command);
        }

        int size = commands.size();

        if (size == 2)
        {
            if (commands[0] == "add")
            {
                ofstream writeFile("Locations.txt", ios::app);
                if (writeFile.is_open())
                {
                    writeFile << commands[1] << endl;
                    writeFile.close();
                    cout << "Successfully written in file";
                }
                else
                {
                    cout << "Failed to open a file";
                }
            }
            else if (commands[0] == "list" && commands[1] == "locations")
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
            else
            {
                ifstream readFile("Records.txt");
                if (readFile.is_open())
                {
                    string line = "";

                    int rowIndex = 0;
                    while (getline(readFile, line))
                    {
                        istringstream iss(line);
                        string word = "";
                        int colIndex = 0;
                        while (getline(iss, word, ','))
                        {
                            words[rowIndex][colIndex] = word;
                            colIndex++;
                        }

                        rowIndex++;
                    }

                    if (commands[0] == "list" && commands[1] == "diseases")
                    {
                        for (int i = 0; i < rows; i++)
                        {
                            cout << words[i][1] << endl;
                        }
                    }

                    if (commands[0] == "where")
                    {
                        string disease = commands[1];
                        int flag = 0;
                        for (int i = 0; i < rows; i++)
                        {
                            if (words[i][1] == disease)
                            {
                                flag++;
                                cout << words[i][0] << endl;
                            }
                        }

                        if (flag <= 0)
                        {
                            cout << "No location with this disease" << endl;
                        }
                    }

                    if (commands[0] == "cases")
                    {
                        string disease = commands[1];
                        int cases = 0;
                        for (int i = 0; i < rows; i++)
                        {
                            if (words[i][1] == disease)
                            {
                                int caseNumber = stoi(words[i][2]);
                                cases += caseNumber;
                            }
                        }

                        cout << "Total cases of '" << disease << "' = " << cases << endl;
                    }

                    readFile.close();
                    cout << "Successfully read from file";
                }
                else
                {
                    cout << "Failed to open file for reading" << endl;
                }
            }
        }
        else if (size == 3)
        {
            if (commands[0] == "cases")
            {
                string location = commands[1];
                string disease = commands[2];
                int cases = 0;
                for (int i = 0; i < rows; i++)
                {
                    if (words[i][0] == location && words[i][1] == disease)
                    {
                        int caseNumber = stoi(words[i][2]);
                        cases += caseNumber;
                    }
                }

                cout << "Total cases of " << disease << " at " << location << " are: " << cases << endl;
            }
        }
        else if (size == 4)
        {
            if (commands[0] == "record")
            {
                ofstream writeFile("Records.txt", ios::app);
                if (writeFile.is_open())
                {
                    writeFile << commands[1] << "," << commands[2] << "," << commands[3] << endl;
                    writeFile.close();
                    cout << "Successfully written in file";
                }
                else
                {
                    cout << "Failed to open a file";
                }
            }
        }
        else if (command == "delete")
        {
            cout << "Choose to delete";
        }
        else if (command == "help")
        {
            cout << "=============================================================================================" << endl;
            cout << "\t\t\t\t\t HELP MENU" << endl;
            cout << "=============================================================================================" << endl;
            cout << "add <location> \t\t\t\t\t To add a location" << endl;
            cout << "record <locations> <disease> <cases> \t\t To record a new disease record" << endl;
            cout << "list locations \t\t\t\t\t To view all existing locations" << endl;
            cout << "list diseases \t\t\t\t\t To view all recorded diseases" << endl;
            cout << "where <disease> \t\t\t\t Find where disease exists" << endl;
            cout << "cases <disease> \t\t\t\t Find cases of a disease in a location" << endl;
            cout << "cases <location> <disease> \t\t\t Find total cases of a disease " << endl;
            cout << "delete <location> \t\t\t\t To delete existing location" << endl;
            cout << "clear \t\t\t\t\t\t To clear the terminal" << endl;
            cout << "exit \t\t\t\t\t\t To exit" << endl;
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