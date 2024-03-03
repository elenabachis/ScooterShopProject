#include "ScooterUi.h"
#include "tests.h"
#include <iostream>

using namespace repository;
using namespace controller;
using namespace ui;
using namespace std;

int main() {
    call_all_tests();
    cout << "Starting application..." << endl;
    cout << "Welcome to Scooter Rental 1.0" << endl;
    int option;
    cout << "How would you like to store your data\n"
            "1. persistent storage (your data will be saved after the program ends)\n"
            "2. temporary storage (your data will not be saved after the program ends)\n"
            "3. exit\n"
            "Your option:" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            CSVFileRepository csvrepo("storage.txt");
            auto shared_csvrepo = make_shared<CSVFileRepository>(csvrepo);
            Controller controller1(shared_csvrepo);
            UI ui1(controller1);
            ui1.run();
            break;
        }
        case 2: {
            InMemoryRepository repo;
            auto shared_repo = make_shared<InMemoryRepository>(repo);
            Controller controller2(shared_repo);
            UI ui2(controller2);
            ui2.run();
            break;
        }
        case 3: {
            cout << "Exiting the program... Goodbye!" << endl;
            return 0;
        }
        default:
            cout << "Sorry! Invalid input!!!Try again!" << endl;
            break;
    }
    return 0;
}
