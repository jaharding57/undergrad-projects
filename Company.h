/*
PIC 10B Homework 4, Company.h
Author: Johnathan Harding
Date: 1/31/2022
*/

#ifndef __COMPANY_H__ //header guards to prevent compile-time error
#define __COMPANY_H__

#include "Employee.h" //including neccessary header files
#include <string> 
#include <vector>
#include <memory>
#include <fstream>


int find_next_id();
void run_events();

class Company {
private:
	std::vector<std::shared_ptr<Employee>> employees;
public:
	//std::vector<std::shared_ptr<Employee>> employees;

	/*have a default constructor that reads through all the files and creates Employees
	of suitable type for each file, storing them as pointers;*/
	Company();

	/*asks a user what type of employee they want to create
	(ÏSÓ for salaried, ÏHÓ for hourly worker) with other commands
	aborting the creation.*/
	void create_employee();

	/*prompts a user for a name, email address,and salary and instantiates SalariedWorker,
	saves it, and adds it to employees*/
	void create_salaried();

	/*prompts a user for a name, email address, and rate. Instantiates HourlyWorkerhat class,
	saves it, and adds it to employees */
	void create_hourly();

	/*have a print directory function that displays how many employees are in the
	company and then runs through the vector and calls print on all entries;*/
	void print_directory() const;

	/*do hours function: runs through the vector and, for the HourlyWorkers, prompts the user.
	After user input, it should call set hours and save() on the employee to save
	changes to employee;*/
	void do_hours();

	/*runs through the vector and calls the print pay on all elements;*/
	void print_payroll() const;
};

#endif //__COMPANY_H__


