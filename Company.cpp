/*
PIC 10B Homework 4, Company.cpp
Author: Johnathan Harding
Date: 1/31/2022
*/

#include "Employee.h" //including necessary header files
#include "HourlyWorker.h"
#include "SalariedWorker.h"
#include "Company.h"

using namespace std; //allows me to use std abbreviations

//********************************************************************************************//
//find_next_id() IMPLEMENTATION find_next_id() IMPLEMENTATION find_next_id() IMPLEMENTATION               //
//********************************************************************************************//
//finds the value that ought to be used for the next employee's ID number
int find_next_id() {
    int fileNumber = 0; //first file opened: employee0.txt
    while (true) { //repeat until break
        string fileToAttempt = "employee"; //setting up appropriate file based on id #
        string whichFile = to_string(fileNumber);
        fileToAttempt += whichFile;
        fileToAttempt += ".txt"; //all to make proper file name based on iteration 

        ifstream fin;
        fin.open(fileToAttempt);
        if (fin.fail()) //checking if in valid state after attempt
        {
            break;
        } //if can't open any more files, break the loop
        else
        {
            fileNumber++;
        } //if can open, increase so tries to open next file in next iteration
        fin.close(); //close the stream
    }
    //return the number of the file which failed to open, and thus proper next ID value
    return fileNumber; 
}

//************************************************************************************//
//EMPLOYEE IMPLEMENTATIONS EMPLOYEE IMPLEMENTATIONS EMPLOYEE IMPLEMENTATIONS
//************************************************************************************//

//static member variable next_id initialization, accessor, and mutator
    //initialized to the proper next_id value
    int Employee::next_id = find_next_id();

    int Employee::getNextID() {return next_id; } //for use in employee constructors
    void Employee::upNextID() { next_id++; } //for after making new employee, 

//constructor that accepts strings name and email
Employee::Employee(string n, string e) : name(move(n)), email(move(e)), id(getNextID()) {
    upNextID(); //to increase next_id value by 1, we have added employee!
}

    //mutators
    void Employee::setName(const std::string& n) { name = n; }
    void Employee::setEmail(const std::string& e) { email = e; }
    void Employee::setID(int _id) { id = _id; }

    //accessors
    string Employee::getName() const { return name; }
    string Employee::getEmail() const { return email; }
    int Employee::getID() const { return id; }

//constructor that accepts an ifstream and initializes
Employee::Employee(ifstream& fin) {
    /*read in employee type (irrelevant to Employee class constructor, 
    but we need to move the stream pointer forward*/
    string empType = "";
    getline(fin, empType, '\t'); 
   
    //read-in the full name with spaces via getline()
    string fullName = "";
    getline(fin, fullName, '\t');

    //read-in employ email from file
    string email = "";
    fin >> email;

    //read-in employee ID from file
    int _id = 0;
    fin >> _id;

    this->setName(fullName); //setting employee info
    this->setEmail(email);
    this->setID(_id); 

}

/*prints the information of an employee to console : [NAME] [TAB] [ID] [TAB] [EMAIL],
uses the accessors to grab private datafields*/
void Employee::print() {
    cout << this->getName() << '\t' << this->getID() << '\t' << this->getEmail() << "\n";
}

/*that writes the name, email, and id of the Employee to a file, 
each entry separated by a tab*/
void Employee::write_data(ofstream& fout) const {
    fout << this->getName() << '\t' << this->getID() << '\t' << this->getEmail() << "\n";
}

//************************************************************************************//
//HOURLYWORKER IMPLEMENTATIONS HOURLYWORKER IMPLEMENTATIONS HOURLYWORKER IMPLEMENTATIONS
//************************************************************************************//

/*constructor accepting a name, email, and hourly rate, setting the hours
worked to 0 initially;*/
HourlyWorker::HourlyWorker(std::string n, std::string e, double r) : 
    Employee(move(n), move(e)), rate(r), hours(0) {}

/*constructor accepting an input file stream to read in the name, id, email,
hours worked, and hourly rate;*/
HourlyWorker::HourlyWorker(ifstream& fin) :
    Employee(fin) {
    //fins from the position retained after Employee() called...
    fin >> hours;
    fin >> rate;
}

//to set the number of hours someone worked
void HourlyWorker::set_hours(double i) {
    this->hours = i;
}

//uses public accessors to grab datafields and print them
void HourlyWorker::print_pay() const {
    cout << this->getName() << " receives $" << (this->rate * this->hours) << "\n";
}

