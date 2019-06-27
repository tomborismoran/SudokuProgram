#include "SudokuClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <memory>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;


int Run(0);

template <class T> bool string_to_number(string Input, T& Number)
{
	const int NumberFlag(-1);
	bool Valid = 0;
	try
	{
		stringstream InputStream(Input);
		if ((InputStream >> Number).fail())
		{
			throw NumberFlag;
		}
		InputStream >> Number;
		Valid = 1;
	}
	catch (const int Error)
	{
		if (Error == NumberFlag)
		{
			cout << "Invalid conversion. ";
		}
	}
	return Valid;
}

//clears spaces and newlines from instream until there is something else
void clear_white_space(ifstream& Infile)
{
	while ((Infile.peek() == ' ') || (Infile.peek() == '\n'))
	{
		Infile.ignore(1);
	}
}

//clears spaces from instream until there is something else
void clear_just_spaces(ifstream& Infile)
{
	while (Infile.peek() == ' ')
	{
		Infile.ignore(1);
	}
}

void sudoku::print_out_test()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << i << j << ": " << TrueGrid[i][j] << ": ";
			for (int k = 0; k < 10; k++)
			{
				cout << Potential[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}

void sudoku::set_grid_sizes()
{
	TrueGrid.resize(9);
	Potential.resize(9);
	for (int i = 0; i < 9; i++)
	{
		TrueGrid[i].resize(9);
		Potential[i].resize(9);
		for (int j = 0; j < 9; j++)
		{
			Potential[i][j].resize(10);
		}
	}
}

void sudoku::initiate_potential()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Potential[i][j][0] = 0;
			for (int k = 1; k < 10; k++)
			{
				Potential[i][j][k] = 1;
			}
		}
	}
}

int sudoku::return_number_of_numbers()
{
	int Number = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (TrueGrid[i][j] != 0)
			{
				Number++;
			}
		}
	}
	return Number;
}

bool sudoku::check_box_validity(int yLimit, int xLimit)
{
	int Valid = 1;
	int BoxCheckList[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = yLimit; i < (yLimit + 3); i++)
	{
		for (int j = xLimit; j < (xLimit + 3); j++)
		{
			BoxCheckList[TrueGrid[i][j]]++;
		}
	}
	for (int k = 1; k < 10; k++)
	{
		if (BoxCheckList[k] > 1)
		{
			Valid = 0;
		}
	}

	return Valid;
}

bool sudoku::check_validity()
{
	bool Valid = 1;
	int CheckList[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//check rows
	for (int i = 0; i < 9; i++)
	{
		if (Valid)
		{
			for (int k = 0; k < 10; k++)
			{
				CheckList[k] = 0;
			}
			for (int j = 0; j < 9; j++)
			{
				CheckList[TrueGrid[i][j]]++;
			}
			for (int k = 1; k < 10; k++)
			{
				if (CheckList[k] > 1)
				{
					Valid = 0;
				}
			}
		}
	}
	if (Valid)
	{
		//check columns
		for (int j = 0; j < 9; j++)
		{
			if (Valid)
			{
				for (int k = 0; k < 10; k++)
				{
					CheckList[k] = 0;
				}
				for (int i = 0; i < 9; i++)
				{
					CheckList[TrueGrid[i][j]]++;
				}
				for (int k = 1; k < 10; k++)
				{
					if (CheckList[k] > 1)
					{
						Valid = 0;
					}
				}
			}
		}
	}
	//check boxes
	if (Valid)
	{
		Valid = check_box_validity(0, 0);
	}
	if (Valid)
	{
		Valid = check_box_validity(0, 3);
	}
	if (Valid)
	{
		Valid = check_box_validity(0, 6);
	}
	if (Valid)
	{
		Valid = check_box_validity(3, 0);
	}
	if (Valid)
	{
		Valid = check_box_validity(3, 3);
	}
	if (Valid)
	{
		Valid = check_box_validity(3, 6);
	}
	if (Valid)
	{
		Valid = check_box_validity(6, 0);
	}
	if (Valid)
	{
		Valid = check_box_validity(6, 3);
	}
	if (Valid)
	{
		Valid = check_box_validity(6, 6);
	}
	return Valid;
}

bool sudoku::check_box_potential(int y, int x, int Integer)
{
	bool Truth = 1;
	int yTest = y / 3;
	int yRun = 0;
	if (yTest == 1)
		yRun = 3;
	if (yTest == 2)
		yRun = 6;
	int xTest = x / 3;
	int xRun = 0;
	if (xTest == 1)
		xRun = 3;
	if (xTest == 2)
		xRun = 6;

	for (int i = yRun; i < (yRun + 3); i++)
	{
		for (int j = xRun; j < (xRun + 3); j++)
		{
			if ((i != y) && (j != x))
			{
				if (TrueGrid[i][j] == Integer)
				{
					Truth = 0;
				}
			}
		}
	}
	return Truth;
}

bool sudoku::check_line_potential(int y, int x, int Integer)
{
	bool Truth = 1;
	for (int i = 0; i < 9; i++)
	{
		if (i != y)
		{
			if ( TrueGrid[i][x] == Integer )
			{
				Truth = 0;
			}
		}
		if (i != x)
		{
			if (TrueGrid[y][i] == Integer)
			{
				Truth = 0;
			}
		}
	}

	return Truth;
}

void sudoku::reset_potential()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (TrueGrid[i][j] == 0)
			{
				Potential[i][j][0] = 0;
				for (int k = 1; k < 10; k++)
				{
					Potential[i][j][k] = check_line_potential(i,j,k) * check_box_potential(i,j,k);
				}
			}
			else
			{
				for (int k = 1; k < 10; k++)
				{
					if (k == TrueGrid[i][j])
					{
						Potential[i][j][k] = 1;
					}
					else
					{
						Potential[i][j][k] = 0;
					}
				}
			}
		}
	}
}

