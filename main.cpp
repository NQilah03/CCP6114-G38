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
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

const int MAX_COLUMNS = 10;
const int MAX_ROWS = 100;
const int MAX_SHEET = 100;

// Global Variables
string sheetName = "";
string columnNames[MAX_COLUMNS];
string columnTypes[MAX_COLUMNS];
string database[MAX_SHEET];
string sheetData[MAX_ROWS][MAX_COLUMNS];
int numColumns = 0;
int numRows = 0;

// Function Prototypes

// Milestone 1 functions
void createNewAttendanceSheet();
void createSheet();
void insertRow();

// Milestone 2 functions
string showExistingFiles(int);
void editSheetMenuM2();
void deleteAttendanceRow();
void countRowsOutput();

// File functions
int splitLine(string line, string tokens[], int maxTokens);
void loadAttendanceFile(string filename);
void createCSVfile(string);
void readDataFromFile(string filename);

// Display functions
void MainMenuM1();
int MainMenuM2();
void M2MenuChoice(int, int);
void viewSheetCSV();
void printSheetRawCSV();
void displayCurrentSheet();

// Helper functions
bool isValidInt(string value);
bool isValidText(string value);
int findStudentIdCol();
string getIntInputLine(string prompt);


int main()
{
    string termName;
    cout << "============================================\n";
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "============================================\n\n";

    cout << "Create School Term (Database)" << endl;
    cout << "-------------------------------------------\n";
    cout << "Enter term name: ";
    cin >> termName;
    cout << "Database \"" << termName << "\" created and loaded." << endl << endl;
    cin.ignore();

    int choice=1, sheet=0;
    M2MenuChoice(choice, sheet);
    return 0;
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

bool isValidText(string value) {
    if (value.empty()) return false;

    for (int i = 0; i < value.length(); i++) {
        if (!isdigit(value[i])) {
            return true;
        }
    }
    return false;
}

// Splits a CSV line by comma
int splitLine(string line, string tokens[], int maxTokens) {
    int count = 0;
    string token = "";
    
    // Go through each character in the line
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            tokens[count] = token;
            count++;
            token = "";
        } else {
            token = token + line[i];
        }
    }
    
    tokens[count] = token;
    count++;
    
    return count;
}

// Loads attendance data from a CSV file into memory
// Assumes the first column is StudentID (INT)
void loadAttendanceFile(string filename) {
    ifstream f(filename);
    if (!f) {
        cout << "Error: Cannot open file.\n";
        return;
    }

    // Clear old data
    for (int i = 0; i < MAX_COLUMNS; i++) columnNames[i] = "";
    for (int r = 0; r < MAX_ROWS; r++)
        for (int c = 0; c < MAX_COLUMNS; c++)
            sheetData[r][c] = "";

    numRows = 0;
    numColumns = 0;

    string line;
    string tokens[MAX_COLUMNS];

    // Read header
    if (getline(f, line)) {
        numColumns = splitLine(line, tokens, MAX_COLUMNS);
        for (int i = 0; i < numColumns; i++) {
            columnNames[i] = tokens[i];
        }
    }

    // Read data rows
    while (getline(f, line) && numRows < MAX_ROWS) {
        int cols = splitLine(line, tokens, MAX_COLUMNS);

        // First column must be StudentID
        if (cols <= 0 || !isValidInt(tokens[0])) continue;

        for (int c = 0; c < numColumns; c++) {
            sheetData[numRows][c] = (c < cols) ? tokens[c] : "";
        }
        numRows++;
    }

    f.close();
}

