#include <iostream>
# include <conio.h>
#include <string>
#include <fstream>
#include <limits>  // For numeric_limits

using namespace std;

// Function prototypes
void displayWelcomeMessage();
char getNationality();
int getBudget();
void displayLocations();
void displayKashmirPlaces();
void displayGilgitBaltistanPlaces();
void displayMuree();
void displayNARANKAGHAN();
int getHotelType();
int calculateHotelExpenses(int, int);
int getTravelType();
int calculateTravelExpenses(int, int);
void displayTotalExpenses(int);
void displayEmergencyContacts();
float getUserRating();
float convertToPKR(char nationality);
void storeCustomerInfo(int budget, int locationChoice, int hotelType, int travelType, int numDays, int numPerson, int totalExpenses, float rating);

// Constants
struct traveltype
{
    const int AIR_TRAVEL_COST = 5000;
    const int ROAD_TRAVEL_COST = 2000;
}ttmode;
struct hotel {
    const int BUDGET_HOTEL = 1000;
    const int MID_RANGE_HOTEL = 2000;
    const int LUXURY_HOTEL = 3000;
}htmode;

struct currencyconv {
    const float DOLLAR_TO_PKR = 286;
    const float EURO_TO_PKR = 308;
}ccmode;

// Main program
int main() {
    displayWelcomeMessage();
    cout << endl << endl;
    char nationality = getNationality();
    float conversionRate = convertToPKR(nationality);
    int budget = getBudget();
    budget *= conversionRate;

    cout << "YOUR BDGET IN PKR = " << endl;
    cout << " \033[35m =============\033[0m" << endl;
    cout << "   Rs." << budget << endl;
    cout << "  \033[35m=============\033[0m" << endl;
    cout << endl;

    displayLocations();
    int locationChoice;
    cin >> locationChoice;

    switch (locationChoice) {
    case 1:
        displayKashmirPlaces();
        break;
    case 2:
        displayGilgitBaltistanPlaces();
        break;
    case 3:
        displayMuree();
        break;
    case 4:
        displayNARANKAGHAN();
        break;
    default:
        cout << "Invalid location choice!" << endl;
        return 0;
    }
    cout << endl;

    displayEmergencyContacts();
    cout << endl;

    int numDays, numPerson;
    cout << "Enter The Number of Days You Are Planning to Stay: ";
    cin >> numDays;
    cout << endl;
    cout << "Enter The Number of People Travelling: ";
    cin >> numPerson;
    cout << endl;

    int hotelType = getHotelType();
    int hotelExpenses = calculateHotelExpenses(numDays, hotelType);
    if (hotelExpenses == -1)
    {
        return 0;
    }

    cout << endl;
    int travelType = getTravelType();
    int travelExpenses = calculateTravelExpenses(numPerson, travelType);
    if (travelExpenses == -1) {
        return 0;
    }

    cout << endl;
    int totalExpenses = hotelExpenses + travelExpenses;
    displayTotalExpenses(totalExpenses);

    char ans;
    if (totalExpenses <= budget) {
        cout << "                          \033[32m                    ---------------------------------------------------------\033[0m" << endl;
        if (totalExpenses < budget)
        {
            cout << "                      \033[32m                           YOUR TRIP EXPENSES ARE WITHIN YOUR BUDGET :)      \033[0m" << endl;
        }
        else
        {
            cout << "                      \033[32m                          YOUR TRIP EXPENSES ARE EQUAL TO YOUR BUDGET        \033[0m" << endl;
        }
        cout << "                          \033[32m                    ---------------------------------------------------------\033[0m" << endl;
        cout << "WANNA TRY AGAIN?" << endl;
        cout << " PRESS 'Y' IF YOU WANT TO TRY AGAIN (or any other key to skip) " << endl;
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
        {
            main();
        }
        else
        {
            float rating = getUserRating();
            storeCustomerInfo(budget, locationChoice, hotelType, travelType, numDays, numPerson, totalExpenses, rating);
            cout << "                                      \033[33m                        ********************************  \033[0m" << endl;
            cout << "                                                               THANK YOU FOR USING OUR SYSTEM          " << endl;
            cout << "                                      \033[33m                        ********************************  \033[0m" << endl;
        }
    }
    else {
        // Display the message in red
        cout << "                                                  \033[31m---------------------------------------------------------\033[0m" << endl;
        cout << "                                                  \033[31m     YOUR TRIP EXPENSES ARE GREATER THAN YOUR BUDGET\033[0m     " << endl;
        cout << "                                                  \033[31m---------------------------------------------------------\033[0m" << endl;
        cout << " WE SUGGEST YOU TO TRY AGAIN " << endl;
        cout << " PRESS 'y' IF YOU WANT TO TRY AGAIN (or any other key to skip)  " << endl;
        cin >> ans;
        if (ans == 'y') {
            main();
        }
        else {
            float rating = getUserRating();
            storeCustomerInfo(budget, locationChoice, hotelType, travelType, numDays, numPerson, totalExpenses, rating);
            cout << "                                      \033[33m                        ********************************  \033[0m" << endl;
            cout << "                                                               THANK YOU FOR USING OUR SYSTEM          " << endl;
            cout << "                                      \033[33m                        ********************************  \033[0m" << endl;
        }
    }

    _getch();
    return 0;
}

