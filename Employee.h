/*
PIC 10B Homework 4, Employee.h
Author: Johnathan Harding
Date: 1/31/2022
*/

#ifndef __EMPLOYEE_H__ //header guards to prevent compile-time error
#define __EMPLOYEE_H__

#include <string> //including neccessary header files
#include <fstream>
#include <iostream>

/**
@class Employee This is an abstract class inherited by two other. It holds basic employee data:
				name, email, ID number. There are also support functions, though they do not do 
				much for this abstract class. This class also has a static member variable for 
				keeping track of what the ID# ought to be for an employee.
*/
class Employee {
	public:
		/**
		The default destructor, marked virtual, exists as required in base-class for polymorphism.
		*/
		virtual ~Employee() = default;
		//auxiliary constructors and assignment operators
			/**
			The move constructor allows one employee's data to be moved into a newly constructed one.
			@param x An r-value reference to an Employee object.
			*/
			Employee(Employee&& x) noexcept = default;//move constructor
			
			/**
			The copy cosntructor allows one Employee to be made as a copy of another.
			@param x An l-value reference to an Employee object.
			*/
			Employee(const Employee& x) = default;//copy constructor
			
			/**
			The move assignment operator allows one employee's data to be moved into another.
			@param x An r-value reference to an Employee object.
			*/
			Employee& operator=(Employee&& x) noexcept = default;//move operator

			/**
			The copy assignment operator allows one Employee to be the copy of another.
			@param x An l-value reference to an Employee object.
			*/
			Employee& operator=(const Employee&) = default;//copy operator

		/**
		Employee constructor that accepts a name and email address, and creates an Employee
		with those 
		@param n The string to be made the name of the employee.
		@param e The string to be the email of the employee.
		*/
		Employee(std::string n, std::string e);

		/**
		//Employee constructor that accepts an input file stream and reads a name, email, and id from the stream.
		@param fin The input filestream to be read from.
		*/
		Employee(std::ifstream& fin);

		//mutators:

		/**
		Mutator for an employee's name.
		@param n The string for the name to be set to...
		*/
		void setName(const std::string& n);
		
		/**
		Mutator for an employee's email address.
		@param e The string for the email to be set to...
		*/
		void setEmail(const std::string& e);
		
		/**
		Mutator for an employee's ID#.
		@param _id The int for the employee's ID to be set to...
		@return description of what is returned (if a return)
		*/
		void setID(int _id); //trying to overload to have one that accepts int

		//accessors for name, email, and id:

		/**
		Accessor for name of an employee.
		@return The name of an implicitly passed Employee.
		*/
		std::string getName() const;

		/**
		Accessor for an employee's email address.
		@return The email of an implicitly passed Employee.
		*/
		std::string getEmail() const;

		/**
		Accessor for emloyee ID#.
		@return The ID of an implicitly passed Employee.
		*/
		int getID() const;

		/**
		Accessor for the static member of the Employee class.
		@return The value held by the static member variable, next_id, for any implicitly passed
		Employee object.
		*/
		static int getNextID();

		/**
		Prints directory information to the console for a given employee.
		*/
		void print();

		/**
		Write data function (that can be overridden). Writes the name, email,
		and id of the Employee to a file, each entry separated by a tab.
		@param fout The ofstream object that the function is to write to a file through.
		*/
		void virtual write_data(std::ofstream& fout) const;

		/**
		Pure virtual print payfunctions that mandates functionality for printing payment 
		information data.
		*/
		void virtual print_pay() const = 0;

		/**
		Pure virtual save functions that mandates functionality for saving 
		employee data.
		*/
		void virtual save() const = 0;

	private:
		std::string name; //string that holds an employee's name
		std::string email; //string that holds an employee's email address
		int id; //int that holds and employee's ID number

		static int next_id; //holding the value of the next id to be created
	
	protected:
		/**
		Accessor for the private static int next_id through an implicitly passed Employee class object.
		@return Returns the current value of the static member variable. 
		*/
		static void upNextID(); //for after making new employee
};

#endif //__EMPLOYEE_H__