//Function to save the attendance data into a csv file.
//The idea is the same as the viewSheetCSV() function but instead of
//outputting on the terminal, we write into a file.
void createCSVfile(string sheetName){
    ofstream outputFile;
    string filename = sheetName + ".csv";
    outputFile.open(filename);

    if(!outputFile){
        cout << "\nError opening the file \"" << filename << "\"." << endl;
    }
    else{
        // Header (CSV)
        for (int i = 0; i < numColumns; i++){
            outputFile << columnNames[i];
            if (i != (numColumns - 1)) outputFile << ",";
        }
        outputFile << "\n";

        // Rows (CSV)
        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numColumns; col++){
                outputFile << sheetData[row][col];
                if (col != (numColumns - 1)) outputFile << ",";
            }
            outputFile << "\n";
        }

        cout << "\nThe file \"" << filename << "\" has been created. Please check your folders." << endl;

        // Reset for next sheet
        for (int i = 0; i < numColumns; i++) columnNames[i] = "";
        for (int r = 0; r < numRows; r++)
            for (int c = 0; c < numColumns; c++)
                sheetData[r][c] = "";

        numRows = 0;
    }
    outputFile.close();
}

//Function to read attendance data from the attendance csv file.
void readDataFromFile(string filename){
    ifstream readFile;
    readFile.open(filename);
    if (!readFile){
        cout << "\nError opening the file \"" << filename << "\"." << endl;
    }
    else {
        cout << "\nReading attendance data from file...\n";
        cout << "Successfully loaded: " << filename << "\n\n";

        // Load the file contents into columnNames[] and sheetData[] arrays
        // This allows the data to be edited
        loadAttendanceFile(filename);

        viewSheetCSV(); // Display the loaded sheet to the user
        editSheetMenuM2();
    }

    readFile.close();
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

    cout << "Sheet structure created successfully." << endl << endl;
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

//Function to view the attendance data in CSV, not in file.
void viewSheetCSV() {
    cout << "\n-------------------------------------------\n";
    cout << "     View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    //Loop through each elements in the columnName[] array to display the column names.
    for (int i = 0; i < numColumns; i++){
        cout << columnNames[i];           
        if (i != (numColumns - 1)){
            cout << ", "; //Add comma between elements
        }
    }
    cout << endl;

    //Loop through each rows and columns to display the elements
    for (int row = 0; row < numRows; row++){
        for (int column = 0; column < numColumns; column++){
            cout << sheetData[row][column];
            if (column != (numColumns - 1)){ //add comma between elements.
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void printSheetRawCSV() {
    // Header
    for (int i = 0; i < numColumns; i++) {
        cout << columnNames[i];
        if (i != numColumns - 1) cout << ", ";
    }
    cout << endl;

    // Rows
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numColumns; c++) {
            cout << sheetData[r][c];
            if (c != numColumns - 1) cout << ", ";
        }
        cout << endl;
    }
}

void displayCurrentSheet() {
    cout << "\n-------------------------------------------\n";
    cout << "Current Attendance Sheet" << "\n";
    cout << "-------------------------------------------\n";
    printSheetRawCSV();
}


void MainMenuM1()
{
    cout << "\n-------------------------------------------\n";
    cout << "Main Menu Milestone 1\n";
    cout << "-------------------------------------------\n";
    cout << "1. Insert More Rows\n";
    cout << "2. View Attendance Sheet (CSV)\n";
    cout << "3. Save Sheet in CSV File and Exit\n";
}

//Function to display menu choices after attendance sheet created and filled.
int MainMenuM2(){
    int choice;
    cout << "\n-------------------------------------------\n";
    cout << "Main Menu Milestone 2\n";
    cout << "-------------------------------------------\n";
    cout << "1. Create New Attendance Sheet\n";
    cout << "2. Load Existing Attendance Sheet(s)\n";
    cout << "3. Exit Program\n\n";
    cout << "Please Enter Your Choice: ";
    cin >> choice;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Invalid input. Please enter a valid number.\n\n";
        cin >> choice;
    }
    cin.ignore();

    return choice;
}

void M2MenuChoice(int choice, int sheet){
    while(choice == 1){ //1.Create new attendance sheet
        createNewAttendanceSheet();
        choice = MainMenuM2();
        database[sheet] = sheetName + ".csv";
        sheet++;                              
    }

    if (choice == 2){ //2.Load existing files
        string loadingFileName;
        if (sheet == 1){
            loadingFileName = sheetName + ".csv";
            readDataFromFile(loadingFileName);
        }                                            
        else if (sheet > 1){
            //If more than one file, display file list & let user choose which file to load
            loadingFileName = showExistingFiles(sheet);
            readDataFromFile(loadingFileName);
        }
    }
    else { //3.Exit program
        return;
    }
}

void createNewAttendanceSheet(){
    int choice;

    cout << "============================================\n";
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "============================================\n";

    createSheet();
    insertRow();

    while(true)
    {
        MainMenuM1();
        cout << "\nPlease Enter Your Choice: ";
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
            insertRow();
            break;

        case 2:
            viewSheetCSV();
            break;

        case 3:
            createCSVfile(sheetName);
            return;

        default:
            cout << "\nError: Invalid menu choice. Please try again.\n\n";
            break;
        }
    }
}


//Function to show all existing files and let user choose the file to load.
string showExistingFiles(int sheet){
    int fileToLoad;
    string loadingFileName;
    cout << "-------------------------------------------\n";
    cout << "\tExisting Files" << endl;
    cout << "-------------------------------------------\n";
    for (int i = 0; i < sheet; i++){
        cout << i + 1 << ". " << database[i] << endl;
    }
    do{
        cout << "\nPlease choose which file to load [1-" << sheet << "]: ";
        cin >> fileToLoad;
    }while(fileToLoad < 1 || fileToLoad > sheet);
    loadingFileName = database[fileToLoad - 1];
    return loadingFileName;
}

void editSheetMenuM2() {
    while (true) {
        int choice;
        cout << "\n-------------------------------------------\n";
        cout << "Main Menu Milestone 2 (Edit Loaded Sheet)\n";
        cout << "-------------------------------------------\n";
        cout << "1. Display Current Sheet\n";
        cout << "2. Delete Attendance Row\n";
        cout << "3. Count Rows\n";
        cout << "4. Exit to Main Menu\n\n";
        cout << "Please Enter Your Choice: ";

        cin >> choice;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Invalid input. Please enter a valid number.\n\n";
            cin >> choice;
        }
        cin.ignore();

        if (choice == 1) {
            displayCurrentSheet();
        }
        else if (choice == 2) {
            deleteAttendanceRow();
        }
        else if (choice == 3) {
            countRowsOutput();
        }
        else if (choice == 4) {
            return;
        }
        else {
            cout << "Error: Invalid menu choice.\n";
        }
    }
}

