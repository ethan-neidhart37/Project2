// Knapsack class
// Version f08.1
#include <iostream>
#include <vector>
#include <fstream>
#include "d_except.h"

using namespace std;

class knapsack
{
public:
	knapsack(ifstream &fin);
	knapsack(const knapsack &);
	int getCost(int) const;
	int getValue(int) const;
	int getCost() const;
	int getValue() const;
	int getNumObjects() const;
	int getCostLimit() const;
	void printSolution();
	void select(int);
	void unSelect(int);
	bool isSelected(int) const;
	vector<bool> getSelected();

private:
	int numObjects;
	int costLimit;
	vector<int> value;
	vector<int> cost;
	vector<bool> selected;
	int totalValue;
	int totalCost;
};