//writes employee data to proper file
void HourlyWorker::write_data(ofstream& fout) const {
    fout << "hourly\t" << this->getName() << "\t" << this->getEmail() << "\t"
        << this->getID() << "\t" << this->hours << "\t" << this->rate;
}

//saves employee data to proper file using ofstream and fout
void HourlyWorker::save() const {
    string fileName = "employee"; //setting up appropriate file based on id #
    string fileNumber = to_string(this->getID());
    fileName += fileNumber;
    fileName += ".txt";

    ofstream fout; //opening proper file
    fout.open(fileName);
    if (fout.fail()) //checking if in valid state
        { cout << "Error opening ofstream";  }
    HourlyWorker::write_data(fout); //saving
    fout.close();
}

//********************************************************************************************//
//SALARIEDWORKER IMPLEMENTATIONS SALARIEDWORKER IMPLEMENTATIONS SALARIEDWORKER IMPLEMENTATIONS//
//********************************************************************************************//

//constructor accepting name, email, and salary data directly
SalariedWorker::SalariedWorker(string n, string e, double s) : 
    Employee(move(n), move(e)), salary(s) {}

//constructor that makes a worker from a passed ifstream, reading from a file
SalariedWorker::SalariedWorker(ifstream& fin) : 
    Employee(fin) {
    fin >> salary;
}

//getter that returns a worker's salary information
double SalariedWorker::getSalary() const { return this->salary; }

//allows printing of a salaried worker's pay
void SalariedWorker::print_pay() const {
    cout << this->getName() << " receives $" << (this->getSalary()) << "\n";
}

//more refined version of write_data, special for SalariedWorker class
void SalariedWorker::write_data(std::ofstream& fout) const {
    fout << "salaried\t" << this->getName() << "\t" << this->getEmail() << "\t"
        << this->getID() << "\t" << this->getSalary();
}

//saves a SalariedWorker's information to a file
void SalariedWorker::save() const {
    string fileName = "employee"; //setting up appropriate file based on id #
    string fileNumber = to_string(this->getID());
    fileName += fileNumber;
    fileName += ".txt";

    ofstream fout; //opening proper file
    fout.open(fileName);
    if (fout.fail()) //checking the stream is in valid state
        {cout << "Error opening ofstream";}
    SalariedWorker::write_data(fout); //saving employee data
    fout.close();
}

//********************************************************************************************//
//COMPANY IMPLEMENTATIONS COMPANY IMPLEMENTATIONS COMPANY IMPLEMENTATIONS               //
//********************************************************************************************//

Company::Company() {
    employees = {}; //employees vector initially empty
   
    int fileNumber = 0; //file to be opened will be "employee0.txt"
    while (true) { //goes until break is called
        ifstream fin;
        string fileToAttempt = "employee"; //setting up appropriate file based on id #
        string whichFile = to_string(fileNumber);
        fileToAttempt += whichFile;
        fileToAttempt += ".txt";
        fin.open(fileToAttempt); //try to open the file
        if (fin.fail())
            {break;} //checking if stream is in valid state/if there are no more files, breaks loop
        else
            {
                string empType; //to determine which kind of employee to make
                fin >> empType;
                fin.seekg(0); //should reset stream ptr to beginning of file...
                if (empType == "salaried")
                    {
                        SalariedWorker X(fin);  //make salaried worker

                        //uses push_back() to add to employees vector
                        std::shared_ptr<Employee> p = make_shared<SalariedWorker>(X);
                        employees.push_back(p);

                    }
                else if (empType == "hourly")
                    {
                        HourlyWorker X(fin); //make hourly worker

                        //uses push_back() to add to employees vector
                        std::shared_ptr<Employee> p = make_shared<HourlyWorker>(X);//trying with 
                        employees.push_back(p);
                    }
            }
        fin.close(); //close the file
        fileNumber++; //increases so next desired file opened for next iteration
    }
}

//makes a salaried worker
void Company::create_salaried() {
    cin.ignore(); //to discard any extra chars in stream
    string name = ""; //enter and grab entire name
    cout << "Enter name: ";
    getline(cin, name);

    string email = ""; //enter and grab email
    cout << "Enter email: ";
    cin >> email;

    double sal = 0; //enter and grab salary
    cout << "Enter salary: $";
    cin >> sal;

    SalariedWorker X(name, email, sal); //make SalariedWorker with those specs. 
    X.save(); //need to save the new employee's data to a txt file
    std::shared_ptr<Employee> p = make_shared<SalariedWorker>(X); //make sh. ptr p to it
    employees.push_back(p); //add p to employees

    cin.ignore(); //to discard any extra chars in stream
    return;
}

