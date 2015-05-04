#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "snake.h"


void
init()
{
	// Terminal environment init
	WINDOW *wnd;

	wnd = initscr();
	keypad(wnd, TRUE);
	cbreak();
	noecho();
	clear();

	// dir init
	dir.x = 0;
	dir.y = 0;
	// food init
	food.x = 0;
	food.y = 0;
	// interval timer value
	delay = 200;

	p1.x = 5;
	p1.y = 5;
	Q = (queue)malloc(sizeof(struct q_node));
	init_queue(Q);
	front_enqueue(p1, Q);

	move(p1.y, p1.x);
	addch(SHAPE);
	move(LINES-1, COLS-1);
	refresh();

	// Signal and ticker TODO
	signal(SIGALRM, snake_move);	//Use timer to control moving.
	set_ticker(delay);
}


// This func is for signal
void	// default moving dir: right.
snake_move()	//TODO
{
	//
	// if (position.x > COLS)

	p1 = rear_dequeue(Q);
	move(p1.y, p1.x);
	addch(BLANK);
	p1.x += dir.x;
	p1.y += dir.y;
	move(p1.y, p1.x);
	addch(SHAPE);
	move(LINES-1, COLS-1);
	refresh();

	front_enqueue(p1, Q);
	signal(SIGALRM, snake_move);

	// if ()	// after eat TODO
		// produce_food();
}

/*
void
eat()
{

}
*/

//TODO
void
produce_food()	//TODO one more timer for the food
{
	food.x = rand() % COLS;	//COLS AND LINES IN THE TERMINAL
	food.y = rand() % (LINES - 1); //use one line to show some info.
	move(food.y, food.x);
	addch(FOOD);
	move(LINES-1, COLS-1);
	refresh();
}

int
set_ticker(int n_msecs)	// Set the interval timer
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;

	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void
end()
{
	endwin();	// Reset the terminal.
	destroy_queue(Q);
	free(Q);
}