// Deletes an attendance row based on StudentID
// Rows below the deleted record are shifted up
void deleteAttendanceRow() {
    cout << "\n-------------------------------------------\n";
    cout << "Delete Attendance Row\n";
    cout << "-------------------------------------------\n";

    int sidCol = findStudentIdCol(); // Find the column that containts StudentID
    if (sidCol == -1) {
        cout << "Error: StudentID column not found.\n";
        return;
    }

    string sid = getIntInputLine("Enter StudentID to delete: ");

    int targetRow = -1; // Search for matching row
    for (int r = 0; r < numRows; r++) {
        if (sheetData[r][sidCol] == sid) {
            targetRow = r;
            break;
        }
    }

    if (targetRow == -1) {
        cout << "Error: StudentID does not exist.\n";
        return;
    }

    // Shift rows upward to remove the selected row
    for (int r = targetRow; r < numRows - 1; r++) { 
        for (int c = 0; c < numColumns; c++) {
            sheetData[r][c] = sheetData[r + 1][c];
        }
    }

    for (int c = 0; c < numColumns; c++) {
        sheetData[numRows - 1][c] = "";
    }

    numRows--;

    cout << "Row deleted successfully.\n";

    cout << "\nUpdated Sheet:\n";
    printSheetRawCSV();
}

void countRowsOutput() {
    cout << "\n-------------------------------------------\n";
    cout << "Count Rows\n";
    cout << "-------------------------------------------\n";
    cout << "Number of rows: " << numRows << endl;
}

int findStudentIdCol() {
    for (int i = 0; i < numColumns; i++) {
        if (columnNames[i] == "StudentID") {
            return i;
        }
    }
    return -1;
}

string getIntInputLine(string prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);

        if (!isValidInt(s)) {
            cout << "Error: Invalid integer. Try again.\n\n";
            continue;
        }
        return s;
    }
}