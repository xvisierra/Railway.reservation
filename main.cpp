#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

const string ADMIN_PASSWORD = "admin";
unordered_map<string, string> users;

void loadUsers() {
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        string username, password;
        while (userFile >> username >> password) {
            users[username] = password;
        }
        userFile.close();
    }
}

void saveUser(const string& username, const string& password) {
    users[username] = password;
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        userFile << username << " " << password << endl;
        userFile.close();
    }
    else {
        cout << "Unable to open user file!" << endl;
    }
}

void userMenu() {
    cout << "\nUser Menu:\n";
    cout << "1. Display all trains\n";
    cout << "2. Search for a train\n";
    cout << "3. Reserve a seat\n";
    cout << "4. View reservations\n";
    cout << "5. Exit user menu\n";
}

void adminMenu() {
    cout << "\nAdmin Menu:\n";
    cout << "1. Add a new user\n";
    cout << "2. View all users\n";
    cout << "3. View all trains\n";
    cout << "4. Search for a train\n";
    cout << "5. Add a new train\n";
    cout << "6. Modify a train\n";
    cout << "7. Delete a train\n";
    cout << "8. View reservations\n";
    cout << "9. Exit admin menu\n";
}

void displayAllTrains() {
    ifstream trainFile("trains.txt");
    if (trainFile.is_open()) {
        string line;
        while (getline(trainFile, line)) {
            cout << line << endl;
        }
        trainFile.close();
    }
    else {
        cout << "Unable to open train file!" << endl;
    }
}

void searchTrain() {
    string trainNumber;
    cout << "Enter train number: ";
    getline(cin, trainNumber);

    ifstream trainFile("trains.txt");
    if (trainFile.is_open()) {
        string line;
        bool found = false;
        while (getline(trainFile, line)) {
            if (line.find("Train Number: " + trainNumber) != string::npos) {
                found = true;
                cout << line << endl;
                break;
            }
        }
        if (!found) {
            cout << "Train not found!" << endl;
        }
        trainFile.close();
    }
    else {
        cout << "Unable to open train file!" << endl;
    }
}

