#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 4
#define CLEAR_COMMAND "clear"
#define MAX_RECORDS 50
const char* LOCATIONS_FILE = "Locations.txt";
const char* RECORDS_FILE = "Records.txt";

void addData(const char* filename, const char* data) {
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", data);
        fclose(file);
        printf("Data written successfully\n");
    } else {
        printf("Failed to open file\n");
    }
}

void readData(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[100];
        int index = 0;
        char locations[100][100];
        int numLocations = 0;

        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0'; // Remove newline character
            strcpy(locations[numLocations++], line);
        }
        fclose(file);

        // Sort the locations
        for (int i = 0; i < numLocations - 1; i++) {
            for (int j = i + 1; j < numLocations; j++) {
                if (strcmp(locations[i], locations[j]) > 0) {
                    char temp[100];
                    strcpy(temp, locations[i]);
                    strcpy(locations[i], locations[j]);
                    strcpy(locations[j], temp);
                }
            }
        }

        // Print the sorted locations
        for (int i = 0; i < numLocations; i++) {
            printf("%s\n", locations[i]);
        }

        printf("Successfully read from file\n");
    } else {
        printf("Failed to read from file\n");
    }
}

void printHelp() {
    printf("=============================================================================================\n");
    printf("\t\t\t\t\t HELP MENU\n");
    printf("=============================================================================================\n");
    printf("add <location> \t\t\t\t\t To add a location\n");
    printf("record <locations> <disease> <cases> \t\t To record a new disease record\n");
    printf("list locations \t\t\t\t\t To view all existing locations\n");
    printf("list diseases \t\t\t\t\t To view all recorded diseases\n");
    printf("where <disease> \t\t\t\t Find where disease exists\n");
    printf("cases <disease> \t\t\t\t Find cases of a disease in a location\n");
    printf("cases <location> <disease> \t\t\t Find total cases of a disease \n");
    printf("delete <location> \t\t\t\t To delete existing location\n");
    printf("clear \t\t\t\t\t\t To clear the terminal\n");
    printf("exit \t\t\t\t\t\t To exit\n");
}

void handleAddCommand(char* command) {
    char location[100];
    if (sscanf(command, "add %[^\n]", location) == 1) {
        addData(LOCATIONS_FILE, location);
    } else {
        printf("Invalid number of arguments for 'add' command\n");
    }
}

void handleListLocationsCommand() {
    readData(LOCATIONS_FILE);
}

void handleListDiseaseCommand() {
    FILE* file = fopen(RECORDS_FILE, "r");
    if (file != NULL) {
        char line[100];
        int index = 0;
        char diseases[100][100];
        int numDiseases = 0;

        while (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, ",");
            while (token != NULL) {
                token[strcspn(token, "\n")] = '\0'; // Remove newline character
                strcpy(diseases[numDiseases++], token);
                token = strtok(NULL, ",");
            }
        }
        fclose(file);

        // Print the diseases
        for (int i = 0; i < numDiseases; i += 2) {
            printf("%d. %s\n", index + 1, diseases[i + 1]);
            index++;
        }

        printf("Successfully read from file\n");
    } else {
        printf("Failed to read from file\n");
    }
}

void handleWhereCommand(char* command) {
    char disease[100];
    if (sscanf(command, "where %[^\n]", disease) == 1) {
        FILE* file = fopen(RECORDS_FILE, "r");
        if (file != NULL) {
            char line[100];
            int flag = 0;
            while (fgets(line, sizeof(line), file)) {
                char recLocation[100], recDisease[100];
                if (sscanf(line, "%[^,],%[^\n]", recLocation, recDisease) == 2) {
                    if (strcmp(recDisease, disease) == 0) {
                        flag++;
                        printf("%s\n", recLocation);
                    }
                }
            }

            if (flag == 0) {
                printf("No locations with this disease\n");
            }

            fclose(file);
            printf("Successfully read from file\n");
        } else {
            printf("Failed to open file for reading\n");
        }
    } else {
        printf("Invalid number of arguments for 'where' command\n");
    }
}