void sudoku::make_empty_truth()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			TrueGrid[i][j] = 0;
		}
	}
}

void sudoku::check_potential_for_truths()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int Test = 0;
			for (int k = 0; k < 10; k++)
			{
				if (Potential[i][j][k] == 1)
					Test++;
			}
			if (Test == 1)
			{
				for (int k = 0; k < 10; k++)
				{
					if (Potential[i][j][k] == 1)
						TrueGrid[i][j] = k;
				}
			}
		}
	}
}

void sudoku::box_needs_to_truths(int yLimit, int xLimit)
{
	int PotentialSum[10] = { 0,0,0,0,0,0,0,0,0,0 };
	for (int i = yLimit; i < (yLimit+3); i++)
	{
		for (int j = xLimit; j < (xLimit+3); j++)
		{
			for (int k = 0; k < 10; k++)
			{
				PotentialSum[k] = PotentialSum[k] + Potential[i][j][k];
			}
		}
	}
	for (int k = 0; k < 10; k++)
	{
		if (PotentialSum[k] == 1)
		{
			for (int i = yLimit; i < (yLimit + 3); i++)
			{
				for (int j = xLimit; j < (xLimit + 3); j++)
				{
					if ((Potential[i][j][k] == 1) && (TrueGrid[i][j] != k))
					{
						TrueGrid[i][j] = k;
					}
				}
			}
		}
	}
}

void sudoku::check_needs_for_truths()
{
	//check rows
	for (int i = 0; i < 9; i++)
	{
		int PotentialSum[10] = { 0,0,0,0,0,0,0,0,0,0 };
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				PotentialSum[k] = PotentialSum[k] + Potential[i][j][k];
			}
		}
		for (int k = 0; k < 10; k++)
		{
			if (PotentialSum[k] == 1)
			{
				for (int j = 0; j < 9; j++)
				{
					if ((Potential[i][j][k] == 1) && (TrueGrid[i][j] != k))
					{
						TrueGrid[i][j] = k;
					}
				}
			}
		}
	}
	//check columns
	for (int i = 0; i < 9; i++)
	{
		int PotentialSum[10] = { 0,0,0,0,0,0,0,0,0,0 };
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				PotentialSum[k] = PotentialSum[k] + Potential[j][i][k];
			}
		}
		for (int k = 0; k < 10; k++)
		{
			if (PotentialSum[k] == 1)
			{
				for (int j = 0; j < 9; j++)
				{
					if ((Potential[j][i][k] == 1) && (TrueGrid[j][i] != k))
					{
						TrueGrid[j][i] = k;
					}
				}
			}
		}
	}
	//check boxes
	box_needs_to_truths(0, 0);
	box_needs_to_truths(0, 3);
	box_needs_to_truths(0, 6);
	box_needs_to_truths(3, 0);
	box_needs_to_truths(3, 3);
	box_needs_to_truths(3, 6);
	box_needs_to_truths(6, 0);
	box_needs_to_truths(6, 3);
	box_needs_to_truths(6, 6);
}

bool sudoku::is_done()
{
	bool Truth = 1;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (TrueGrid[i][j] == 0)
				Truth = 0;
		}
	}
	return Truth;
}

sudoku::sudoku()
{
	set_grid_sizes();
	make_empty_truth();
	initiate_potential();
}

