#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iso646.h>

#define TRUE 1;
#define FALSE 0;

#define OK 1;
#define CLEAR 0;
#define ERROR -1;
#define OVERFLOW -2;
#define NULL ((void *)0);
//printf ("%c", NULL);
#define NOTFOUND 0;




int inital_grid[9][9];//for when i change it to solve instead of just generating random ones
int temp_grid[9][9];//for making changes to each number allowing us to revert to the original if any issues are encountered
int grid[9][9];// our main grid
int rano;// a random integer which is used to begin the proccess
int current_numb;//current number im attempting to find a place for
int line_place = 3; // which spot in the line we are dealing with... integer beetween 0-8
int current_line= 0;// which line we are dealing with... integer beetween 0-8
int is_allowed = 0;// a boolean which returns false if any illegal positions are found
int numb_of_spaces;//an int which represents the number of available spaces on the current line
int position_of_new;// place in the line the random generator generated to attempt  (available spaces-1)
int full;// a boolean which returns true when the board is full
int start_x, start_y;//values for the inner grid test
int num_of_calls = 0;


int* ptr;//a ptr used to store var directly to memory


void clear_grid(void); //init clear grid to 0s   [[done]]
int get_open_spaces(void);//set value of numb_of_spaces (available spaces on line) using Current_line  [[done]]
int random_location(void);// sets value value_of_new[[done]]
int check_grid_y(void);// checks y axis            [[done]]
int check_grid_inter(void);//checks 3 by 3 cubes   [[done]]
void place_values(void);// places values if all is good
void check_full_grid(void);
int which_box(void);
int if_allowed(void);
int random_grid(void);
void print_grid(void);
void main_loop(void);

void show_grid(void);
void check_grid_x(void);




int main(void) {
    //int ih = 4 > 6? 3: 0;
   // printf("%i", ih);
    printf(" \n \n");
    ptr = NULL;

    //printf("%p \n \n", ptr);
    srand(time(0));
    //print_grid();
    for (int i = 0; i < 1; i++) {
        int g = 1;
        while (g == 1) {
            if (full) {
                g = 0;
                //break;
            }
            clear_grid();
            main_loop();
        }
    }
    //main_loop();
    printf("\n \n");
    num_of_calls = num_of_calls * 10;
    printf("%d", num_of_calls);
    exit(0);
}

void main_loop(void) {
    for (int k = 0; k < 9; k++) {
        ptr = &current_line;
        *ptr = k;
        ptr = NULL;
        for (int i = 1; i < 10; i++) {
            ptr = &current_numb;
            *ptr = i;
            ptr = NULL;
            is_allowed = 0;
            int tries = 0;
            while (!is_allowed) {
                tries++;
                if (tries > 10) {
                    break;
                }
                //printf("%d ", is_allowed);
                is_allowed = 1;
                get_open_spaces();
                random_location();
                //is_allowed = 1;
                check_grid_y();
                if (is_allowed) {

                    check_grid_inter();
                }


            }
            //printf("\n\n isallow %d \n\n", is_allowed);
            if (is_allowed == 1 && current_numb != 0) {
                place_values();
            }
            check_full_grid();
            if (full) {
                print_grid();
                return;
            }
            //print_grid();
        }
    }
}


void clear_grid(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ptr = &grid[i][j];
            *ptr = 0;
            ptr = NULL;
        }
    }
    //return grid;
}


void check_full_grid(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                ptr = &full;
                *ptr = 0;
                ptr = NULL;
                //print_grid();
                return;
            }
        }
    }
    ptr = &full;
    *ptr = 1;
    ptr = NULL;
    //print_grid();
}

void print_grid(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d  ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void place_values(void) {
    ptr = &grid[current_line][position_of_new];
    *ptr = current_numb;
    ptr = NULL;
}

int check_grid_y(void) {
    ptr = &num_of_calls;
    (*ptr)++;
    ptr =NULL;
    for (int i = 0; i < 9; i++) {
        if (grid[i][position_of_new] == current_numb) {
            if (i != current_line) {
                ptr = &is_allowed;
                *ptr = 0;
                ptr = NULL;
                return 0;
            }
            break;
        }
    }
    return 1;
}

int get_open_spaces(void) {
    ptr = &numb_of_spaces;
    *ptr = 0;
    ptr = NULL;
    for (int i = 0; i < 9; i++) {
        if (grid[current_line][i] == 0) {
            ptr = &numb_of_spaces;
            (*ptr)++;  // = numb_of_spaces++;
            ptr = NULL;
        }
    }
}

int random_location(void) {
    int defg = numb_of_spaces + 1;
    ptr = &position_of_new;
    *ptr = 0;
    ptr = NULL;

    rano = rand() % numb_of_spaces;/// add 1 because index starts with zero

    int j = 0;
    for (int i = 0; i < 9; i++) {
        if (grid[current_line][i] == 0) {
            if (j == rano) {
                ptr = &position_of_new;
                *ptr = i;
                ptr = NULL;
                return 1;
            }
            j++;
        }
    }
    return 0;
}


int check_grid_inter(void) {
    ptr = &start_x;
    int* ptr_2 = &start_y;
    if (position_of_new < 3) {
        *ptr = 0;
    }else if (position_of_new > 2 && position_of_new < 6) {
        *ptr = 3;

    }else if (position_of_new > 5) {
        *ptr = 6;
    }
    if (current_line < 3) {
        *ptr_2 = 0;
    }else if (current_line > 2 && current_line < 6) {
        *ptr_2 = 3;

    }else if (current_line > 5) {
        *ptr_2 = 6;
    }
    ptr = NULL;
    ptr_2 = NULL;
    //printf("%d", start_x);
    int max_x = start_x + 3;
    int max_y = start_y + 3;
    for (int i = start_y; i < max_y; i++) {
        for (int j = start_x; j < max_x; j++) {
            if (grid[i][j] == current_numb) {
                //if (i != current_line) {
                ptr = &is_allowed;
                *ptr = 0;
                ptr = NULL;
                    //printf("%d  ", grid[i][j]);
                return 0;


            }
        }

    }
    ptr = &is_allowed;
    *ptr = 1;
    //printf("passed");
    ptr = NULL;
}




// ptr = &position_of_new;
// *ptr = rand() % (numb_of_spaces - 1) + 1;
// ptr = NULL;