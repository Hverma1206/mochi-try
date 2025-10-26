#include <ncurses.h>
#include <unistd.h>

int main() {
    int eye_x_left = 10;
    int eye_x_right = 20;
    int eye_y = 5;
    int move_direction = 1;
    int blink_state = 0;
    int frame_count = 0;

    int max_x, max_y;

    initscr();
    noecho();
    curs_set(0);
    timeout(50);

    getmaxyx(stdscr, max_y, max_x);

    while (true) {
        clear();

        if (frame_count % 40 == 0)
         {
            blink_state = 1;
        } 
        else if (frame_count % 40 == 1) 
        {
            blink_state = 2;
        } 
        else if (frame_count % 40 == 2) 
        {
            blink_state = 1;
        } 
        else if (frame_count % 40 == 3)
         {
            blink_state = 0;
        }

        if (blink_state == 0) {
            mvprintw(eye_y, eye_x_left, "( )");
        } 
        
    
        else if (blink_state == 1) {
            mvprintw(eye_y, eye_x_left, " - ");
        } 
        else {
            mvprintw(eye_y, eye_x_left, "---");
        }

        if (blink_state == 0)
         {
            mvprintw(eye_y, eye_x_right, "( )");
        } 
        else if
         (blink_state == 1) {
            mvprintw(eye_y, eye_x_right, " - ");
        } 
        else 
        {
            mvprintw(eye_y, eye_x_right, "---");
        }
        mvprintw(eye_y + 1, (eye_x_left + eye_x_right) / 2, "_");
        refresh();
        if (getch() == 'q') 
        {
            break;
        }
        
        frame_count++;
    }

    endwin();
    return 0;
}