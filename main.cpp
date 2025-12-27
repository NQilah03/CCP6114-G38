#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Constants
const int MAX_COLUMNS = 10;
const int MAX_ROWS = 100;

// Global Variables
string sheetName = "";
string columnNames[MAX_COLUMNS];
string columnTypes[MAX_COLUMNS];
string sheetData[MAX_ROWS][MAX_COLUMNS];
int numColumns = 0;
int numRows = 0;

// Function Prototypes
void createSheet();
void insertRow();
void viewSheetCSV();
bool isValidInt(string value);
void MainMenu();

int main()
{
    int choice;

    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

    //createSheet();
    //insertRow();
    //viewSheetCSV();
    do
    {
        MainMenu();
        cout << "Please Enter Your Choice\n";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Invalid input. Please enter a valid number.\n\n";
            continue;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            createSheet();
            break;

        case 2:
            insertRow();
            break;

        case 3:
            viewSheetCSV();
            break;

        case 4:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Error: Invalid menu choice. Please try again.\n\n";
        }

    }
    while (choice != 4);

    return 0;
}

void createSheet() {
    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl << endl;

    // define number of columns
    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid INT value." << endl;
            numColumns = 0;
        } 
        else if (numColumns < 1 || numColumns > MAX_COLUMNS) {
            cout << "Invalid INT value. Please enter an INT value between 1 and " << MAX_COLUMNS << "." << endl;
        }
    } while (numColumns < 1 || numColumns > MAX_COLUMNS);

    cin.ignore();

    // loop through each column and get name and type
    for (int i=0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);

        do {
            cout << "Enter column " << (i + 1) << " type (INT or TEXT): ";
            getline(cin, columnTypes[i]);

            if (columnTypes[i] != "INT" && columnTypes[i] != "TEXT") {
                cout << "Invalid type. Please enter INT or TEXT." << endl;
            }
        } while (columnTypes[i] != "INT" && columnTypes[i] != "TEXT");

    }

    cout << "Sheet structure created successfully." << endl << endl;
}

bool isValidInt(string value) {
    if (value.empty()) return false;

    for (int i = 0; i < value.length(); i++) {
        if (!isdigit(value[i])) {
            return false;
        }
    }
    return true;
}

void insertRow() {
    string input;

    while (true) {
        cout << "\n-------------------------------------------\n";
        cout << "Insert New Attendance Row\n";
        cout << "-------------------------------------------\n";

        if (numRows >= MAX_ROWS) {
            cout << "Error: Maximum row limit reached.\n";
            return;
        }

        for (int col = 0; col < numColumns; col++) {
            while (true){
                cout << "Enter " << columnNames[col] << ": ";
                getline(cin, input);

                if (columnTypes[col] == "INT") {
                    if (!isValidInt(input)) {
                        cout << "Error: Invalid INT value. Please enter a number.\n";
                        continue;
                    }
                }


                sheetData[numRows][col] = input;
                break;
            }
        }

        numRows++;
        cout << "Row inserted successfully.\n\n";

        cout << "Insert another row? (Y/N): ";
        getline(cin, input);

        if (input != "Y" && input != "y") {
            break;
        }
    }
}

void viewSheetCSV() {
    cout << "\n-------------------------------------------\n";
    cout << "     View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < numColumns; i++){
        cout << columnNames[i];
        if (i != (numColumns - 1)){
            cout << ", ";
        }
    }
    cout << endl;

    for (int row = 0; row < numRows; row++){
        for (int column = 0; column < numColumns; column++){
            cout << sheetData[row][column];
            if (column != (numColumns - 1)){
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void MainMenu()
{
    cout << "\n-------------------------------------------\n";
    cout << "Main Menu\n";
    cout << "-------------------------------------------\n";
    cout << "1. Create Attendance Sheet\n";
    cout << "2. Insert Attendance Row\n";
    cout << "3. View Attendance Sheet (CSV)\n";
    cout << "4. Exit\n";
}