/*
sudoku::sudoku(sudoku &Original)
{
	TrueGrid = Original.TrueGrid;
	Potential = Original.Potential;
}

sudoku::sudoku(sudoku &&Original)
{
	TrueGrid = Original.TrueGrid;
	Potential = Original.Potential;
	Original.TrueGrid.clear();
	Original.Potential.clear();

}

sudoku & sudoku::operator=(sudoku &Original)
{
	if (&Original == this) return *this;
	TrueGrid.clear();
	Potential.clear();
	set_grid_sizes();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			TrueGrid[i][j] = Original.TrueGrid[i][j];
			for (int k = 1; k < 10; k++)
			{
				Potential[i][j][k] = Original.Potential[i][j][k];
			}
		}
	}
	return *this;
}

sudoku & sudoku::operator=(sudoku &&Original)
{
	TrueGrid.clear();
	Potential.clear();
	set_grid_sizes();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			TrueGrid[i][j] = Original.TrueGrid[i][j];
			for (int k = 1; k < 10; k++)
			{
				Potential[i][j][k] = Original.Potential[i][j][k];
			}
		}
	}
	Original.TrueGrid.clear();
	Original.Potential.clear();
	return *this;
}
*/

sudoku::~sudoku()
{
	TrueGrid.clear();
	Potential.clear();
}

void sudoku::set_number(int y, int x, int Number)
{
	TrueGrid[y][x] = Number;
	reset_potential();
}

int sudoku::return_number(int y, int x)
{
	int Value = TrueGrid[y][x];
	return Value;
}

ifstream& operator>>(ifstream &Infile, sudoku &Grid)
{
	int yGrid = 0;
	int xGrid = 0;
	while (Infile.peek() != EOF)
	{
		string Line;
		getline(Infile, Line, ',');
		bool Test = string_to_number<int>(Line,Grid.TrueGrid[yGrid][xGrid]);
		clear_just_spaces(Infile);
		xGrid++;
		if (Infile.peek() == '\n')
		{
			Infile.ignore(1);
			yGrid++;
			xGrid = 0;
		}
		clear_white_space(Infile);
	}
	Grid.reset_potential();
	return Infile;
}

ostream& operator<<(ostream &OutStream, sudoku &Grid)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			OutStream << Grid.TrueGrid[i][j];
			OutStream << ",";
		}
		OutStream << "\n";
	}
	return OutStream;
}

bool operator==(sudoku One, sudoku Two)
{
	bool Equal = 1;
	if (One.TrueGrid != Two.TrueGrid)
	{
		Equal = 0;
	}
	return Equal;
}

bool sudoku::unsolvable()
{
	bool Unsolvable = 0;
	bool ZeroPotential = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int Test = 0;
			for (int k = 1; k < 10; k++)
			{
				if (Potential[i][j][k] == 1)
				{
					Test++;
				}
			}
			if (Test == 0)
			{
				ZeroPotential = 1;
			}
		}
	}

	if ( (ZeroPotential) || (!check_validity()) )
	{
		Unsolvable = 1;
	}
	/*
	else
	{
		//for any TrueGrid point, try check_any_addition
		//this will trigger serious recursion in here, until I'm checking if a full grid is solvable (good!)
		int y = 9;
		int x = 9;
		for (int i = 0; i < 9; i++)
		{
			if (y == 9)
			{
				for (int j = 0; j < 9; j++)
				{
					if (x == 9)
					{
						if (TrueGrid[i][j] == 0)
						{
							y = i;
							x = j;
						}
					}
				}
			}
		}
		bool CheckAny = 1;
		if ((y < 9) && (x < 9))
		{
			if (TrueGrid[y][x] == 0)
			{
				CheckAny = check_any_addition(y, x);
			}
		}
		if (CheckAny == 0)
		{
			Unsolvable = 1;
		}
	}
	*/

	return Unsolvable;
}

void sudoku::try_to_solve()
{
	bool End = 0;
	vector<vector<vector<bool>>> LastPotential;
	int Times = 0;
	while (!End)
	{
		check_potential_for_truths();
		reset_potential();
		check_needs_for_truths();
		reset_potential();
		if (!unsolvable())
		{
			if (LastPotential == Potential)
			{
				End = 1;
			}
			else
			{
				LastPotential = Potential;
				End = is_done();
			}
		}
		else
		{
			//cout << "Not solvable" << endl;
			End = 1;
		}
		Times++;
	}
}

