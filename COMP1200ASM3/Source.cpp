#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//By: Gianluca Venditti 
//For: Travis.J Smith 
//Date: Friday, April 30th, 2021
//Purpose: Displaying bird sightings in the area, that reads from a file and outputs a report

const int SIZE = 20;

void loadArrays(ifstream&,string[], int[][3], int&);
void computeSum(const int[][3], int[], int);
void mostSightings(const int[],  int&, int);
void findBird(const int[][3], int&, int&, int&);
void printReport(ofstream&, const string[], const int [][3], const int[], int, int);
int indexOfHighestBird(const int[], int);
int addSumArray(const int[], int);

int main()
{
	int sightings[SIZE][3];  
	string bird[SIZE];
	int totalAreaSightings[SIZE] = { 0 };
	int noBirds;
	int highestRow, highestCol, mostSeen;

	ifstream fin("birds.dat");
	if (!fin.is_open())
	{
		cout << "error opening birds.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("birds.rpt");
	if (!fout.is_open())
	{
		cout << "error opening birds.rpt file - contact systems";
		system("pause");
		exit(-2);
	}

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, bird, sightings, noBirds);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute total sightings by area\n\n";
	computeSum(sightings, totalAreaSightings, noBirds);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind most seen bird and highest number of sightings:\n\n";
	findBird(sightings, highestRow, highestCol, noBirds);
	cout << "\n\n" << bird[highestRow] << " had the most number of sightings = "
		<< sightings[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind the most seen bird:\n\n";
	mostSightings(totalAreaSightings, mostSeen, noBirds);
	cout << "\n\n Most seen bird is " << bird[mostSeen] << endl;

	cout << "\n\n=======================================================\n\n";

	printReport(fout, bird, sightings, totalAreaSightings, mostSeen, noBirds);
	cout << "\n\n=======================================================\n\n";

	fout.close();
	fin.close();

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing birds.dat file\n\n";
	system("type birds.dat");
	cout << "\n\n Printing birds.rpt file\n\n";
	system("type birds.rpt");
	system("pause");
}

void loadArrays(ifstream& fin,string bird[], int sightings[][3], int& noBird)
{
	for (noBird = 0; noBird < SIZE; noBird++)
	{
		getline(fin, bird[noBird]);

		if (fin.eof())
			break;

		for (int sightingsCounter = 0; sightingsCounter < 3; sightingsCounter++)
		{
			fin >> sightings[noBird][sightingsCounter];
		}
		fin.ignore(80, '\n');
	}
	noBird--; 
}

void computeSum (const int sightings[][3], int totalSight[], int noBird)
{
	for (int birdCounter = 0; birdCounter < SIZE; birdCounter++)
	{
		for (int sightingsCounter = 0; sightingsCounter < 3; sightingsCounter++)
		{
			totalSight[birdCounter] += sightings[birdCounter][sightingsCounter];
		}
	}
}

void mostSightings(const int totalAreaSightings[], int& mostSeen, int noBird)

{
	mostSeen = 0; // best index 

	if (noBird > 0) 
	{
		for (int row = 0; row < noBird; row++)
		{
			
			if (totalAreaSightings[row] > totalAreaSightings[mostSeen])
			{
				mostSeen = row;
			}
		}
	}
	else
	{
		cout << "Unable to search array! Array empty!";
	}
}

void findBird(const int totalAreaSightings[][3], int& highestRow, int& highestCol, int& noBird)

{
	highestRow = 0; 
	highestCol = 0; 

	if (noBird > 0)
	{
		for (int row = 0; row < noBird; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				if (totalAreaSightings[row][col] > totalAreaSightings[highestRow][highestCol])
				{
					highestRow = row;
					highestCol = col;
				}
			}
		}
	}
	else
	{
		cout << "Unable to search array! Array empty!";
	}
}

void printReport(ofstream& fout, const string bird[], const int sightings[][3], const int totalAreaSightings[], int mostSeen, int noBird)
{
	int rowOfHightest = indexOfHighestBird(totalAreaSightings, noBird);
	int sum = addSumArray(totalAreaSightings, noBird);

	fout << setw(10) << "Type of Bird" << setw(15) << right << "Area #1" << setw(15) 
		 << right <<"Area #2" << setw(15) << right << "Area #3" 
		 << setw(10) << right << "Total" << endl << endl;         

	for (int row = 0; row < noBird; row++)
	{
		fout << setw(20) << left << bird[row];
		
		for (int col = 0; col < 3; col++)
		{
		fout << setw(15) << left << sightings[row][col];
		
		}
		fout << setw(10) << left << totalAreaSightings[row];
		if (row == rowOfHightest)
		{
			fout << "** Most Sightings **";
		}
		fout << endl;
	}
	fout << endl;
	fout << "Total Number of Sightings = " << sum << endl; 
	fout << endl << endl; 
}

int indexOfHighestBird(const int sumArray[], int noBird)
{
	int indexOfHighest = 0; 

	for (int counter = 1; counter < noBird; counter++)
	{
		if (sumArray[indexOfHighest] < sumArray[counter])
		{
			indexOfHighest = counter;
		}
	}
	return indexOfHighest;
}

int addSumArray(const int sumArray[], int noBird)
{
	int sum = 0;

	for (int counter = 0; counter < noBird; counter++)
	{
		sum += sumArray[counter];
	}
	return sum;
}
/*

Load arrays



=======================================================



Compute total sightings by area



=======================================================



Find most seen bird and highest number of sightings:



Baltimore Oriole had the most number of sightings = 53


=======================================================



Find the most seen bird:



 Most seen bird is Blue Heron


=======================================================



=======================================================

program ended successfully


 Printing birds.dat file

Blue Heron
25      50       4
Cardinal
25      0       25
King Fisher
3       44       0
Pink Flamingo
0       40       2
Baltimore Oriole
53      8        7
Blue Jay
0		5		 3
Penguin
0		0		 1
HummingBird
20		3		 0




 Printing birds.rpt file

Type of Bird        Area #1        Area #2        Area #3     Total

Blue Heron          25             50             4              79        ** Most Sightings **
Cardinal            25             0              25             50
King Fisher         3              44             0              47
Pink Flamingo       0              40             2              42
Baltimore Oriole    53             8              7              68
Blue Jay            0              5              3              8
Penguin             0              0              1              1
HummingBird         20             3              0              23

Total Number of Sightings = 318


Press any key to continue . . .

*/