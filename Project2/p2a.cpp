// File: p1a.cpp
// Authors: Kevin Do, Ethan Neidhart
// Project 1a: Solving knapsack using exhaustive search

#include "p2a.h"

using namespace std;

float getPriority(knapsack &k, int i)
{
	return (float)k.getValue(i) / (float)k.getCost(i);
}

void partition(knapsack &k, int p, int r, vector<int> &items)
// Helper function for quicksort
// Puts all items with greater priority than pivot to left of pivot
// Puts all items with less priority than pivot to right of pivot
{
	if (p <= r)
		return;

	int pivot = items[r];
	int temp;
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		if (getPriority(k, items[j]) >= getPriority(k, pivot))
		{
			i++;

			//Exchange values at locations i and j
			temp = items[i];
			items[i] = items[j];
			items[j] = temp;
		}
	}

	//Exchange pivot with value at i + 1 so it is in sorted position
	temp = items[i + 1];
	items[i + 1] = items[r];
	items[r] = temp;

	//Partition the list before the pivot
	partition(k, p, i, items);

	//Partition the list after the pivot
	partition(k, i + 2, r, items);
}

void quicksortKnapsack(knapsack &k, vector<int> &items)
{
	vector<int> items(k.getNumObjects(), 0);

	for (int i = 0; i < k.getNumObjects(); i++)
		items[i] = i;

	partition(k, 0, k.getNumObjects() - 1, items);
}

void greedyKnapsack(knapsack &k)
{
	int size = k.getNumObjects();
	int limit = k.getCostLimit();
	int cost = 0;

	vector <int> items(size, 0);
	for (int i = 0; i < size; i++)
		items[i] = i;

	quicksortKnapsack(k, items);
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

void exhaustiveKnapsack(knapsack &k, int t)
{
	clock_t startTime;
	clock_t currentTime;
	startTime = clock();
	float diff; //time difference
	float duration = 0;
	bool foundNode = false; //found a position
	bool endOfKnapsackSets = false;
	vector <bool> selectedObjs(k.getNumObjects(), false);
	int score = 0;
	int i;

	while (t > duration && !endOfKnapsackSets)
	{
		// Display
		//cout << "knapsack" << k.getNumObjects() << ".input - " << "duration: " << duration << "s" << endl;

		if (score < k.getValue() && k.getCost() <= k.getCostLimit())
		{
			score = k.getValue();
			selectedObjs = k.getSelected();
		}

		// Reset
		foundNode = false;
		i = 0;

		while (!foundNode)
		{
			if (k.isSelected(i))
			{
				k.unSelect(i);
				if (i == k.getNumObjects() - 1) { endOfKnapsackSets = true; }
				else { i++; }
			}
			else
			{
				k.select(i);
				foundNode = true;
			}
		}
		currentTime = clock();
		diff = (float)currentTime - (float)startTime;
		duration = diff / CLOCKS_PER_SEC;
	}

	for (int i = 0; i < selectedObjs.size(); i++)
	{
		if (selectedObjs[i]) { k.select(i); }
		else { k.unSelect(i); }
	}
}

void knapsackOutput(knapsack & k)
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
{
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	// fileName = "knapsack/input/knapsack16.input";

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
}
