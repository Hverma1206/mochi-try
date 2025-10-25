#include <ncurses.h> 
#include <unistd.h> 

int main() {
    int x = 0, y = 10; 
    int direction = 1; 
    int max_x, max_y;

    initscr();            
    noecho();             
    curs_set(0);        
    timeout(50);          

    getmaxyx(stdscr, max_y, max_x);

    while (true) {
        
        clear(); 

        mvprintw(y, x, "O"); 
        
        refresh(); 

        x = x + direction;

        if (x >= max_x - 1) 
        { 
            direction = -1;
        } else if (x <= 0) 
        {
            direction = 1;
        }

        if (getch() == 'q') 
        {
            break;
        }
        
    }

    endwin(); 
    return 0;
}