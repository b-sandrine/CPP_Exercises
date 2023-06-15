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
                    int rows = 5, cols = 3;
                    vector<vector<string>> words(rows, vector<string>(cols));

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

                    if(commands[0] == "where") {
                        string disease = commands[1];
                        int flag = 0;
                        for(int i = 0; i< rows; i ++) {
                            if(words[i][1] == disease) {
                                flag ++;
                                cout << words[i][0] << endl;
                            }
                        }

                        if(flag <= 0) {
                            cout << "No location with this disease"<<endl;
                        }
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
    }
}