/*
PIC 10B Homework 4, SalariedWorker.h
Author: Johnathan Harding
Date: 1/31/2022
*/

#ifndef __SALARIEDWORKER_H__ //header guards to prevent compile-time error
#define __SALARIEDWORKER_H__

#include "Employee.h"
#include <string> 
#include <fstream>

/**
@class SalariedWorker A class derived from Employee but specialized for holding data about salaried workers.
This class also holds data about a worker's salary, refined versions of some Employee class functions,
and implementations for
the save() and print_pay() functions mandated within the Employee class.
*/
class SalariedWorker : public Employee {
public:
	//constructors:

	/**
	Constructor that accepts a name, email, and salary
	@param n A string to set the name of the employee to...
	@param e A string to set the email of the employee to...
	@param s A double to set the salary of the employee to...
	*/
	SalariedWorker(std::string n, std::string e, double s);

	/**
	Constructor accepting an input file stream
	@param fin The ifstream that will read for employee data.
	*/
	SalariedWorker(std::ifstream& fin);

	/**
	Accessor for private datafield salary information.
	@return Returns the salary of an implicitly passed SalaryWorker object.
	*/	
	double getSalary() const;

	/**
	Refined implementation of print_pay that prints additional information specific to this class.
	*/
	void print_pay() const final;

	/**
	A more refined version of write_data that works for additional data held by this class.
	@param fout The ofstream object to written to a file through
	*/
	void write_data(std::ofstream& fout) const final;

	/**
	Implement of the save for the HourlyWorker. Uses write_data() to write pertinent SalariedWorker
	information to the proper text file.
	*/
	void save() const final;

private:
	double salary; //the private datafield holding a SalariedWorker's salary information

};

#endif //__EMPLOYEE_H__
