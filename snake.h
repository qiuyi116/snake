//
// Why this file is not pure C???
//
#ifndef SNAKE_H
#define SNAKE_H


#define  SHAPE  '*'
#define  BLANK  ' '
#define  FOOD   '@'

// Global curses vars
// KEY_UP
// KEY_DOWN
// KEY_LEFT
// KEY_RIGHT

// COLS
// LINES
// End global curses vars

// The struct for positionition
typedef struct pos_node {
	int x;  // x to col
	int y;  // y to row
} position;


// The struct of snake node
struct snake;
struct q_node;
typedef struct snake  *ptr_snake;
typedef struct q_node *queue;

struct snake {
	position pos;
	ptr_snake pre;
	ptr_snake next;
};

// The struct for queue's front and rear
struct q_node {
	ptr_snake front;
	ptr_snake rear;
};

// Operation for the snake node
void init_queue(queue);	// init a queue
void destroy_queue(queue);	// destroy a queue
int is_exist(position, queue); // search if X exist in queue Q, 1 or 0
position get_front(queue);
void front_enqueue(position, queue);	// enqueue X at front
position rear_dequeue(queue);	// dequeue from rear
// End

// For error handling
void error(const char*);
void fatal_error(const char*);
void logging(const char*);	// log time and the error reason
// End

// init the terminal environment
void init();
// get input order
void get_order();
// the moving of the snake
void snake_move();
// random produce food
void produce_food();
// set iterval timer
int set_ticker(int);
// reset terminal and free memory
void end();


// void death();
// reset the terminal environment and free memory

// TODO where to set them? Is this a sytax(?) of cpp but not pure c?
// Some global vars
// int hour, min, sec;
// int level;

#endif
//	SNAKE_H
