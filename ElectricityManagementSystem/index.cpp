#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <random>
#include <variant>

using namespace std;

void printHelp()
{
    cout << "add \t\t\t\t\t To create a new user account" << endl;
    cout << "buy \t\t\t\t\t To Buy electricity" << endl;
    cout << "exit \t\t\t\t\t To terminate the program" << endl;
}

string generateToken(int length)
{
    string token;
    static const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, sizeof(charset) - 2);

    for (int i = 0; i < length; ++i)
    {
        token += charset[distribution(generator)];
    }

    return token;
}

vector<string> searchForUser(string names)
{
    ifstream readFile("userData.txt");
    vector<string>  userData;
    if (readFile.is_open())
    {
        string line;
        while (getline(readFile, line))
        {
            istringstream iss(line);
            string recNames, recCategory;
            int recCashPowerNumber;

            getline(iss, recNames, ',');
            getline(iss, recCategory, ',');
            iss >> recCashPowerNumber;

            string strCashPowerNumber = string(to_string(recCashPowerNumber));

            if (recNames == names)
            {
                readFile.close();
                userData.push_back(recNames);
                userData.push_back(recCategory);
                userData.push_back(strCashPowerNumber);
            }
            else
            {
                cout << "User not found" << endl;
            }
        }
        cout << "Successfully read from file" << endl;
    }
    else
    {
        cout << "Failed to open file" << endl;
    }

    readFile.close();
    return userData;
}

int main()
{
    cout << "\t\t\t *****************  Welcome to the Electricity Management Application  *****************" << endl;
    cout << "\t\t*****************************************************************************************************" << endl
         << endl;
    cout << "type 'help' to view all available commands" << endl;
    string command;

    while (true)
    {
        cout << "Enter your command: ";
        cin >> command;

        cin.ignore();
        if (command == "add")
        {
            string names, category, cashPowerNumber;
            ofstream writeFile("userData.txt",ios::app);
            if (writeFile.is_open())
            {
                cout << "Enter names: ";
                getline(cin, names);
                cout << "Enter Category: ";
                getline(cin, category);
                cout << "Enter Cash Power Number: ";
                getline(cin, cashPowerNumber);

                writeFile << names << "," << category << "," << cashPowerNumber << endl;
                cout << "Successfully saved the records";
            }
        }
        else if (command == "help")
        {
            printHelp();
        }
        else if (command == "exit")
        {
            break;
        }
        else if (command == "buy")
        {
            string names;
            string money;
            string token = generateToken(30);
            cout << "Enter your names: ";
            getline(cin, names);
            cout << "Enter amount of money:  ";
            getline(cin, money);

            vector<string> userData = searchForUser(names);

            for(const auto& var: userData) {
                cout << var << endl;
            }
        }
        else
        {
            cout << "Invalid command. Please try again." << endl;
        }
    }
    return 0;
}