void sudoku::check_for_duplicates(vector<sudoku> &Solutions)
{
	vector<sudoku> SingleSolutions;
	bool First = 1;
	for (vector<sudoku>::iterator Iterator = Solutions.begin(); Iterator < Solutions.end(); Iterator++)
	{
		if (First)
		{
			SingleSolutions.push_back(*Iterator);
		}
		else
		{
			bool Original = 1;
			for (vector<sudoku>::iterator SingleIterator = SingleSolutions.begin(); SingleIterator < SingleSolutions.end(); SingleIterator++)
			{
				if (*Iterator == *SingleIterator)
				{
					Original = 0;
				}
			}
			if (Original)
			{
				SingleSolutions.push_back(*Iterator);
			}
		}
		First = 0;
	}
	Solutions.empty();
	Solutions = SingleSolutions;
}

vector<sudoku> sudoku::return_possible_solutions()
{
	cout << ".";
	int MinPotential = 9;
	int yMin = 0;
	int xMin = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int Test = 0;
			for (int k = 1; k < 10; k++)
			{
				Test = Test + Potential[i][j][k];
			}
			if ((Test < MinPotential) && (Test > 1))
			{
				MinPotential = Test;
				yMin = i;
				xMin = j;
			}
		}
	}
	vector<sudoku> Solutions;
	int NumberOfSolutions = 0;
	for (int k = 1; k < 10; k++)
	{
		if (Potential[yMin][xMin][k] == 1)
		{
			Solutions.push_back(*this);
			Solutions[NumberOfSolutions].set_number(yMin, xMin, k);
			NumberOfSolutions++;
		}
	}
	for (vector<sudoku>::iterator Iterator = Solutions.begin(); Iterator < Solutions.end(); Iterator++)
	{
		(*Iterator).try_to_solve();
	}
	size_t Tick = 0;
	while (Tick < Solutions.size())
	{
		if ((Solutions[Tick].unsolvable()))
		{
			//unsolvable -> delete this one
			Solutions.erase(Solutions.begin()+Tick);
		}
		else if (Solutions[Tick].is_done())
		{
			//solvable and done -> add to tick
			Tick++;
		}
		else
		{
			// solvable and not done -> run function again with this one, and add those results to solutions vector
			vector<sudoku> MetaSolutions = Solutions[Tick].return_possible_solutions();
			for (vector<sudoku>::iterator MetaIterator = MetaSolutions.begin(); MetaIterator < MetaSolutions.end(); MetaIterator++)
			{
				Solutions.push_back(*MetaIterator);
			}
			Solutions.erase(Solutions.begin() + Tick);
		}
	}
	check_for_duplicates(Solutions);
	return Solutions;
}

vector<sudoku> sudoku::solve()
{
	try_to_solve();
	vector<sudoku> Solutions;
	if (is_done())
	{
		Solutions.push_back(*this);
	}
	else
	{
		Solutions = return_possible_solutions();
	}
	return Solutions;
}

void read_and_solve_file_sudoku()
{
	sudoku Sudoku;

	ifstream InputFile("SudokuInput.txt");
	if (InputFile.is_open())
	{
		InputFile >> Sudoku;
	}
	else
	{
		cout << "Failed to open input file" << endl;
	}
	InputFile.close();
	
	ofstream OutputFile("SudokuOutput.txt");
	if (OutputFile.is_open())
	{
		vector<sudoku> Solutions = Sudoku.solve();

		cout << "Given " << Solutions.size() << " solutions" << endl;

		for (vector<sudoku>::iterator Iterator = Solutions.begin(); Iterator < Solutions.end(); Iterator++)
		{
			OutputFile << (*Iterator) << endl << endl;
		}
	}
	else
	{
		cout << "Failed to open output file" << endl;
	}
	OutputFile.close();
	
}

bool sudoku::empty()
{
	bool Test = 0;
	sudoku EmptySudoku;
	if (*this == EmptySudoku)
	{
		Test = 1;
	}
	return Test;
}

bool sudoku::check_any_addition(int y, int x)
{
	bool Valid = 0;
	sudoku TestSudoku(*this);
	for (int k = 1; k < 10; k++)
	{
		TestSudoku = *this;
		if ( Potential[y][x][k] == 1 )
		{
			TestSudoku.set_number(y, x, k);
			if (!(TestSudoku.unsolvable()))
			{
				Valid = 1;
			}
		}
	}

	return Valid;
}

