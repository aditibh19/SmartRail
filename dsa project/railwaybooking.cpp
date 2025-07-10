#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

struct Train {
    string TName;
    string TID;
    string TSource;
    string TDest;
    string TDate;
    string TTime;
    int TSeats;
    int firstClassPrice;
    int secondClassPrice;
    int thirdClassPrice;
    int sleeperPrice;
    vector<string> availableSeats;
};

struct Ticket {
    int ticketID;
    string passengerName;
    string trainID;
    string seatNumber;
    int price;
};

struct User {
    string username;
    string password;
    string preferences;
};

class Graph {
public:
    void addEdge(const string& source, const string& destination, int price) {
        adjList[source].emplace_back(destination, price);
        adjList[destination].emplace_back(source, price);
    }

    vector<string> dijkstra(const string& start, const string& end) {
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        unordered_set<string> visited;

        for (const auto& pair : adjList) {
            distances[pair.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto current = pq.top(); pq.pop();
            int currentDistance = current.first;
            string currentNode = current.second;

            if (visited.count(currentNode)) continue;
            visited.insert(currentNode);

            for (const auto& neighbor : adjList[currentNode]) {
                const string& neighborNode = neighbor.first;
                int price = neighbor.second;

                int newDistance = currentDistance + price;
                if (newDistance < distances[neighborNode]) {
                    distances[neighborNode] = newDistance;
                    previous[neighborNode] = currentNode;
                    pq.push({newDistance, neighborNode});
                }
            }
        }

        vector<string> path;
        for (string at = end; at != ""; at = previous[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }

private:
    unordered_map<string, vector<pair<string, int>>> adjList;
};

class RailwayBookingSystem {
private:
    vector<Train> trains;
    unordered_map<int, Ticket> bookedTickets;
    unordered_map<string, User> users;
    string currentUser;
    int nextTicketID = 1;
    Graph trainGraph;

public:
    RailwayBookingSystem() {
        initializeTrains();
        loadUsersFromFile();
        loadBookedTicketsFromFile();
    }

    void initializeTrains();
    void displayTrains();
    void reserveTicket(Train& train);
    void cancelTicket();
    void viewBookedTickets();
    void registerUser();
    void loginUser();
    void showMenu();
    void searchTrain();
    void updateBookedTicketsFile();
    void loadBookedTicketsFromFile();
    void loadUsersFromFile();
    void updateUsersFile();
    void adminModule();
    void paymentProcessing(int amount);

    void modifyTrainSchedule();
    void searchTrainByDateOrPrice();
    void storeUserPreference(const string& preference);
};

void RailwayBookingSystem::initializeTrains() {
    trains.push_back({"Rajdhani Express", "RJD101", "Delhi", "Mumbai", "2023-12-01", "14:00", 100, 3000, 1500, 800, 500});
    trains.push_back({"Shatabdi Express", "SJD202", "Delhi", "Lucknow", "2023-12-02", "06:00", 80, 2500, 1200, 700, 400});
    trains.push_back({"Duronto Express", "DUR303", "Delhi", "Kolkata", "2023-12-03", "17:00", 150, 4000, 2000, 1000, 600});
    trains.push_back({"Maharashtra Express", "MHA404", "Mumbai", "Pune", "2023-12-04", "10:00", 120, 1500, 700, 400, 300});
    trains.push_back({"Intercity Express", "INT505", "Mumbai", "Goa", "2023-12-05", "08:00", 60, 2000, 1000, 600, 350});
trains.push_back({"Gatimaan Express", "GAT808", "Delhi", "Agra", "2023-12-08", "08:00", 100, 1500, 800, 400, 200});
trains.push_back({"Shivneri Express", "SHV909", "Mumbai", "Nagpur", "2023-12-09", "05:30", 120, 2800, 1400, 700, 450});
trains.push_back({"Rajkot Express", "RJK1010", "Rajkot", "Mumbai", "2023-12-10", "15:00", 150, 2000, 1000, 600, 300});
trains.push_back({"Mysore Express", "MYS1111", "Bangalore", "Mysore", "2023-12-11", "10:30", 80, 1200, 600, 350, 200});
trains.push_back({"Nizamuddin Express", "NZD1212", "Delhi", "Hyderabad", "2023-12-12", "16:00", 100, 3500, 1800, 900, 500});
trains.push_back({"Kota Express", "KOT1313", "Kota", "Delhi", "2023-12-13", "07:00", 90, 1000, 500, 300, 150});
trains.push_back({"Chennai Express", "CHE1414", "Chennai", "Mumbai", "2023-12-14", "20:00", 150, 2500, 1200, 600, 350});
trains.push_back({"Patna Express", "PAT1515", "Patna", "Delhi", "2023-12-15", "22:00", 120, 2200, 1100, 550, 300});
trains.push_back({"Kolkata Mail", "KOL1616", "Kolkata", "Delhi", "2023-12-16", "18:00", 200, 3000, 1500, 800, 400});
trains.push_back({"Surat Express", "SUR1717", "Surat", "Mumbai", "2023-12-17", "09:00", 130, 1800, 900, 500, 250});
trains.push_back({"Varanasi Express", "VAR1818", "Varanasi", "Delhi", "2023-12-18", "10:00", 100, 2600, 1300, 700, 350});
trains.push_back({"Amritsar Express", "AMR1919", "Amritsar", "Delhi", "2023-12-19", "12:00", 150, 3000, 1500, 800, 400});
trains.push_back({"Bhuj Express", "BHU2020", "Bhuj", "Ahmedabad", "2023-12-20", "15:30", 80, 900, 500, 300, 150});
trains.push_back({"Satyagrah Express", "SAT2121", "Bhopal", "Delhi", "2023-12-21", "20:00", 120, 1500, 800, 400, 200});
trains.push_back({"Kanyakumari Express", "KNY2222", "Kanyakumari", "Delhi", "2023-12-22", "16:00", 100, 4000, 2000, 1000, 600});
trains.push_back({"Kochuveli Express", "KOV2323", "Kochuveli", "Delhi", "2023-12-23", "11:00", 150, 3500, 1700, 850, 450});
trains.push_back({"Latur Express", "LAT2424", "Latur", "Mumbai", "2023-12-24", "09:00", 100, 1300, 650, 350, 180});
trains.push_back({"Puducherry Express", "PUD2525", "Puducherry", "Chennai", "2023-12-25", "13:00", 90, 1200, 600, 300, 150});
trains.push_back({"Nanded Express", "NAN2626", "Nanded", "Mumbai", "2023-12-26", "22:30", 80, 1500, 800, 400, 200});
trains.push_back({"Jammu Tawi Express", "JAM2727", "Jammu", "Delhi", "2023-12-27", "17:00", 150, 3300, 1700, 850, 500});
trains.push_back({"Bangalore Express", "BLR2828", "Bangalore", "Delhi", "2023-12-28", "21:00", 120, 4000, 2000, 1000, 600});
trains.push_back({"Kolkata Superfast", "KOS2929", "Kolkata", "Delhi", "2023-12-29", "23:00", 100, 3200, 1600, 800, 400});
trains.push_back({"Udaipur Express", "UDA3030", "Udaipur", "Delhi", "2023-12-30", "15:00", 90, 2700, 1350, 675, 350});

    for (auto& train : trains) {
        for (int i = 1; i <= train.TSeats; i++) {
            train.availableSeats.push_back(to_string(i));
        }
    }

    trainGraph.addEdge("Delhi", "Mumbai", 1500);
    trainGraph.addEdge("Delhi", "Lucknow", 800);
    trainGraph.addEdge("Delhi", "Kolkata", 2000);
    trainGraph.addEdge("Mumbai", "Pune", 300);
    trainGraph.addEdge("Mumbai", "Goa", 900);
    trainGraph.addEdge("Delhi", "Agra", 200);
trainGraph.addEdge("Mumbai", "Nagpur", 900);
trainGraph.addEdge("Rajkot", "Mumbai", 450);
trainGraph.addEdge("Bangalore", "Mysore", 150);
trainGraph.addEdge("Delhi", "Hyderabad", 2000);
trainGraph.addEdge("Kota", "Delhi", 300);
trainGraph.addEdge("Chennai", "Mumbai", 1800);
trainGraph.addEdge("Patna", "Delhi", 1000);
trainGraph.addEdge("Kolkata", "Delhi", 1500);
trainGraph.addEdge("Surat", "Mumbai", 250);
trainGraph.addEdge("Varanasi", "Delhi", 800);
trainGraph.addEdge("Amritsar", "Delhi", 400);
trainGraph.addEdge("Bhuj", "Ahmedabad", 700);
trainGraph.addEdge("Bhopal", "Delhi", 700);
trainGraph.addEdge("Kanyakumari", "Delhi", 2800);
trainGraph.addEdge("Kochuveli", "Delhi", 2900);
trainGraph.addEdge("Latur", "Mumbai", 450);
trainGraph.addEdge("Puducherry", "Chennai", 200);
trainGraph.addEdge("Nanded", "Mumbai", 300);
trainGraph.addEdge("Jammu", "Delhi", 600);
trainGraph.addEdge("Bangalore", "Delhi", 1800);
trainGraph.addEdge("Kolkata", "Delhi", 1500);
trainGraph.addEdge("Udaipur", "Delhi", 700);

}

void RailwayBookingSystem::displayTrains() {
    cout << "Available Trains:\n";
    for (const auto& train : trains) {
        cout << "Train Name: " << train.TName 
             << ", Train ID: " << train.TID 
             << ", Source: " << train.TSource 
             << ", Destination: " << train.TDest 
             << ", Date: " << train.TDate 
             << ", Time: " << train.TTime 
             << ", Seats Available: " << train.TSeats 
             << ", First Class Price: " << train.firstClassPrice 
             << ", Second Class Price: " << train.secondClassPrice 
             << ", Third Class Price: " << train.thirdClassPrice 
             << ", Sleeper Price: " << train.sleeperPrice << endl;
    }
}
void RailwayBookingSystem::searchTrain() {
    string from, to;
    cout << "Enter departure station: ";
    cin >> from;
    cout << "Enter destination station: ";
    cin >> to;

    vector<string> path = trainGraph.dijkstra(from, to);
    if (path.empty() || path[0] != from) {
        cout << "No path found from " << from << " to " << to << endl;
        return;
    }

    cout << "Shortest path from " << from << " to " << to << ": ";
    for (const string& station : path) {
        cout << station << " ";
    }
    cout << endl;

    cout << "Available trains:\n";
    vector<Train> availableTrains;
    for (const Train& train : trains) {
        if (train.TSource == from && train.TDest == to) {
            availableTrains.push_back(train);
            cout << "Train Name: " << train.TName 
                 << ", Train ID: " << train.TID 
                 << ", Date: " << train.TDate 
                 << ", Time: " << train.TTime 
                 << ", Seats Available: " << train.TSeats << endl;
        }
    }

    if (availableTrains.empty()) {
        cout << "No trains available for this route.\n";
        return;
    }

    string bookChoice;
    cout << "Would you like to book a ticket for one of these trains? (yes/no): ";
    cin >> bookChoice;

    if (bookChoice == "yes") {
        string trainID;
        cout << "Enter Train ID to book: ";
        cin >> trainID;

        auto it = find_if(availableTrains.begin(), availableTrains.end(), [&trainID](const Train& t) { return t.TID == trainID; });
        if (it != availableTrains.end()) {
            reserveTicket(*it);
        } else {
            cout << "Invalid Train ID!\n";
        }
    }
}


void RailwayBookingSystem::reserveTicket(Train& train) {
    if (train.TSeats <= 0) {
        cout << "No seats available for this train!\n";
        return;
    }

    string passengerName = currentUser;
    cout << "Booking for user: " << passengerName << endl;

    int price;
    cout << "Select class (1. First Class, 2. Second Class, 3. Third Class, 4. Sleeper): ";
    int classChoice;
    cin >> classChoice;

    switch (classChoice) {
        case 1: price = train.firstClassPrice; break;
        case 2: price = train.secondClassPrice; break;
        case 3: price = train.thirdClassPrice; break;
        case 4: price = train.sleeperPrice; break;
        default: 
            cout << "Invalid choice! Defaulting to First Class.\n";
            price = train.firstClassPrice;
            break;
    }

    cout << "Available seats: ";
    for (const auto& seat : train.availableSeats) {
        cout << seat << " ";
    }
    cout << endl;

    string seatNumber;
    cout << "Select a seat number: ";
    cin >> seatNumber;

    if (find(train.availableSeats.begin(), train.availableSeats.end(), seatNumber) == train.availableSeats.end()) {
        cout << "Invalid seat number!\n";
        return;
    }

    paymentProcessing(price);

    Ticket newTicket = { nextTicketID++, passengerName, train.TID, seatNumber, price };
    bookedTickets[newTicket.ticketID] = newTicket;

    train.availableSeats.erase(remove(train.availableSeats.begin(), train.availableSeats.end(), seatNumber), train.availableSeats.end());
    train.TSeats--;

    cout << "Ticket booked successfully! Ticket ID: " << newTicket.ticketID << ", Price: " << newTicket.price << endl;
    updateBookedTicketsFile();
}

void RailwayBookingSystem::paymentProcessing(int amount) {
    cout << "Processing payment of " << amount << "...\n";
    cout << "Payment successful!\n";
}

void RailwayBookingSystem::cancelTicket() {
    if (currentUser.empty()) {
        cout << "You must be logged in to cancel a ticket.\n";
        return;
    }

    int ticketID;
    cout << "Enter Ticket ID to cancel: ";
    cin >> ticketID;

    if (bookedTickets.erase(ticketID)) {
        cout << "Ticket cancelled successfully.\n";
        updateBookedTicketsFile();
    } else {
        cout << "Invalid Ticket ID!\n";
    }
}

void RailwayBookingSystem::viewBookedTickets() {
    if (currentUser.empty()) {
        cout << "You must be logged in to view booked tickets.\n";
        return;
    }

    cout << "Booked Tickets for " << currentUser << ":\n";
    for (const auto& pair : bookedTickets) {
        const Ticket& ticket = pair.second;
        if (ticket.passengerName == currentUser) {
            cout << "Ticket ID: " << ticket.ticketID 
                 << ", Train ID: " << ticket.trainID 
                 << ", Seat Number: " << ticket.seatNumber 
                 << ", Price: " << ticket.price << endl;
        }
    }
}

void RailwayBookingSystem::registerUser() {
    User newUser;
    cout << "Enter username: ";
    cin >> newUser.username;
    cout << "Enter password: ";
    cin >> newUser.password;
    cout << "Enter preferences (optional): ";
    cin.ignore(); // Clear the newline from previous input
    getline(cin, newUser.preferences);

    if (users.find(newUser.username) != users.end()) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    users[newUser.username] = newUser;
    updateUsersFile();
    cout << "Registration successful!\n";
}

void RailwayBookingSystem::loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second.password == password) {
        currentUser = username;
        cout << "Login successful!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void RailwayBookingSystem::loadBookedTicketsFromFile() {
    ifstream infile("booked_tickets.txt");
    if (infile) {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            Ticket ticket;
            ss >> ticket.ticketID >> ticket.passengerName >> ticket.trainID >> ticket.seatNumber >> ticket.price;
            bookedTickets[ticket.ticketID] = ticket;
            if (ticket.ticketID >= nextTicketID) {
                nextTicketID = ticket.ticketID + 1;
            }
        }
    }
}


void RailwayBookingSystem::updateBookedTicketsFile() {
    ofstream outfile("booked_tickets.txt");
    for (const auto& pair : bookedTickets) {
        const Ticket& ticket = pair.second;
        outfile << ticket.ticketID << " " 
                << ticket.passengerName << " "
                << ticket.trainID << " "
                << ticket.seatNumber << " "
                << ticket.price << endl;
    }
}
void RailwayBookingSystem::loadUsersFromFile() {
    ifstream infile("users.txt");
    if (infile) {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            User user;
            ss >> user.username >> user.password;
            getline(ss, user.preferences); // Read the entire line for preferences
            users[user.username] = user;
        }
    }
}



