/*
 * InventoryTracker.h
 *
 *  Created on: Aug 3, 2026
 *      Author: alecgerman
 */
#pragma once

#include <unordered_map>
#include <string>

const std::string COL_NAME_1 = "Name";
const std::string COL_NAME_2 = "Count";

class InventoryTracker {
private:
	std::unordered_map<std::string, int> inventory;
	
	void readItems();
	void saveItems();
	static void displayDivider();
	static void displayTableMarginal(std::string label1 = COL_NAME_1, std::string label2 = COL_NAME_2);
	static void displayTableRow(std::string label1, std::string label2);
	static void displayMenu();
public:
	void findItem();
	void displayInventoryCounts(bool asHistogram = false) const;
	static void operate();
};

