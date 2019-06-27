#ifndef MY_CLASS_H // Will only be true the once!
#define MY_CLASS_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <memory>
#include <algorithm>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

using namespace std;

class sudoku
{
protected:
	vector<vector<int>> TrueGrid;
	vector<vector<vector<bool>>> Potential;
public:
	sudoku();
	//sudoku(sudoku &Original);
	//sudoku(sudoku &&Original);
	//sudoku & operator=(sudoku &Original);
	//sudoku & operator=(sudoku &&Original);
	~sudoku();
	friend ifstream& operator>>(ifstream& instream, sudoku& Grid);
	friend ostream& operator<<(ostream &OutStream, sudoku &Grid);
	void set_grid_sizes();
	void make_empty_truth();
	void initiate_potential();
	bool check_line_potential(int y, int x, int Integer);
	bool check_box_potential(int y, int x, int Integer);
	void reset_potential();
	void set_number(int y, int x, int Number);
	void check_potential_for_truths();
	void check_needs_for_truths();
	void box_needs_to_truths(int yLimit, int xLimit);
	void try_to_solve();
	bool is_done();
	bool unsolvable();
	bool empty();
	bool check_any_addition(int y, int x);
	void print_out_test();
	vector<sudoku> return_possible_solutions();
	vector<sudoku> solve();
	bool check_validity();
	bool check_box_validity(int yLimit, int xLimit);
	void check_for_duplicates(vector<sudoku> &Solutions);
	friend bool operator==(sudoku One, sudoku Two);
	int return_number_of_numbers();
	int return_number(int y, int x);
};

void read_and_solve_file_sudoku();
sudoku create_a_sudoku(int MeanNumber);
void test_possibilities();
void make_a_sudoku_and_print();

#endif
