// *********************************************************
// Program: TC1L_GROUP38_A1.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT2L and TT3L
// Trimester: 2530
// Member_1: 252UC241MK | ADRIANA NUR ZAHRA BINTI MOHD HELMI | ADRIANA.NUR.ZAHRA1@student.mmu.edu.my | 0132080445
// Member_2: 252UC242N8 | CHIAM JUIN HOONG | CHIAM.JUIN.HOONG1@student.mmu.edu.my | 0125450314
// Member_3: 252UC243DZ | NURSYAHIRAH AQILAH BINTI AINUL HISHAM | NURSYAHIRAH.AQILAH.AINUL1@student.mmu.edu.my | 0194482144
// Member_4: 252UC243DY | QAISARAH BINTI SHAMSUL AZRAN | QAISARAH.SHAMSUL.AZRAN1@student.mmu.edu.my | 0134130145
// *********************************************************
// Task Distribution
// Member_1: Create Sheet, Sheet Structure, Data Types
// Member_2: Insert Attendance Row
// Member_3: Main Menu and Error Handling
// Member_4: View Attendance Sheet in CSV
// *********************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
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
bool sheetExist = false;

// Function Prototypes
void createSheet();
void insertRow();
void viewSheetCSV();
bool isValidInt(string value);
bool isValidText(string value);
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
        cout << "Please Enter Your Choice\n\n";
        cin >> choice;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Invalid input. Please enter a valid number.\n\n";
            cin >> choice;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            createSheet();
            insertRow();
            break;

        /**case 2:
            if (sheetExist == false)
            {
                cout << "\nPlease create an attendance sheet first.\n";
            }
            else
            {
                insertRow();
            }
            break;  **/

        case 2:
            if (sheetExist == false)
            {
                cout << "\nPlease create an attendance sheet first.\n";
            }
            else
            {
                viewSheetCSV();
            }

            break;

        case 3:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Error: Invalid menu choice. Please try again.\n\n";
        }

    }
    while (choice != 3);

    return 0;
}

void createSheet() {
    cout << "\nEnter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl << endl;

    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid INT value. Please enter a number.\n";
            numColumns = 0;
        }
        else if (numColumns < 1 || numColumns > MAX_COLUMNS) {
            cout << "Invalid INT value. Please enter a value between 1 and "
                 << MAX_COLUMNS << ".\n";
        }

    } while (numColumns < 1 || numColumns > MAX_COLUMNS);

    cin.ignore();

    // loop through each column and get name and type
    for (int i = 0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);

        do {
            cout << "Enter column " << (i + 1) << " type (INT or TEXT): ";
            getline(cin, columnTypes[i]);

            if (columnTypes[i] != "INT" && columnTypes[i] != "TEXT") {
                cout << "Invalid type. Please enter INT or TEXT.\n";
            }
        } while (columnTypes[i] != "INT" && columnTypes[i] != "TEXT");
    }

    sheetExist = true;
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
        else if (columnTypes[col] == "TEXT") {
            if (!isValidText(input)) {
                cout << "Error: Invalid TEXT value. Please enter text.\n";
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

bool isValidText(string value) {
    if (value.empty()) return false;

    for (int i = 0; i < value.length(); i++) {
        if (!isdigit(value[i])) {
            return true;
        }
    }
    return false;
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
    //cout << "2. Insert Attendance Row\n";
    cout << "2. View Attendance Sheet (CSV)\n";
    cout << "3. Exit\n";
}
