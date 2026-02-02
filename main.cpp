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
string termName = "";
string columnNames[MAX_COLUMNS];
string columnTypes[MAX_COLUMNS];
string database[MAX_SHEET];
string sheetData[MAX_ROWS][MAX_COLUMNS];
int numColumns = 0;
int numRows = 0;

// Function Prototypes

// Milestone 1 functions
string createNewAttendanceSheet();
string createSheet();
void insertRow();

// Milestone 2 functions
string showExistingFiles(int);
void editSheetMenuM2(string);
void deleteAttendanceRow(string);
void countRowsOutput();
void updateAttendanceRow(string);
void insertRowM2(string);

// File functions
int splitLine(string line, string tokens[], int maxTokens);
void loadAttendanceFile(string filename);
void createCSVfile(string);
void readDataFromFile(string filename);
void saveCSVfile(string filename);

// Display functions
void MainMenuM1();
int MainMenuM2();
void M2MenuChoice(int choice, int sheet);
void viewSheetCSV();
void printSheetRawCSV();
void displayCurrentSheet();
void viewTermName();

// Helper functions
bool isValidInt(string value);
bool isValidText(string value);
int findStudentIdCol();
string getIntInputLine(string prompt);


int main()
{
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
void loadAttendanceFile(string filename) {
    ifstream f(filename);
    if (!f) {
        cout << "Error: Cannot open file.\n";
        return;
    }

    // Clear old data
    for (int i = 0; i < MAX_COLUMNS; i++) {
        columnNames[i] = "";
        columnTypes[i] = "";
    }
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

    // Set fixed column types for Milestone 2
    columnTypes[0] = "INT";  // StudentID
    columnTypes[1] = "TEXT"; // Name
    columnTypes[2] = "INT";  // Status
}

//Function to save the attendance data into a csv file.
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
        for (int i = 0; i < numColumns; i++) {
            columnNames[i] = "";
            columnTypes[i] = "";
        }
        for (int r = 0; r < numRows; r++)
            for (int c = 0; c < numColumns; c++)
                sheetData[r][c] = "";

        numRows = 0;
    }
    outputFile.close();
}

// Function to save updated or deleted data to file
void saveCSVfile(string filename) {
    ofstream outputFile;
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
        cout << "\nChanges saved to file successfully.\n";
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
        loadAttendanceFile(filename);

        viewSheetCSV(); // Display the loaded sheet to the user
        editSheetMenuM2(filename);  // Pass filename to edit menu
    }

    readFile.close();
}

string createSheet() {
    string sheetName;
    cout << "\nEnter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl << endl;

    numColumns = 3;
    
    // fixed columns for milestone 2
    columnNames[0] = "StudentID";
    columnTypes[0] = "INT";
    
    columnNames[1] = "Name";
    columnTypes[1] = "TEXT";
    
    columnNames[2] = "Status";
    columnTypes[2] = "INT";

    cout << "Sheet structure created successfully." << endl << endl;
    return sheetName;
}

string createNewAttendanceSheet(){
    int choice;
    string sheetName;

    cout << "============================================\n";
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "============================================\n";

    sheetName = createSheet();
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
            return sheetName;

        default:
            cout << "\nError: Invalid menu choice. Please try again.\n\n";
            break;
        }
    }
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

        // Get StudentID
        while (true) {
            cout << "Enter StudentID: ";
            getline(cin, input);

            if (!isValidInt(input)) {
                cout << "Error: Invalid INT value. Please enter a number.\n";
                continue;
            }

            sheetData[numRows][0] = input;
            break;
        }

        // Get Name 
        while (true) {
            cout << "Enter Name: ";
            getline(cin, input);

            if (!isValidText(input)) {
                cout << "Error: Invalid TEXT value. Please enter text.\n";
                continue;
            }

            sheetData[numRows][1] = input;
            break;
        }

        // Get Status
        while (true) {
            cout << "Enter Status (0 or 1): ";
            getline(cin, input);

            if (!isValidInt(input)) {
                cout << "Error: Invalid INT value. Please enter 0 or 1.\n";
                continue;
            }

            if (input != "0" && input != "1") {
                cout << "Error: Status must be 0 or 1.\n";
                continue;
            }

            sheetData[numRows][2] = input;
            break;
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

void insertRowM2(string currentFilename) {
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
                cout << "Enter " << columnNames[col] << " (" << columnTypes[col] << "): ";
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

        // Auto save new row to file
        saveCSVfile(currentFilename);

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
        string sheetName = createNewAttendanceSheet();
        database[sheet] = sheetName + ".csv";
        sheet++;
        choice = MainMenuM2();                           
    }

    if (choice == 2){ //2.Load existing files
        if (sheet == 0) {
            // No sheets created yet
            cout << "\nError: No attendance sheets available to load.\n";
            cout << "Please create a new attendance sheet first.\n";
            return;
        }
        
        string loadingFileName;
        if (sheet == 1){
            loadingFileName = database[0];
            readDataFromFile(loadingFileName);
        }
        else if (sheet > 1){
            // Multiple files exist, let user choose
            loadingFileName = showExistingFiles(sheet);
            readDataFromFile(loadingFileName);
        }
    }
    else { //3.Exit program
        return;
    }
}

