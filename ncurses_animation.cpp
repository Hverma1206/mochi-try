#include <ncurses.h>
#include <unistd.h>
int main() {
    int eye_x_left = 5;
    int eye_x_right = 18;
    int eye_y = 3;
    int move_direction = 1;
    int blink_state = 0;
    int frame_count = 0;

    int max_x, max_y;

    initscr();
    noecho();
    curs_set(0);
    timeout(50);
    start_color();
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);

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

        if (blink_state == 0)
         {
            attron(COLOR_PAIR(1));
            mvprintw(eye_y, eye_x_left, "   ");
            mvprintw(eye_y + 1, eye_x_left, " o ");
            mvprintw(eye_y + 2, eye_x_left, "   ");
            attroff(COLOR_PAIR(1));
            
            attron(COLOR_PAIR(1));
            mvprintw(eye_y, eye_x_right, "   ");
            mvprintw(eye_y + 1, eye_x_right, " o ");
            mvprintw(eye_y + 2, eye_x_right, "   ");
            attroff(COLOR_PAIR(1));
        } 
        else if (blink_state == 1) 
        {
            mvprintw(eye_y + 1, eye_x_left, "---");
            mvprintw(eye_y + 1, eye_x_right, "---");
        } 
        else 
        {
            mvprintw(eye_y + 1, eye_x_left, "===");
            mvprintw(eye_y + 1, eye_x_right, "===");
        }
        
        mvprintw(eye_y + 3, (eye_x_left + eye_x_right) / 2, "^");
        
        refresh();
        if (getch() == 'q') {
            break;
        }
        frame_count++;}
    endwin();
    return 0;
}