void handleCasesCommand(char* command) {
    char arguments[MAX_ARGUMENTS][100];
    int numArguments = sscanf(command, "cases %[^,\n],%[^,\n]", arguments[0], arguments[1]);
    if (numArguments == 1 || numArguments == 2) {
        FILE* file = fopen(RECORDS_FILE, "r");
        if (file != NULL) {
            char line[100];
            char location[100] = "";
            char disease[100];
            int cases = 0;
            while (fgets(line, sizeof(line), file)) {
                char recLocation[100], recDisease[100], recCasesStr[100];
                if (sscanf(line, "%[^,],%[^,],%[^\n]", recLocation, recDisease, recCasesStr) == 3) {
                    if (numArguments == 1) {
                        if (strcmp(recDisease, arguments[0]) == 0) {
                            cases += atoi(recCasesStr);
                        }
                    } else {
                        if (strcmp(recLocation, arguments[0]) == 0 && strcmp(recDisease, arguments[1]) == 0) {
                            cases += atoi(recCasesStr);
                        }
                    }
                }
            }

            printf("Total cases of '%s' = %d\n", arguments[numArguments - 1], cases);
            fclose(file);
            printf("Successfully read from file\n");
        } else {
            printf("Failed to open file for reading\n");
        }
    } else {
        printf("Invalid number of arguments for 'cases' command\n");
    }
}

void handleRecordCommand(char* command) {
    char location[100], disease[100], cases[100];
    if (sscanf(command, "record %[^,\n],%[^,\n],%[^\n]", location, disease, cases) == 3) {
        FILE* file = fopen(RECORDS_FILE, "a");
        if (file != NULL) {
            fprintf(file, "%s,%s,%s\n", location, disease, cases);
            fclose(file);
            printf("Successfully recorded data\n");
        } else {
            printf("Failed to record data\n");
        }
    } else {
        printf("Invalid number of arguments for 'record' command\n");
    }
}

void handleDeleteCommand(char* command) {
    char location[100];
    if (sscanf(command, "delete %[^\n]", location) == 1) {
        FILE* file = fopen(RECORDS_FILE, "r");
        if (file != NULL) {
            char line[100];
            char records[MAX_RECORDS][100];
            int numRecords = 0;
            while (fgets(line, sizeof(line), file)) {
                char recLocation[100];
                sscanf(line, "%[^,],", recLocation);
                if (strcmp(recLocation, location) != 0) {
                    strcpy(records[numRecords++], line);
                }
            }

            fclose(file);

            file = fopen(RECORDS_FILE, "w");
            if (file != NULL) {
                for (int i = 0; i < numRecords; i++) {
                    fputs(records[i], file);
                }

                fclose(file);
                printf("Records successfully deleted\n");
            } else {
                printf("Failed to open file for updating records\n");
            }
        } else {
            printf("Failed to delete record\n");
        }
    } else {
        printf("Invalid number of arguments for 'delete' command\n");
    }
}

int main() {
    printf("\t\t\t\t ********************* WELCOME TO HR SYSTEM *********************\n\n");
    printf("type `help` then press Enter key\n");
    char commandLine[100];

    while (1) {
        printf("\nconsole > ");
        fgets(commandLine, sizeof(commandLine), stdin);

        if (strlen(commandLine) <= 1) {
            continue;
        }

        if (strncmp(commandLine, "add", 3) == 0) {
            handleAddCommand(commandLine);
        } else if (strncmp(commandLine, "list", 4) == 0) {
            if (strncmp(commandLine + 5, "locations", 9) == 0) {
                handleListLocationsCommand();
            } else if (strncmp(commandLine + 5, "diseases", 8) == 0) {
                handleListDiseaseCommand();
            } else {
                printf("Invalid command %s\n", commandLine);
            }
        } else if (strncmp(commandLine, "record", 6) == 0) {
            handleRecordCommand(commandLine);
        } else if (strncmp(commandLine, "delete", 6) == 0) {
            handleDeleteCommand(commandLine);
        } else if (strncmp(commandLine, "where", 5) == 0) {
            handleWhereCommand(commandLine);
        } else if (strncmp(commandLine, "cases", 5) == 0) {
            handleCasesCommand(commandLine);
        } else if (strncmp(commandLine, "help", 4) == 0) {
            printHelp();
        } else if (strncmp(commandLine, "exit", 4) == 0) {
            break;
        } else if (strncmp(commandLine, "clear", 5) == 0) {
            system(CLEAR_COMMAND);
        } else {
            printf("Invalid command: %s\n", commandLine);
        }
    }

    return 0;
}