sudoku create_a_sudoku(int MeanNumber)
{
	srand(time(NULL));
	double MeanNumberConvert = MeanNumber;
	double NumberProbability = MeanNumberConvert / 81;
	double Random;
	double RandomChance;
	bool NumberList[81];
	bool KeepNumbering = 1;
	while (KeepNumbering)
	{
		int CountNumbers = 0;
		for (int i = 0; i < 81; i++)
		{
			Random = (rand() % 100);
			RandomChance = (Random / 100);
			if (RandomChance < NumberProbability)
			{
				NumberList[i] = 1;
				CountNumbers++;
			}
			else
			{
				NumberList[i] = 0;
			}
		}
		if (CountNumbers == MeanNumber)
		{
			KeepNumbering = 0;
			cout << "Number list complete" << endl;
		}
	}

	sudoku Sudoku;

	bool Incomplete = 1;
	while (Incomplete)
	{
		srand(time(NULL));
		int yFail = 9;
		int xFail = 9;
		bool Possible = 1;
		for (int i = 0; i < 9; i++)
		{
			if (Possible)
			{
				for (int j = 0; j < 9; j++)
				{
					if (Possible)
					{
						if (Sudoku.check_any_addition(i, j))
						{
							//if (NumberList[(i * 9) + j])
							//{
								bool BadNumber = 1;
								while (BadNumber)
								{
									int RandomInteger = ((rand() % 9) + 1);
									Sudoku.set_number(i, j, RandomInteger);
									if (!Sudoku.unsolvable())
									{
										//a good number choice
										BadNumber = 0;
									}
								}
							//}
						}
						else
						{
							cout << "Failed at: " << i << "." << j << endl;
							yFail = i;
							xFail = j;
							Possible = 0;
						}
					}
				}
			}
		}

		if ((Sudoku.unsolvable()) || (yFail < 9))
		{
			Sudoku.make_empty_truth();
			Sudoku.reset_potential();
		}
		else
		{
			Incomplete = 0;
			cout << endl << "Sudoku completed" << endl;
		}
	}

	sudoku ReturnSudoku;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (NumberList[(i * 9) + j])
			{
				ReturnSudoku.set_number(i, j, Sudoku.return_number(i, j));
			}
		}
	}

	return ReturnSudoku;
}

void make_a_sudoku_and_print()
{
	sudoku Sudoku(create_a_sudoku(30));

	ofstream OutputFile("SudokuOutput.txt");
	if (OutputFile.is_open())
	{
		OutputFile << "Made:" << endl;
		OutputFile << Sudoku;
		OutputFile << "Unsolvable? " << Sudoku.unsolvable() << endl << endl;

		vector<sudoku> Solutions = Sudoku.solve();
		OutputFile << "Given " << Solutions.size() << " solutions:" << endl << endl;
		for (vector<sudoku>::iterator Iterator = Solutions.begin(); Iterator < Solutions.end(); Iterator++)
		{
			OutputFile << (*Iterator) << endl;
		}
	}
	else
	{
		cout << "Failed to open output file" << endl;
	}
	OutputFile.close();

}

void test_possibilities()
{
	int MinimumMean = 70;
	int Attempts = 0;
	sudoku BestSudokuStart;
	sudoku BestSudokuSolved;
	sudoku Test;
	sudoku TestStart;
	vector<sudoku> TestSolutions;
	while (Attempts < 100)
	{
		Test = create_a_sudoku((MinimumMean-1));
		TestStart = Test;
		if (Test.return_number_of_numbers() < MinimumMean)
		{
			cout << Attempts << ".";
			int StartingNumber = Test.return_number_of_numbers();
			Test.try_to_solve();
			if ( (Test.is_done()) && (Test.check_validity()) )
			{
				//solved easy
				MinimumMean = StartingNumber;
				Attempts = 0;
				cout << " Solved easy" << endl << MinimumMean << ": ";
				BestSudokuStart = TestStart;
				BestSudokuSolved = Test;
			}
			else
			{
				TestSolutions = Test.return_possible_solutions();
				if (TestSolutions.size() == 1)
				{
					//can be solved to one solution
					MinimumMean = StartingNumber;
					Attempts = 0;
					cout << " Solved hard" << endl << MinimumMean << ": ";
					BestSudokuStart = TestStart;
					BestSudokuSolved = TestSolutions[0];
				}
			}
			Attempts++;
		}
	}

	ofstream OutputFile("NewTestOutput.txt");
	if (OutputFile.is_open())
	{
		OutputFile << "This sudoku has " << MinimumMean << " numbers:" << endl;
		OutputFile << BestSudokuStart << endl;
		OutputFile << "Solution is:" << endl;
		OutputFile << BestSudokuSolved << endl;
	}
	else
	{
		cout << "Failed to open output file" << endl;
	}
	OutputFile.close();
}