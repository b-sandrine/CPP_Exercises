#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
#define CLEAR_COMMAND "clear"

const string LOCATIONS_FILE = "Locations.txt";
const string RECORDS_FILE = "Records.txt";

void addData(string filename, string data)
{
    ofstream file;
    file.open(filename, ios::app);
    if (file.is_open())
    {
        file << data << endl;
        file.close();
        cout << "Data written successfully";
    }
    else
    {
        cout << "Failed to open file";
    }
    return;
}

void readData(string filename)
{
    ifstream file(filename);

    if (file.is_open())
    {
        string line = "";
        int index = 0;
        vector<string> locations;

        while (getline(file, line))
        {
            locations.push_back(line);
        }
        file.close();
        sort(locations.begin(), locations.end());

        for(const string& location: locations) {
            cout << location <<endl;
        }
        cout << "Successfully read from file";
    }
    else
    {
        cout << "Failed to read from file";
    }

    return;
}

void printHelp()
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

void handleAddCommand(const vector<string> &commands)
{
    if (commands.size() != 2)
    {
        cout << "Invalid number of arguments for 'add' command" << endl;
        return;
    }

    addData(LOCATIONS_FILE, commands[1]);
}

void handleListLocationsCommand()
{
    readData(LOCATIONS_FILE);
}

void handleListDiseaseCommand()
{
    ifstream file(RECORDS_FILE);

    if (file.is_open())
    {
        string line = "";
        int index = 0;
        vector<string> locations;

        while (getline(file, line))
        {
            istringstream iss(line);
            string recLocation, recDisease, recCases;
            while(getline(iss,recLocation,(',')) && getline(iss,recDisease,',')) {
                cout << ++index << ". " << recDisease << endl;
            } 
        }
        file.close();
        cout << "Successfully read from file";
    }
    else
    {
        cout << "Failed to read from file";
    }

}

void handleWhereCommand(const vector<string> &commands)
{
    if (commands.size() != 2)
    {
        cout << "Invalid number of arguments for 'where' command" << endl;
        return;
    }

    ifstream readFile(RECORDS_FILE);
    if (readFile.is_open())
    {
        string line;
        int flag = 0;
        while (getline(readFile, line))
        {
            istringstream iss(line);
            string location, disease;
            if (getline(iss, location, ',') && getline(iss, disease, ','))
            {
                if (disease == commands[1])
                {
                    flag++;
                    cout << location << endl;
                }
            }
        }

        if (flag == 0)
        {
            cout << "No locations with this disease" << endl;
        }

        readFile.close();
        cout << "Successfully read from file" << endl;
    }
    else
    {
        cout << "Failed to open fil for reading" << endl;
    }
}

void handleCasesCommand(const vector<string> &commands)
{
    if (commands.size() < 2)
    {
        cout << "Invalid number of arguments for 'cases' command" << endl;
        return;
    }

    ifstream readFile(RECORDS_FILE);
    if (readFile.is_open())
    {
        string line;
        string location = (commands.size() == 3) ? commands[1] : "";
        string disease = commands.back();
        int cases = 0;
        while (getline(readFile, line))
        {
            istringstream iss(line);
            string recLocation, recDisease, recCasesStr;
            if (getline(iss, recLocation, ',') && getline(iss, recDisease, ',') && getline(iss, recCasesStr, ','))
            {
                if(location == "") {
                    if(recDisease == disease) {
                        cases += stoi(recCasesStr); 
                    }
                }
                else {
                    if(recLocation == location && recDisease == disease) {
                        cases += stoi(recCasesStr); 
                    }
                }
            }
        }

        cout << "Total cases of '" << disease << "' = " << cases << endl;
        readFile.close();
        cout << "Successfully read from file" << endl;
    }
    else
    {
        cout << "Failed to open file for reading" << endl;
    }
}

void handleRecordCommand(const vector<string> &commands)
{
    if (commands.size() != 4)
    {
        cout << "Invalid number of arguments for 'record' command" << endl;
        return;
    }

    ofstream writeFile("Records.txt", ios::app);
    if (writeFile.is_open())
    {
        string location = commands[1];
        string disease = commands[2];
        string cases = commands[3];

        writeFile << location << "," << disease << "," << cases << endl;
        writeFile.close();
        cout << "Successfully recorded data" << endl;
    }
    else
    {
        cout << "Failed to record data" << endl;
    }
}

void handleDeleteCommand(const vector<string> &commands)
{
    if (commands.size() != 2)
    {
        cout << "Invalid number of arguments for 'delete' command" << endl;
        return;
    }

    ifstream readFile(RECORDS_FILE);
    if (readFile.is_open())
    {
        string line;
        string location = commands[1];
        vector<string> records;

        while (getline(readFile, line))
        {
            istringstream iss(line);
            string recLocation;
            getline(iss, recLocation, ',');
            if (recLocation != location)
            {
                records.push_back(line);
            }
        }

        readFile.close();

        ofstream writeFile(RECORDS_FILE);

        if(writeFile.is_open()) {
            for(const auto& record: records) {
                writeFile << record << endl;
            }

            writeFile.close();
            cout << "Records successfully deleted" << endl;
        }
        else {
            cout << "Failed to open file for updating records" << endl;
        }
    }
    else {
        cout << "Failed to delete record" <<endl;
    }
}

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

        while (iss >> command)
        {
            commands.push_back(command);
        }

        if (commands.empty())
        {
            continue;
        }

        if (commands[0] == "add")
        {
            handleAddCommand(commands);
        }
        else if (commands[0] == "list")
        {
            if (commands.size() == 2)
            {
                if (commands[1] == "locations")
                {
                    handleListLocationsCommand();
                }
                else if (commands[1] == "diseases")
                {
                    handleListDiseaseCommand();
                }
                else
                {
                    cout << "Invalid command " << commandLine << endl;
                }
            }
        }
        else if (commands[0] == "record")
        {
            handleRecordCommand(commands);
        }
        else if(commands[0] == "delete") 
        {
            handleDeleteCommand(commands);
        }
        else if (commands[0] == "where")
        {
            handleWhereCommand(commands);
        }
        else if (commands[0] == "cases")
        {
            handleCasesCommand(commands);
        }
        else if (commands[0] == "help")
        {
            printHelp();
        }
        else if (commands[0] == "exit")
        {
            break;
        }
        else if (commands[0] == "clear")
        {
            system("clear");
        }
        else
        {
            cout << "Invalid command: " << commandLine << endl;
        }
    }
    return 0;
}