//to make a new hourly worker for the company
void Company::create_hourly() {
    cin.ignore();//to discard any extra chars in stream
    string name = ""; //enter and grab whole name
    cout << "Enter name: ";
    getline(cin, name);

    string email = ""; //enter and grab email
    cout << "Enter email: ";
    cin >> email;

    double rate = 0; //enter and grab ay rate
    cout << "Enter hourly rate: $";
    cin >> rate;

    HourlyWorker X(name, email, rate); //make HourlyWorker with those specs.
    X.save();//need to save the new employee's data to a txt file
    std::shared_ptr<Employee> p = make_shared<HourlyWorker>(X); //make a shared_ptr p to it
    employees.push_back(p); //add that p to employees

    return;
}

//general create employee func., appears and prompts user to choose which type
void Company::create_employee() {
    //request for user data
    cout << "What type of employee?\n" << "S - Salaried\n" << "H - Hourly\n"
        << "Abort (all other inputs)?";
    string empType = ""; //to choose which type
    cin >> empType;
    if (empType == "S") //if the user chooses to make a SalariedWorker
    {
        this->create_salaried();
    }
    if (empType == "H") //if the user chooses to make a HourlyWorker
    {
        this->create_hourly();
    }
    else if ( (empType != "S") && (empType != "H") ) //if the user chooses neither, abort
    {
        cout << "creation aborted\n";
        return; }

    return; //after done creating employee
}

//to print all members of the company
void Company::print_directory() const {
    size_t employeeCount = 0;
    employeeCount = this->employees.size();
    cout << "There are " << employeeCount << " employees:\n"; //prints # of employees
    employeeCount = this->employees.size(); //this meaning the company implicitly passed
        for (size_t i = 0; i < employeeCount; ++i) {
            (this->employees[i])->print(); //print employee data at each index of vector
        }

}

void Company::print_payroll() const {
    size_t employeeCount = 0;
    employeeCount = this->employees.size(); //this meaning the company implicitly passed
    for (size_t i = 0; i < employeeCount; ++i) {
        (this->employees[i])->print_pay(); //print employee data at each index of vector
    }
}

//to enter the number of hours each HourlyWorker worked
void Company::do_hours() {
    size_t employeeCount = 0;
    employeeCount = this->employees.size(); //this meaning the company implicitly passed
    for (size_t i = 0; i < employeeCount; ++i) { //do for the number of employees
        shared_ptr<Employee> empPtr = this->employees[i];
        if ( shared_ptr<HourlyWorker> hourlyPtr = 
            dynamic_pointer_cast<HourlyWorker>(empPtr) ) 
            { // try to dynamically cast shared_pointer to a shared_ptr to HourlyWorker
            double hoursWorked; //to hold new # of hours worked
            cout << "How many hours did " << (this->employees[i])->getName() << " work? ";
            cin >> hoursWorked; //user input
            hourlyPtr->set_hours(hoursWorked); //setting hours for that HourlyWorker
            hourlyPtr->save();//need to save new hours to employee's txt file
        }
        else { //if is impossible tp make the cast, skip to the next iteration
            continue;
            }
    }
    return;
}

//********************************************************************************************//
// run_events() IMPLEMENTATION run_events() IMPLEMENTATION run_events() IMPLEMENTATION               //
//********************************************************************************************//
void run_events() {
    Company JohnCorp; //makes a company called JohnCorp.
    while (true) {//goes until break command made
        //prints user input request and menu of options
        cout << "What would you like to do?\n" << "C - Create Employee\n" <<
            "D - Display Current Directory\n" << "H - Set Hours\n"
            << "P - Print Payroll\n" << "Quit (all other inputs)?";
        string entry = ""; //to hold user input
        cin >> entry;
        if (entry == "C") { //if user wants to make a new employee
            cin.ignore(); //to discard extra chars in the stream
            JohnCorp.create_employee();
            cout << "\n";
            continue;
        }
        if (entry == "D") { //if user wants to make a new employee
            cin.ignore(); //to discard extra chars in the stream
            JohnCorp.print_directory();
            cout << "\n";
            continue;
        }
        if (entry == "H") { //if user wants to set the hours worked for HourlyWorkers
            cin.ignore(); //to discard extra chars in the stream
            JohnCorp.do_hours();
            cout << "\n";
            continue;
        }
        if (entry == "P") { //if user wants to to see how much each employee is to be paid
            cin.ignore(); //to discard extra chars in the stream
            JohnCorp.print_payroll();
            cout << "\n";
            continue;
        }
        else //any other output, quits by returning to main
        {
            break; //cuts loop, goes back to run_events (was return statement)
        }
    }
    return; //terminates and returns to main
}