void RailwayBookingSystem::updateUsersFile() {
    ofstream outfile("users.txt");
    for (const auto& pair : users) {
        const User& user = pair.second;
        outfile << user.username << " " 
                << user.password << " "
                << user.preferences << endl;
    }
}

void RailwayBookingSystem::adminModule() {
    cout << "Admin Module:\n";
    modifyTrainSchedule();
}

void RailwayBookingSystem::modifyTrainSchedule() {
    string trainID;
    cout << "Enter Train ID to modify: ";
    cin >> trainID;

    auto it = find_if(trains.begin(), trains.end(), [&trainID](const Train& t) { return t.TID == trainID; });
    if (it != trains.end()) {
        cout << "Current Schedule: " << it->TDate << " " << it->TTime << endl;
        cout << "Enter new Date (YYYY-MM-DD): ";
        cin >> it->TDate;
        cout << "Enter new Time (HH:MM): ";
        cin >> it->TTime;
        cout << "Train schedule updated successfully.\n";
    } else {
        cout << "Train not found!\n";
    }
}

void RailwayBookingSystem::showMenu() {
    int choice;
    do {
        cout << "1. View Trains\n"
             << "2. Register User\n"
             << "3. Login User\n"
             << "4. Reserve Ticket\n"
             << "5. Cancel Ticket\n"
             << "6. View Booked Tickets\n"
             << "7. Search Train\n"
             << "8. Admin Module\n"
             << "9. Exit\n"
             << "Enter your choice: ";
             
        cin >> choice;

        switch (choice) {
            case 1: displayTrains(); break;
            case 2: registerUser(); break;
            case 3: loginUser(); break;
            case 4: {
                string trainID;
                cout << "Enter Train ID to book: ";
                cin >> trainID;
                auto it = find_if(trains.begin(), trains.end(), [&trainID](const Train& t) { return t.TID == trainID; });
                if (it != trains.end()) {
                    reserveTicket(*it);
                } else {
                    cout << "Train not found!\n";
                }
                break;
            }
            case 5: cancelTicket(); break;
            case 6: viewBookedTickets(); break;
            case 7: searchTrain(); break;
            case 8: adminModule(); break;
            case 9: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n"; break;
        }
    } while (choice != 9);
}

int main() {
    RailwayBookingSystem system;
    system.showMenu();
    return 0;
}