void reserveSeat(const string& username) {
    string trainNumber;
    cout << "Enter train number: ";
    getline(cin, trainNumber);

    ifstream trainFile("trains.txt");
    if (trainFile.is_open()) {
        string line;
        bool found = false;
        while (getline(trainFile, line)) {
            if (line.find("Train Number: " + trainNumber) != string::npos) {
                found = true;
                cout << "Enter number of seats to reserve: ";
                int numSeats;
                cin >> numSeats;
                cin.ignore();

                ofstream reservationFile("reservations.txt", ios::app);
                if (reservationFile.is_open()) {
                    reservationFile << "Username: " << username << ", Train Number: " << trainNumber << ", Number of Seats: " << numSeats << endl;
                    reservationFile.close();
                    cout << "Reservation successful!" << endl;
                }
                else {
                    cout << "Unable to open reservation file!" << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "Train not found!" << endl;
        }
        trainFile.close();
    }
    else {
        cout << "Unable to open train file!" << endl;
    }
}

void viewReservations() {
    ifstream reservationFile("reservations.txt");
    if (reservationFile.is_open()) {
        string line;
        while (getline(reservationFile, line)) {
            cout << line << endl;
        }
        reservationFile.close();
    }
    else {
        cout << "Unable to open reservation file!" << endl;
    }
}

void addTrain() {
    cout << "\nAdding a new train:\n";
    string trainName, trainNumber, departingStation, lastStation;
    int totalSeats, farePerSeat;

    cout << "Enter train name: ";
    getline(cin, trainName);
    cout << "Enter train number: ";
    getline(cin, trainNumber);
    cout << "Enter departing station: ";
    getline(cin, departingStation);
    cout << "Enter last station: ";
    getline(cin, lastStation);
    cout << "Enter total seats: ";
    cin >> totalSeats;
    cout << "Enter fare per seat: ";
    cin >> farePerSeat;
    cin.ignore();

    ofstream trainFile("trains.txt", ios::app);
    if (trainFile.is_open()) {
        trainFile << "Train Name: " << trainName << ", Train Number: " << trainNumber
                  << ", Departing Station: " << departingStation << ", Last Station: " << lastStation
                  << ", Total Seats: " << totalSeats << ", Fare per Seat: " << farePerSeat << endl;
        trainFile.close();
        cout << "Train added successfully!" << endl;
    }
    else {
        cout << "Unable to open train file!" << endl;
    }
}

void modifyTrain() {
    string trainNumber;
    cout << "Enter train number to modify: ";
    getline(cin, trainNumber);

    ifstream trainFile("trains.txt");
    if (trainFile.is_open()) {
        string line;
        bool found = false;
        ofstream tempFile("temp.txt");
        if (tempFile.is_open()) {
            while (getline(trainFile, line)) {
                if (line.find("Train Number: " + trainNumber) != string::npos) {
                    found = true;
                    string trainName, departingStation, lastStation;
                    int totalSeats, farePerSeat;

                    cout << "Enter new train name: ";
                    getline(cin, trainName);
                    cout << "Enter new departing station: ";
                    getline(cin, departingStation);
                    cout << "Enter new last station: ";
                    getline(cin, lastStation);
                    cout << "Enter new total seats: ";
                    cin >> totalSeats;
                    cout << "Enter new fare per seat: ";
                    cin >> farePerSeat;
                    cin.ignore();

                    tempFile << "Train Name: " << trainName << ", Train Number: " << trainNumber
                             << ", Departing Station: " << departingStation << ", Last Station: " << lastStation
                             << ", Total Seats: " << totalSeats << ", Fare per Seat: " << farePerSeat << endl;
                    cout << "Train modified successfully!" << endl;
                }
                else {
                    tempFile << line << endl;
                }
            }
            if (!found) {
                cout << "Train not found!" << endl;
            }
            trainFile.close();
            tempFile.close();
            remove("trains.txt");
            rename("temp.txt", "trains.txt");
        }
        else {
            cout << "Unable to open temporary file!" << endl;
        }
    }
    else {
        cout << "Unable to open train file!" << endl;
    }
}

void deleteTrain() {
    string trainNumber;
    cout << "Enter train number to delete: ";
    getline(cin, trainNumber);

    ifstream trainFile("trains.txt");
    if (trainFile.is_open()) {
        string line;
        bool found = false;
        ofstream tempFile("temp.txt");
        if (tempFile.is_open()) {
            while (getline(trainFile, line)) {
                if (line.find("Train Number: " + trainNumber) != string::npos) {
                    found = true;
                    cout << "Train deleted successfully!" << endl;
                }
                else {
                    tempFile << line << endl;
                }
            }
            if (!found) {
                cout << "Train not found!" << endl;
            }
            trainFile.close();
            tempFile.close();
            remove("trains.txt");
            rename("temp.txt", "trains.txt");
        }
        else {
            cout << "Unable to open temporary file!" << endl;
        }
    }
    else {
        cout << "Unable to open train file!" << endl;
    }
}

int main() {
    loadUsers();

    while (true) {
        cout << "\nWelcome to Railway Reservation System!\n";
        cout << "1. User Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\nUser Login\n";
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            auto it = users.find(username);
            if (it != users.end() && it->second == password) {
                cout << "Login successful! Welcome, " << username << "!" << endl;

                while (true) {
                    userMenu();
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cin.ignore();

                    if (choice == 1) {
                        cout << "\nDisplaying all trains:\n";
                        displayAllTrains();
                    }
                    else if (choice == 2) {
                        cout << "\nSearching for a train:\n";
                        searchTrain();
                    }
                    else if (choice == 3) {
                        cout << "\nReserving a seat:\n";
                        reserveSeat(username);
                    }
                    else if (choice == 4) {
                        cout << "\nViewing reservations:\n";
                        viewReservations();
                    }
                    else if (choice == 5) {
                        cout << "Exiting user menu..." << endl;
                        break;
                    }
                    else {
                        cout << "Invalid choice! Please try again." << endl;
                    }
                }
            }
            else {
                cout << "Invalid username or password. Please try again!" << endl;
            }
        }
        else if (choice == 2) {
            cout << "\nAdmin Login\n";
            string password;
            cout << "Enter admin password: ";
            getline(cin, password);

            if (password == ADMIN_PASSWORD) {
                cout << "Login successful! Welcome, Admin!" << endl;

                while (true) {
                    adminMenu();
                    cout<< "Enter your choice: ";
                    cin >> choice;
                    cin.ignore();

                    if (choice == 1) {
                        cout << "\nAdding a new user:\n";
                        string username, password;
                        cout << "Enter username: ";
                        getline(cin, username);
                        cout << "Enter password: ";
                        getline(cin, password);
                        saveUser(username, password);
                        cout << "User added successfully!" << endl;
                    }
                    else if (choice == 2) {
                        cout << "\nViewing all users:\n";
                        for (const auto& user : users) {
                            cout << "Username: " << user.first << ", Password: " << user.second << endl;
                        }
                    }
                    else if (choice == 3) {
                        cout << "\nViewing all trains:\n";
                        displayAllTrains();
                    }
                    else if (choice == 4) {
                        cout << "\nSearching for a train:\n";
                        searchTrain();
                    }
                    else if (choice == 5) {
                        addTrain();
                    }
                    else if (choice == 6) {
                        cout << "\nModifying a train:\n";
                        modifyTrain();
                    }
                    else if (choice == 7) {
                        cout << "\nDeleting a train:\n";
                        deleteTrain();
                    }
                    else if (choice == 8) {
                        cout << "\nViewing reservations:\n";
                        viewReservations();
                    }
                    else if (choice == 9) {
                        cout << "Exiting admin menu..." << endl;
                        break;
                    }
                    else {
                        cout << "Invalid choice! Please try again." << endl;
                    }
                }
            }
            else {
                cout << "Invalid password. Please try again!" << endl;
            }
        }
        else if (choice == 3) {
            cout << "Exiting the program..." << endl;
            break;
        }
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