void updateAttendanceRow(string currentFilename) {
    cout << "\n-------------------------------------------\n";
    cout << "Update Attendance Row\n";
    cout << "-------------------------------------------\n";

    int sidCol = findStudentIdCol();
    if (sidCol == -1) {
        cout << "Error: StudentID column not found.\n";
        return;
    }

    string sid = getIntInputLine("Enter StudentID to update: ");

    int targetRow = -1;
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

    cout << "\nUpdating row for StudentID " << sid << endl;

    for (int col = 0; col < numColumns; col++) {
        cout << columnNames[col] << " [" << sheetData[targetRow][col] << "]: ";
        string newValue;
        getline(cin, newValue);

        if (newValue.empty()) continue; // Keep old data if blank

        if (columnTypes[col] == "INT") {
            while (!isValidInt(newValue)) {
                cout << "Please enter a valid number (press Enter to skip): ";
                getline(cin, newValue);
                if (newValue.empty()) break;
            }
            if (newValue.empty()) continue;
        }
        else if (columnTypes[col] == "TEXT") {
            while (!isValidText(newValue)) {
                cout << "Please enter a valid text (press Enter to skip): ";
                getline(cin, newValue);
                if (newValue.empty()) break;
            }
            if (newValue.empty()) continue;
        }

        sheetData[targetRow][col] = newValue;
    }

    cout << "\nRow updated successfully!\n";
    displayCurrentSheet();

    saveCSVfile(currentFilename);
}

void viewTermName() {
    if (termName.empty()) {
        cout << "No term created yet.\n";
    } else {
        cout << "\n-------------------------------------------\n";
        cout << "Term Name: " << termName << endl;
        cout << "-------------------------------------------\n";
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

void editSheetMenuM2(string currentFilename) {
    while (true) {
        int choice;
        cout << "\n-------------------------------------------\n";
        cout << "Main Menu Milestone 2 (Edit Loaded Sheet)\n";
        cout << "-------------------------------------------\n";
        cout << "1. View Term Name\n";
        cout << "2. Display Current Sheet\n";
        cout << "3. Update Attendance Row\n";
        cout << "4. Delete Attendance Row\n";
        cout << "5. Insert New Attendance Row\n";
        cout << "6. Count Rows\n";
        cout << "7. Exit to Main Menu\n\n";
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
            viewTermName();
        }
        else if (choice == 2) {
            displayCurrentSheet();
        }
        else if (choice == 3) {
            updateAttendanceRow(currentFilename);
        }
        else if (choice == 4) {
            deleteAttendanceRow(currentFilename);
        }
        else if (choice == 5) {
            insertRowM2(currentFilename);
        }
        else if (choice == 6) {
            countRowsOutput();
        }
        else if (choice == 7) {
            return;
        }
        else {
            cout << "Error: Invalid menu choice.\n";
        }
    }
}

// Deletes an attendance row based on StudentID
void deleteAttendanceRow(string currentFilename) {
    cout << "\n-------------------------------------------\n";
    cout << "Delete Attendance Row\n";
    cout << "-------------------------------------------\n";

    int sidCol = findStudentIdCol();
    if (sidCol == -1) {
        cout << "Error: StudentID column not found.\n";
        return;
    }

    string sid = getIntInputLine("Enter StudentID to delete: ");

    int targetRow = -1;
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

    saveCSVfile(currentFilename);
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