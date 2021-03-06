// File: p2a.cpp
// Authors: Kevin Do, Ethan Neidhart
// Project 2a: Solving knapsack using greedy algorithm

#include "p2a.h"

using namespace std;

float getPriority(knapsack &k, int i)
// Determine priority of an item by its "density" (value/cost)
{
	return (float)k.getValue(i) / (float)k.getCost(i);
}

int partition(knapsack &k, vector<int> &items, int left, int right, int pivot)
// Put every item with a higher priority than the pivot to the left
// Put every item with a lower priority than the pivot to the right
{
	for (int i = left; i < right; i++)
	{
		if (getPriority(k, items[i]) >= getPriority(k, pivot))
		{
			swap(items[i], items[left]);
			left++;
		}
	}
	return left - 1;
}

void quicksortKnapsack(knapsack &k, vector<int> &items, int left, int right)
// Sorting items from highest to lowest priority using partition
{
	//partition(k, 0, k.getNumObjects() - 1, items);
	if (left >= right)
		return;

	int middle = left + (right - left) / 2;
	swap(items[middle], items[left]);
	int midpoint = partition(k, items, left + 1, right, items[left]);
	swap(items[left], items[midpoint]);
	quicksortKnapsack(k, items, left, midpoint);
	quicksortKnapsack(k, items, midpoint + 1, right);
}

void greedyKnapsack(knapsack &k)
// Greedy algorithm to solve knapsack problem by grabbing highest priority items that will fit
{
	int size = k.getNumObjects();
	int limit = k.getCostLimit();
	int cost = 0;

	vector<int> items(size, 0);
	for (int i = 0; i < size; i++)
		items[i] = i;

	quicksortKnapsack(k, items, 0, items.size());
	// The first item in this list now contains the item number of the highest priority knapsack item

	for (int i = 0; i < size; i++)
	{
		int item = items[i];

		if (cost + k.getCost(item) <= limit)
		{
			k.select(item);
			cost += k.getCost(item);
		}

		if (cost == limit)
			return;
	}
}

void knapsackOutput(knapsack & k)
// Writes the results of the algorithm to an output file
{
	string fileName = "knapsack/output/knapsack" + to_string(k.getNumObjects()) + ".output";

	ofstream myfile;
	myfile.open(fileName);

	myfile << "Number of Objects: " << k.getNumObjects() << endl;
	myfile << "Total value: " << k.getValue() << endl;
	myfile << "Total cost: " << k.getCost() << endl;

	// Print out objects in the solution
	for (int i = 0; i < k.getNumObjects(); i++)
	{
		if (k.isSelected(i))
		{
			// Some unnecessary formatting to make output file look nicer
			if (i < 10)
			{
				myfile << i << "   " << k.getValue(i) << " " << k.getCost(i) << endl;
			}
			else
			{
				myfile << i << "  " << k.getValue(i) << " " << k.getCost(i) << endl;
			}
		}
	}
	myfile << endl;
	myfile.close();
}

void knapsackRun()
// Runs an algorithm to solve the knapsack problem
{
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	// fileName = "knapsack/input/knapsack16.input";

	cout << "Enter filename" << endl;
	cin >> fileName;
	string filePath = "knapsack/input/" + fileName + ".input";

	fin.open(filePath.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		knapsack k(fin);

		//exhaustiveKnapsack(k, 600);
		greedyKnapsack(k);

		// Write solution to output file
		knapsackOutput(k);

		cout << endl << "Best solution" << endl;
		k.printSolution();
	}

	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}

	fin.close();

	// loop input all files

	/*
	vector<string> s;
	s.push_back("knapsack/input/knapsack8.input");
	s.push_back("knapsack/input/knapsack12.input");
	s.push_back("knapsack/input/knapsack16.input");
	s.push_back("knapsack/input/knapsack20.input");
	s.push_back("knapsack/input/knapsack28.input");
	s.push_back("knapsack/input/knapsack32.input");
	s.push_back("knapsack/input/knapsack48.input");
	s.push_back("knapsack/input/knapsack64.input");
	s.push_back("knapsack/input/knapsack128.input");
	s.push_back("knapsack/input/knapsack256.input");
	s.push_back("knapsack/input/knapsack512.input");
	s.push_back("knapsack/input/knapsack1024.input");

	for (int i = 0; i < s.size(); i++)
	{
		//cout << "Enter filename" << endl;
		//cin >> fileName;
		fileName = s[i];
		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}

		try
		{
			cout << "Reading knapsack instance for " << s[i] << endl;

			knapsack k(fin);

			//exhaustiveKnapsack(k, 600);
			greedyKnapsack(k);

			// Write solution to output file
			knapsackOutput(k);

			cout << endl << "Best solution" << endl;
			k.printSolution();

			// Pause to view results
			system("PAUSE");
		}

		catch (indexRangeError &ex)
		{
			cout << ex.what() << endl; exit(1);
		}
		catch (rangeError &ex)
		{
			cout << ex.what() << endl; exit(1);
		}

		fin.close();
	}
	*/
}