// Function definitions

void displayWelcomeMessage() {
    cout << "                                               \033[32m        ****************************************************    \033[0m       " << endl;
    cout << "                                                             WELCOME TO OUR TOURISM MANAGEMENT SYSTEM                        " << endl;
    cout << "                                                \033[32m       **************************************************** \033[0m       " << endl;
    cout << "                                                                  EXPLORE TOURIST SPOTS, PLACES TO VISIT                  " << endl;
    cout << "                                                                         AND MUCH MORE!                                 " << endl;
    cout << "                                                 \033[32m      ****************************************************   \033[0m      " << endl;
}

char getNationality() {
    char nationality[10];  // Define a character array to store the input

    cout << endl;
    cout << "Are you a national or international tourist?" << endl;
    cout << "Enter 'N' for national or 'I' for international: ";

    cin >> nationality;  // Read input into the character array

    // Return the first character in uppercase
    return toupper(nationality[0]);
}

int getBudget() {
    int budget;
    cout << endl;
    cout << "Enter your budget for the trip: ";
    while (!(cin >> budget)) {
        cout << "Please enter a valid budget: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return budget;
}

float convertToPKR(char nationality) {
    if (nationality == 'N') {
        return 1.0;
    }
    else if (nationality == 'I') {
        char currencyChoice;
        cout << "Do you have dollars or euros? Enter 'D' for dollars or 'E' for euros: ";
        cin >> currencyChoice;

        if (toupper(currencyChoice) == 'D') {
            return ccmode.DOLLAR_TO_PKR;
        }
        else if (toupper(currencyChoice) == 'E') {
            return ccmode.EURO_TO_PKR;
        }
        else {
            cout << "Invalid currency choice!" << endl;
            return 1.0;
        }
    }
    else {
        cout << "Invalid nationality choice! Please enter 'N' for national or 'I' for international: ";
        cin >> nationality;
        nationality = toupper(nationality);  // Convert to uppercase for consistency
    }
}

void displayLocations() {
    cout << "SELECT TORUIST SPOT " << endl;
    cout << "1. KASHMIR" << endl;
    cout << "2. GILGIT-BALTITSTAN" << endl;
    cout << "3. MURREE" << endl;
    cout << "4. NARAN & KAGHAN :" << endl;
}

void displayKashmirPlaces() {
    cout << "PLACES YOU'LL GONNA VISIT IN KASHMIR " << endl;
    cout << " - SRINAGAR - " << endl;
    cout << " - GULMARG - " << endl;
    cout << " - PAHALGAM - " << endl;
}

void displayGilgitBaltistanPlaces() {
    cout << "PLACES YOU'LL GONNA VISIT IN GILGIT~BALTISTAN: " << endl;
    cout << " - HUNZA VALLEY - " << endl;
    cout << " - SKARDU - " << endl;
    cout << " - FAIRY MEADOWS- " << endl;
}

void displayMuree() {
    cout << "PLACES YOU'LL GONNA VISIT IN MURREE: " << endl;
    cout << " - MALL ROAD - " << endl;
    cout << " - PATRIATA - " << endl;
    cout << " - PINDI POINT - " << endl;
}

void displayNARANKAGHAN()
{
    cout << "PLACES YOU'LL GONNA VISIT IN NARAN KAGHAN: " << endl;
    cout << " - ANSOO LAKE - " << endl;
    cout << " - SIRI PAYE MEADOWS - " << endl;
    cout << " - SAIF~UL~MALOOK - " << endl;
}
int getHotelType()
{
    int hotelType;
    cout << "Select hotel type:" << endl;
    cout << "1. Budget Hotel (Rs. " << htmode.BUDGET_HOTEL << " per day)" << endl;
    cout << "2. Mid-range Hotel (Rs. " << htmode.MID_RANGE_HOTEL << " per day)" << endl;
    cout << "3. Luxury Hotel (Rs. " << htmode.LUXURY_HOTEL << " per day)" << endl;
    cin >> hotelType;
    return hotelType;
}

int calculateHotelExpenses(int numDays, int hotelType)
{
    switch (hotelType) {
    case 1:
        return numDays * htmode.BUDGET_HOTEL;
    case 2:
        return numDays * htmode.MID_RANGE_HOTEL;
    case 3:
        return numDays * htmode.LUXURY_HOTEL;
    default:
        cout << "Invalid hotel type!" << endl;
        return -1;
    }
}

int getTravelType()
{
    int travelType;
    cout << "Select travel type:" << endl;
    cout << "1. Air Travel (Rs. " << ttmode.AIR_TRAVEL_COST << " per person)" << endl;
    cout << "2. Road Travel (Rs. " << ttmode.ROAD_TRAVEL_COST << " per person)" << endl;
    cin >> travelType;
    return travelType;
}

int calculateTravelExpenses(int numPerson, int travelType)
{
    switch (travelType)
    {
    case 1:
        return numPerson * ttmode.AIR_TRAVEL_COST;
    case 2:
        return numPerson * ttmode.ROAD_TRAVEL_COST;
    default:
        cout << " INVALID TRAVEL TYPE : " << endl;
        return -1;
    }
}

void displayTotalExpenses(int totalExpenses) {
    cout << "Your total estimated expenses are: Rs. " << totalExpenses << endl;
}

void displayEmergencyContacts()
{
    cout << "\033[31m Emergency Contacts: \033[0m" << endl;
    cout << "\033[31m - Police: 15 \033[0m" << endl;
    cout << "\033[31m - Ambulance: 115 \033[0m" << endl;
    cout << "\033[31m - Fire Brigade : 16 \033[0m" << endl;
}

float getUserRating() {
    float rating;
    cout << "Please rate our system (1.0 to 5.0): ";
    cin >> rating;
    return rating;
}

void storeCustomerInfo(int budget, int locationChoice, int hotelType, int travelType, int numDays, int numPerson, int totalExpenses, float rating) {
    ofstream file("customer_info.txt", ios::app);
    if (!file) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    file << "Budget: " << budget << " PKR" << endl;
    file << "Location Choice: " << locationChoice << endl;
    file << "Hotel Type: " << hotelType << endl;
    file << "Travel Type: " << travelType << endl;
    file << "Number of Days: " << numDays << endl;
    file << "Number of People: " << numPerson << endl;
    file << "Total Expenses: " << totalExpenses << " PKR" << endl;
    file << "User Rating: " << rating << endl;
    file << "-----------------------------------" << endl;
    file.close();
}