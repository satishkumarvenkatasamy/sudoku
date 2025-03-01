/******************************************************************************
*  File Name        : sudoku.c
*  Author           : Satishkumar Venkatasamy
*  History
* 
*  DD-MON-YYYY      Change
* --------------   ------------------------------------------------------------
*  02-AUG-2017      Creation
*                                   
******************************************************************************/

#include "stdio.h"

//Possible values for each cell will be stored in this 3D matrix
//In 3rd dimension cell, 10th column will be used to store how
//many possible values are there. How many possible values are
//there will be used to solve sudoku at 4th level
int possible_values[9][9][10] = { 0 };

int missing_numbers_in_rows[9][9] = {
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                         };
int missing_numbers_in_cols[9][9] = {
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                         };
int missing_numbers_in_3x3matrix[9][9] = {
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                            { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                         };

int easy_sudoku_problem[9][9] = {
                                    { 5, 0, 1, 0, 0, 0, 0, 2, 0 },
                                    { 8, 9, 3, 7, 0, 5, 1, 0, 0 },
                                    { 6, 0, 0, 0, 1, 0, 0, 7, 0 },
                                    { 9, 0, 0, 2, 3, 1, 0, 0, 0 },
                                    { 0, 2, 0, 0, 4, 0, 0, 3, 0 },
                                    { 0, 0, 0, 6, 8, 9, 0, 0, 2 },
                                    { 0, 8, 0, 0, 7, 0, 0, 0, 1 },
                                    { 0, 0, 5, 8, 0, 2, 7, 6, 4 },
                                    { 0, 6, 0, 0, 0, 0, 3, 0, 8 }
                                  };

int evil_sudoku_problem[9][9] = {
                                    { 0, 8, 4, 3, 7, 0, 0, 0, 0 },
                                    { 0, 5, 0, 0, 0, 2, 0, 6, 0 },
                                    { 0, 0, 0, 0, 0, 4, 0, 3, 9 },
                                    { 0, 6, 0, 0, 0, 0, 0, 0, 0 },
                                    { 8, 0, 0, 5, 0, 9, 0, 0, 7 },
                                    { 0, 0, 0, 0, 0, 0, 0, 4, 0 },
                                    { 5, 7, 0, 9, 0, 0, 0, 0, 0 },
                                    { 0, 9, 0, 4, 0, 0, 0, 7, 0 },
                                    { 0, 0, 0, 0, 1, 5, 9, 2, 0 }
                                };

int medium2_sudoku_problem[9][9] = {
                                     { 7, 1, 6, 2, 9, 4, 0, 0, 0 },
                                     { 0, 0, 0, 6, 0, 0, 0, 0, 1 },
                                     { 2, 0, 0, 0, 0, 0, 9, 0, 0 },
                                     { 0, 0, 0, 0, 0, 6, 8, 4, 0 },
                                     { 8, 9, 7, 0, 0, 0, 1, 5, 6 },
                                     { 0, 6, 1, 5, 0, 0, 0, 0, 0 },
                                     { 0, 0, 5, 0, 0, 0, 0, 0, 2 },
                                     { 1, 0, 0, 0, 0, 8, 0, 0, 0 },
                                     { 0, 0, 0, 3, 2, 5, 7, 1, 4 }
                                 };

//3,901,750,535
int hard_sudoku_problem[9][9] = {
                                     { 0, 0, 6, 1, 0, 0, 0, 0, 9 },
                                     { 0, 9, 0, 0, 0, 6, 0, 0, 0 },
                                     { 7, 0, 0, 0, 5, 2, 0, 0, 0 },
                                     { 6, 4, 5, 2, 3, 0, 0, 0, 0 },
                                     { 0, 1, 0, 0, 0, 0, 0, 2, 0 },
                                     { 0, 0, 0, 0, 1, 4, 6, 5, 3 },
                                     { 0, 0, 0, 3, 8, 0, 0, 0, 4 },
                                     { 0, 0, 0, 5, 0, 0, 0, 3, 0 },
                                     { 8, 0, 0, 0, 0, 9, 1, 0, 0 }
                                 };

int hard_2_sudoku_problem[9][9] = {
                                     { 5, 0, 0, 9, 0, 0, 0, 7, 3 },
                                     { 0, 6, 0, 0, 0, 0, 9, 0, 4 },
                                     { 8, 0, 0, 0, 0, 0, 0, 0, 5 },
                                     { 7, 5, 1, 0, 0, 0, 0, 0, 8 },
                                     { 6, 0, 0, 2, 1, 8, 5, 0, 7 },
                                     { 0, 8, 0, 0, 0, 0, 0, 0, 1 },
                                     { 9, 0, 0, 0, 0, 0, 3, 0, 0 },
                                     { 0, 0, 0, 0, 4, 0, 0, 0, 0 },
                                     { 0, 0, 0, 5, 0, 1, 0, 0, 0 },
                                  };

int hard_3_sudoku_problem[9][9] = {
                                     { 0, 0, 6, 0, 0, 0, 0, 0, 0 },
                                     { 4, 0, 0, 0, 0, 2, 0, 7, 0 },
                                     { 2, 9, 3, 7, 0, 0, 0, 5, 0 },
                                     { 0, 0, 0, 9, 1, 8, 7, 0, 5 },
                                     { 0, 0, 0, 0, 5, 0, 0, 0, 0 },
                                     { 1, 0, 7, 2, 3, 4, 0, 0, 0 },
                                     { 0, 4, 0, 0, 0, 3, 5, 2, 7 },
                                     { 0, 3, 0, 8, 0, 0, 0, 0, 6 },
                                     { 0, 0, 0, 0, 0, 0, 8, 0, 0 },
                                  };

int medium_sudoku_problem[9][9] = {
                                    { 0, 6, 0, 5, 0, 8, 2, 0, 0 },
                                    { 0, 3, 2, 0, 0, 0, 0, 9, 0 },
                                    { 0, 0, 0, 0, 2, 0, 6, 4, 0 },
                                    { 0, 0, 0, 0, 0, 9, 4, 8, 0 },
                                    { 0, 0, 1, 3, 0, 4, 7, 0, 0 },
                                    { 0, 8, 3, 7, 0, 0, 0, 0, 0 },
                                    { 0, 1, 9, 0, 6, 0, 0, 0, 0 },
                                    { 0, 4, 0, 0, 0, 0, 1, 7, 0 },
                                    { 0, 0, 6, 4, 0, 1, 0, 2, 0 }
                                };

int medium3_sudoku_problem[9][9] = {
                                    { 4, 0, 3, 0, 0, 0, 6, 0, 0 },
                                    { 0, 0, 0, 0, 0, 3, 5, 0, 0 },
                                    { 5, 0, 2, 0, 0, 6, 1, 9, 0 },
                                    { 2, 9, 0, 0, 8, 0, 0, 0, 0 },
                                    { 6, 0, 0, 0, 7, 0, 0, 0, 4 },
                                    { 0, 0, 0, 0, 1, 0, 0, 6, 5 },
                                    { 0, 4, 7, 5, 0, 0, 2, 0, 1 },
                                    { 0, 0, 6, 2, 0, 0, 0, 0, 0 },
                                    { 0, 0, 5, 0, 0, 0, 7, 0, 0 }
                                };


int get_missing_numbers( int sudoku_puzzle[9][9] );
int solve_sudoku_1st_level( int sudoku_puzzle[9][9] );
int solve_row_col_1st_level( int row, int col, int iteration_count );

int solve_sudoku_2nd_level( int sudoku_puzzle[9][9] );
int solve_row_col_2nd_level( int row, int col );

int solve_sudoku_3rd_level( int sudoku_puzzle[9][9] );
int solve_row_col_3rd_level( int sudoku_puzzle[9][9], int row, int col );

int solve_sudoku_4th_level( int sudoku_puzzle[9][9] );
int solve_row_col_4th_level(int row, int col, int possible_2_vals[2]);

void print_missing_numbers();
void print_sudoku( int sudoku_puzzle[9][9] );

void clear_missing_possible_arrays( int row, int col, int value_fixed );

int main( int argc, char* argv[] )
{
  char returnchar;
  int fixed = 0;
  int total_fixed = 0;
  int num_iterations = 0;
  int **sample_sudoku_problem = NULL;
	printf("\nHello world\n");

  sample_sudoku_problem = (int **)hard_3_sudoku_problem;
  get_missing_numbers( (int (*)[9])sample_sudoku_problem );
  //print_missing_numbers();

  do
  {
    total_fixed = 0;
    do
    {
      fixed = solve_sudoku_1st_level((int (*)[9])sample_sudoku_problem);
      num_iterations++;
      printf("\nIteration #%d completed.", num_iterations);
      total_fixed += fixed;
    }
    while( fixed > 0 );

    //print_missing_numbers();
    print_sudoku( (int (*)[9])sample_sudoku_problem );
    fixed = 0;
    do
    {
      fixed = solve_sudoku_2nd_level((int (*)[9])sample_sudoku_problem);
      num_iterations++;
      printf("\nIteration #%d completed.", num_iterations);
      total_fixed += fixed;
    }
    while( fixed > 0 );

    print_sudoku( (int (*)[9])sample_sudoku_problem );
    fixed = 0;
    do
    {
      fixed = solve_sudoku_3rd_level((int (*)[9])sample_sudoku_problem);
      num_iterations++;
      printf("\nIteration #%d completed.", num_iterations);
      total_fixed += fixed;
    }
    while( fixed > 0 );
  }
  while( total_fixed > 0 );

  /*
  scanf("%c", &returnchar);
  fixed = 0;
  do
  {
    fixed = solve_sudoku_1st_level((int (*)[9])sample_sudoku_problem);
    num_iterations++;
    printf("\nIteration #%d completed.", num_iterations);
    total_fixed += fixed;
  }
  while( fixed > 0 );
  print_sudoku((int (*)[9])sample_sudoku_problem);

  scanf("%c", &returnchar);

  fixed = 0;
  do
  {
    fixed = solve_sudoku_2nd_level((int (*)[9])sample_sudoku_problem);
    num_iterations++;
    printf("\nIteration #%d completed.", num_iterations);
    total_fixed += fixed;
  }
  while( fixed > 0 );
  print_sudoku( (int (*)[9])sample_sudoku_problem );

  scanf("%c", &returnchar);

  fixed = 0;
  do
  {
    fixed = solve_sudoku_3rd_level((int (*)[9])sample_sudoku_problem);
    num_iterations++;
    printf("\nIteration #%d completed.", num_iterations);
    total_fixed += fixed;
  }
  while( fixed > 0 );
  */
  print_sudoku( (int (*)[9])sample_sudoku_problem );

  scanf("%c", &returnchar);
	return 0;
}



int get_missing_numbers( int sudoku_puzzle[9][9] )
{
  int row, col = 0;
  int val;

  for( row = 0; row < 9; row++ )
  {
    //printf("\n");
    for( col = 0; col < 9; col++ )
    {
      //printf("%d ", val);
      if( sudoku_puzzle[row][col] != 0 )
      {
        //if a number is there, just mark that 
        int availablenum = sudoku_puzzle[row][col];
        missing_numbers_in_rows[row][availablenum-1] = 0;
        missing_numbers_in_cols[col][availablenum-1] = 0;

        val = ((row/3)*3)+(col/3);
        missing_numbers_in_3x3matrix[val][availablenum-1] = 0;
      }
    }
  } //outer for loop
  return 0;
}

int solve_sudoku_1st_level( int sudoku_puzzle[9][9] )
{
  static int iteration_count = 0;
  int row, col = 0;
  int num_fixed = 0;

  for( row = 0; row < 9; row++ )
  {
    for( col = 0; col < 9; col++ )
    {
      if( sudoku_puzzle[row][col] == 0 )
      {
        int val = solve_row_col_1st_level(row, col, iteration_count);
        if( val )
        {
          char dummyChar;
          sudoku_puzzle[row][col] = val;
          clear_missing_possible_arrays( row, col, val );
          num_fixed++;
          printf("\nRow %d col %d solved : %d", row, col, val );
          print_sudoku( sudoku_puzzle );
          scanf("%c", &dummyChar);
        }
      }
    } //inner for loop
  } //outer for loop

  iteration_count++;
  return num_fixed;
}

int solve_row_col_1st_level( int row, int col, int iteration_count )
{
  int counter = 0;
  int matrix3x3_id = (row/3)*3+(col/3);
  int num_match_found = 0;
  int value = 0;

  for( counter = 0; counter < 9; counter++ )
  {  
    if( missing_numbers_in_rows[row][counter] +
        missing_numbers_in_cols[col][counter] +
        missing_numbers_in_3x3matrix[matrix3x3_id][counter] == 3*(counter+1) )
    {
      if( iteration_count == 0 )
      {
        possible_values[row][col][counter] = counter+1;
      }
      //possible_values[row][col][9] += 1;
      num_match_found++;
      value = counter+1;
    } //if block
  } //for loop


  if( num_match_found == 1 )
  {
    missing_numbers_in_rows[row][value-1] = 0;
    missing_numbers_in_cols[col][value-1] = 0;
    possible_values[row][col][value-1] = 0;
    return value; 
  }

  return 0;
}

int solve_sudoku_2nd_level( int sudoku_puzzle[9][9] )
{
  int row, col = 0;
  int num_fixed = 0;

  for( row = 0; row < 9; row++ )
  {
    for( col = 0; col < 9; col++ )
    {
      if( sudoku_puzzle[row][col] == 0 )
      {
        int val = solve_row_col_2nd_level( row, col );
        if( val )
        {
          sudoku_puzzle[row][col] = val;
          clear_missing_possible_arrays( row, col, val );
          num_fixed++;
        } // if block
      } // if block
    } //inner for loop
  }//outer for loop

  return num_fixed;
}

int solve_row_col_2nd_level( int row, int col )
{
  int counter = 0;
  int num_row_zeros = 0;
  int num_col_zeros = 0;
  int num_3x3matrix_zeros = 0;
  int sum_row = 0;
  int sum_col = 0;
  int sum_3x3matrix = 0;
  int matrix3x3_id = (row/3)*3+(col/3);

  for( counter = 0; counter < 9; counter++ )
  {  
    missing_numbers_in_rows[row][counter] == 0 ? num_row_zeros++ : 0;
    sum_row += missing_numbers_in_rows[row][counter];

    missing_numbers_in_cols[col][counter] == 0 ? num_col_zeros++ : 0;
    sum_col += missing_numbers_in_cols[col][counter];

    missing_numbers_in_3x3matrix[matrix3x3_id][counter] == 0 ? num_3x3matrix_zeros++ : 0;
    sum_3x3matrix += missing_numbers_in_3x3matrix[matrix3x3_id][counter];
  }

  if( num_row_zeros == 8 && sum_row <= 9 )
  {
    missing_numbers_in_rows[row][sum_row-1] = 0;
    return sum_row;
  }
  
  if( num_col_zeros == 8 && sum_col <= 9 )
  {
    missing_numbers_in_cols[col][sum_col-1] = 0;
    return sum_col;
  }

  if( num_3x3matrix_zeros == 8 && sum_3x3matrix <= 9 )
  {
    missing_numbers_in_3x3matrix[matrix3x3_id][sum_3x3matrix-1] = 0;
    return sum_3x3matrix;
  }

  return 0;
}



int solve_sudoku_3rd_level( int sudoku_puzzle[9][9] )
{
  int row, col = 0;
  int num_fixed = 0;

  for( row = 0; row < 9; row++ )
  {
    for( col = 0; col < 9; col++ )
    {
      if( sudoku_puzzle[row][col] == 0 )
        num_fixed += solve_row_col_3rd_level( sudoku_puzzle, row, col );
    } //for( col ... block
  } //for( row ... block

  return num_fixed;
}

int solve_row_col_3rd_level( int sudoku_puzzle[9][9], int row, int col )
{
  //variabe to traverse given row/column/3x3matrix
  int traverse_rc3m = 0;
  int traverse_possible_val = 0;
  int value_fixed = 0;
  int num_fixed = 0;
  int numr[9] = { 0 };
  int numc[9] = { 0 };
  int num3x3m[9] = { 0 };
  int matrix3x3_id = (row/3)*3+(col/3);

  for( traverse_rc3m = 0; traverse_rc3m < 9; traverse_rc3m++ )
  {
    numr[traverse_rc3m]= numc[traverse_rc3m] = num3x3m[traverse_rc3m] = 0;
  }

  //traverse complete row 0 to 9 of given "row" to find if a num is unique
  //Also traverse complete column 0 to 9 of given "col" to find a num is unique
  //Also traverse complete 3x3 matrix corresponding to given row, col
  for( traverse_rc3m = 0; traverse_rc3m < 9; traverse_rc3m++ )
  {
    for( traverse_possible_val = 0; traverse_possible_val < 9; traverse_possible_val++)
    {
      int row_3x3m = ((row/3)*3)+traverse_rc3m/3;
      int col_3x3m = ((col/3)*3)+traverse_rc3m%3;

      //if( !traverse_possible_val )
      //  printf("\nFor row %d, col %d, traversing tow  wise: row %d, col %d, ", row, col, row, traverse_rc3m);
      //if( row == 1 && col == 4 )
      //  printf("\nAdding possible value %d for row %d, col %d", possible_values[row][traverse_rc3m][traverse_possible_val], row, traverse_rc3m);
      numr[traverse_possible_val] += possible_values[row][traverse_rc3m][traverse_possible_val];

      //if( !traverse_possible_val )
      //  printf("\nFor row %d, col %d, traversing column wise: row %d, col %d, ", row, col, traverse_rc3m, col);
      numc[traverse_possible_val] += possible_values[traverse_rc3m][col][traverse_possible_val];

      //if( !traverse_possible_val )
      //  printf("\nFor row %d, col %d, scanning 3x3 matrix row %d, col: %d", row, col, row_3x3m, col_3x3m );
      num3x3m[traverse_possible_val] += possible_values[row_3x3m][col_3x3m][traverse_possible_val];
    } // for( traverse_possible_val ) loop
  } // for( traverse_rc3m ) loop

  for( traverse_possible_val = 0; traverse_possible_val < 9; traverse_possible_val++ )
  {
    if( numr[traverse_possible_val] == traverse_possible_val+1  &&
        (possible_values[row][col][traverse_possible_val] == traverse_possible_val + 1) )
    {
      printf("\nRow %d, col %d solved. Value : %d [Across row, this value is unique]", row, col, traverse_possible_val+1);
      value_fixed = sudoku_puzzle[row][col] = traverse_possible_val+1;
      clear_missing_possible_arrays( row, col, traverse_possible_val+1 );
      num_fixed++;
      break;
    } //if block
    if( numc[traverse_possible_val] == traverse_possible_val+1 &&
        (possible_values[row][col][traverse_possible_val] == traverse_possible_val + 1) )
    {
      printf("\nRow %d, col %d solved. Value : %d [Across column, this value is unique]", row, col, traverse_possible_val+1);
      value_fixed = sudoku_puzzle[row][col] = traverse_possible_val+1;
      clear_missing_possible_arrays( row, col, traverse_possible_val+1 );
      num_fixed++;
      break;
    }
    if( (num3x3m[traverse_possible_val] == traverse_possible_val+1) &&
        (possible_values[row][col][traverse_possible_val] == traverse_possible_val+ 1) )
    {
      printf("\nRow %d, col %d solved. Value : %d [Across 3x3 matrix, this value is unique]", row, col, traverse_possible_val+1);
      value_fixed = sudoku_puzzle[row][col] = traverse_possible_val+1;
      num_fixed++;
      clear_missing_possible_arrays( row, col, traverse_possible_val+1 );
      break;
    }
  } //for( traverse_possible_val )


  //if( num_fixed != 0 )
  //{
  //  char dummy;
  //  scanf("%c", &dummy);
  //}
  return num_fixed;
}

int solve_sudoku_4th_level( int sudoku_puzzle[9][9] )
{
  int  row                 = 0;
  int  col                 = 0;
  int  num_possible_vals   = 0;
  int  counter             = 0;
  int  possible_2_vals[2]  = { 0, 0 };

  for( row = 0; row < 9; row++ )
  {
    for( col = 0; col < 9; col++ )
    {
      num_possible_vals = 0;
      possible_2_vals[0] = 0;
      possible_2_vals[1] = 0;
      for( counter = 0; counter < 9; counter++ )
      {
        if( possible_values[row][col][counter] == counter+1 )
        {
          if( num_possible_vals < 2 )
            possible_2_vals[num_possible_vals] = counter+1;
          num_possible_vals += 1;
        }
      }
      if( num_possible_vals == 2 )
        solve_row_col_4th_level( row, col, possible_2_vals );
    }
  }

  return 0;
}

int solve_row_col_4th_level( int row, int col, int possible_2_vals[2] )
{
  int  traverse_row             = 0;
  int  traverse_col             = 0;
  int  counter                  = 0;
  int  num_possible_vals        = 0;
  int  possible_2_oc_vals[2]    = { 0, 0 };

  for( traverse_row = 0; traverse_row < 9; traverse_row++ )
  {
    if( traverse_row == row )
      continue;
    num_possible_vals = 0;
    possible_2_oc_vals[0] = 0;
    possible_2_oc_vals[1] = 0;
    for( counter = 0; counter < 9; counter++ )
    {
      if( possible_values[traverse_row][col][counter] == counter+1 )
      {
          if( num_possible_vals < 2 )
            possible_2_oc_vals[num_possible_vals] = counter + 1;
          num_possible_vals += 1;
      }
    }
    if( num_possible_vals == 2 && 
        possible_2_vals[0] == possible_2_oc_vals[0] &&
        possible_2_vals[1] == possible_2_oc_vals[1] )
    {
        for( counter = 0; counter < 9; counter++ )
        {
          if( counter == row || counter == traverse_row )
            continue;
          clear_missing_possible_arrays( counter, col, possible_2_vals[0] );
          clear_missing_possible_arrays( counter, col, possible_2_vals[1] );
        }
        break;
    }
  }

  for( traverse_col = 0; traverse_col < 9; traverse_col++ )
  {
    if( col == traverse_col )
      continue;
    num_possible_vals = 0;
    possible_2_oc_vals[0] = 0;
    possible_2_oc_vals[1] = 0;

    for( counter = 0; counter < 9; counter++ )
    {
      if( possible_values[row][traverse_col][counter] == counter+1 )
      {
          if( num_possible_vals < 2 )
            possible_2_oc_vals[num_possible_vals] = counter+1;
          num_possible_vals += 1;
      }
    }

    if( num_possible_vals == 2 && 
        possible_2_vals[0] == possible_2_oc_vals[0] &&
        possible_2_vals[1] == possible_2_oc_vals[1] )
    {
        for( counter = 0; counter < 9; counter++ )
        {
          if( counter == col || counter == traverse_col )
            continue;
          clear_missing_possible_arrays( row, counter, possible_2_vals[0] );
          clear_missing_possible_arrays( row, counter, possible_2_vals[1] );
        }
        break;
    }
  }

  for( traverse_row = (row/3); traverse_row < (row/3)+2; traverse_row++ )
  {
    for( traverse_col = (col/3); traverse_col < (col/3)+2; traverse_col++ )
    {
      if( traverse_row == row && traverse_col == col )
        continue;

    }
  }

  return 0;
}

void print_sudoku( int sudoku_puzzle[9][9] )
{
  int row, col = 0;
  printf("\n");
  for( row = 0; row < 9; row++ )
  {
    int level = 0;
    printf("\n+-----+-----+-----+-----+-----+-----+-----+-----+-----+");
    for( level = 0; level < 3; level++ )
    {
      for( col = 0; col < 9; col++)
      {
        if( col == 0 )
          printf("\n");
        if( sudoku_puzzle[row][col] == 0 )
        {
          printf("|");
          possible_values[row][col][(level*3)+0] == 0 ? printf(".") : printf("%d", possible_values[row][col][(level*3)+0]);
          possible_values[row][col][(level*3)+1] == 0 ? printf(" .") : printf(" %d", possible_values[row][col][(level*3)+1]);
          possible_values[row][col][(level*3)+2] == 0 ? printf(" .") : printf(" %d", possible_values[row][col][(level*3)+2]);
        }

        if( level == 0 && sudoku_puzzle[row][col] != 0 )
          printf("|     ");
        else if( level == 1 && sudoku_puzzle[row][col] != 0 )
          printf("|  %d  ", sudoku_puzzle[row][col]);
        else  if( level == 2 && sudoku_puzzle[row][col] != 0 )
          printf("|     ");

        if( (col+1)%3 == 0 )
          printf("");
      } //for inner loop
      printf("|");
      if( (row+1)%3 == 0 )
        printf("");
    } //level for loop
  } //for outer loop
  printf("\n+-----+-----+-----+-----+-----+-----+-----+-----+-----+");
}

void clear_missing_possible_arrays( int row, int col, int value_fixed )
{
  int traverse_rc3m;
  int matrix3x3_id = (row/3)*3+(col/3);
  
  missing_numbers_in_rows[row][value_fixed-1] = 0;
  missing_numbers_in_cols[col][value_fixed-1] = 0;
  missing_numbers_in_3x3matrix[matrix3x3_id][value_fixed-1] = 0;

  //After fixing value, clear that number from possible_values[9][9][9] matrix
  //in corresponding row, column, and 3x3 matrix
  for( traverse_rc3m = 0; traverse_rc3m < 9; traverse_rc3m++ )
  {
    possible_values[row][traverse_rc3m][value_fixed-1] = 0;
    possible_values[traverse_rc3m][col][value_fixed-1] = 0;
    possible_values[((row/3)*3)+traverse_rc3m/3][((col/3)*3)+traverse_rc3m%3][value_fixed-1] = 0;
  } // for loop
  //print_sudoku( sudoku_puzzle );
}

void print_missing_numbers()
{
  int row  = 0;
  int col  = 0;

  for( row = 0; row < 9; row++)
  {
    printf("\nNumbers not available in row #: %d\n", row+1);
    for( col = 0; col < 9; col++ )
    {
      if( missing_numbers_in_rows[row][col] != 0 )
        printf("%d ", missing_numbers_in_rows[row][col]);
    }
  }
  for( row = 0; row < 9; row++)
  {
    printf("\nNumbers not available in column  #: %d\n", row+1);
    for( col = 0; col < 9; col++ )
    {
      if( missing_numbers_in_cols[row][col] != 0 )
        printf("%d ", missing_numbers_in_cols[row][col]);
    }
  }
  for( row = 0; row < 9; row++)
  {
    printf("\nNumbers not available in 3x3 Matrix  #: %d\n", row+1);
    for( col = 0; col < 9; col++ )
    {
      if( missing_numbers_in_3x3matrix[row][col] != 0 )
        printf("%d ", missing_numbers_in_3x3matrix[row][col]);
    }
  }

  return;
}


