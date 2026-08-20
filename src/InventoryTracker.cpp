/*
 * InventoryTracker.cpp
 *
 *  Created on: Aug 3, 2026
 *      Author: alecgerman
 */

#include "InventoryTracker.h"
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

constexpr const char* INPUT_FILE = "CS210_Project_Three_Input_File.txt";
constexpr const char* OUTPUT_FILE = "frequency.dat";
constexpr int COL_WIDTH = 30;

// Functions that help with formatting the output.
void InventoryTracker::displayDivider()
{
	std::cout << std::string(COL_WIDTH * 2, '-') << '\n';
}


void InventoryTracker::displayTableMarginal(std::string label1, std::string label2)
{
	displayDivider();
	displayTableRow(label1, label2);
	displayDivider();
}

void InventoryTracker::displayTableRow(std::string label1, std::string label2)
{
	std::cout << "| "
	          << std::left
			  << std::setw(COL_WIDTH) << label1 << "| "
	          << std::setw(COL_WIDTH - 5) << label2
			  << "|\n";
}
// End formatting functions

// Displays the options menu
void InventoryTracker::displayMenu()
{
	std::cout << "1. Search Item\n" 
	          << "2. Display Inventory\n"
			  << "3. Display Inventory Histogram\n"
			  << "4. Exit Program\n";
}

void InventoryTracker::readItems()
{
	// Initialize an input stream with the opened INPUT_FILE.
	std::ifstream inputFS(INPUT_FILE);

	// Verify that the file opened successfully.
	if (!inputFS.is_open())
	{
		throw std::runtime_error("Failed to open " + std::string(INPUT_FILE));
	}
	
	// Stores the current item read from the input file.
	std::string item;
		
	// Read each item from the input file until EOF
	while (inputFS >> item)
	{
		// If the item does not already exist in the map, it is automatically
		// created with a value of 0. The count is then incremented by one.
		inventory[item]++;		
	}
	
	// Check for an unexpected read error.
	if (inputFS.bad())
	{
		throw std::runtime_error(
			"An error occurred while reading " + std::string(INPUT_FILE));
	}
}

void InventoryTracker::saveItems()
{
	// Initialize an output file with the opened OUTPUT_FILE.
	std::ofstream outputFS(OUTPUT_FILE);
	
	// Verify that the file opened successfully.
	if (!outputFS.is_open())
	{
		throw std::runtime_error("Failed to open " + std::string(OUTPUT_FILE));
	}
	
	// Write the headers to the file.
	outputFS << "Name,Count\n";
	
	// Write each item and its count to the file.
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		outputFS << it->first << "," << it->second << '\n';
	}
	
	// Check for an unexpected write error.
	if (outputFS.bad())
	{
		throw std::runtime_error(
			"An error occurred while writing to " + std::string(OUTPUT_FILE));
	}
}

void InventoryTracker::findItem()
{
	// Stores item to search.
	std::string itemName;
	std::cout << "Input search term: ";
	std::cin >> itemName;
	
	// Checks if the itemName key exists in the inventory map.
	if (inventory.find(itemName) != inventory.end())
	{
		displayTableMarginal();
		displayTableRow(itemName, std::to_string(inventory[itemName]));
		displayDivider();
	}
	else
	{
		std::cout << itemName << " doesn't exist in our inventory database.\n";
	}
}

void InventoryTracker::displayInventoryCounts(bool asHistogram) const
{
	int sum = 0;
	
	// Display table header
	displayTableMarginal();
	
	// Loop over an inventory iterator, display the item name (it->first) and count (it->second).
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		std::string countStr = asHistogram 
			? std::string(it->second, '+') 
			: std::to_string(it->second);
			
		displayTableRow(it->first, countStr);

		sum += it->second;
	}
		
	// Display table footer
	displayTableMarginal("Total", std::to_string(sum));
}

void InventoryTracker::operate()
{
	try 
	{
		InventoryTracker inventoryTracker;
		inventoryTracker.readItems();
		inventoryTracker.saveItems();
		
		int option;
	    bool isRunning = true;
		
		
		while (isRunning)
		{
			std::cout << "Welcome to the CornerGrocer Inventory Tracking System\n\n";
			displayMenu();
			
			std::cout << "\nChoose an option: ";
			std::cin >> option;
			std::cout << "\n";
			
			switch (option)
			{
			case 1:
				inventoryTracker.findItem();
				break;
			case 2:	
				inventoryTracker.displayInventoryCounts(false);
				break;
			case 3:
				inventoryTracker.displayInventoryCounts(true);
				break;
			case 4:
				isRunning = false;
				break;
			default:
				std::cout << "Invalid option\n";
			}
			
			std::cout << '\n';
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
}