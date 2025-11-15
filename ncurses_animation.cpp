#include <ncurses.h>
#include <unistd.h>
#include <cmath>

int main() {
    initscr();
    noecho();
    curs_set(0);
    timeout(50);
    start_color();
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    
    int center_x = max_x / 2;
    int center_y = max_y / 2;
    
    int pupil_offset_x = 0;
    int pupil_offset_y = 0;
    int blink_state = 0;
    int frame_count = 0;
    float wave_offset = 0.0;

    while (true) {
        clear();
        
        if (frame_count % 120 < 60) {
            pupil_offset_x = (frame_count % 120) / 30 - 1;
        } else {
            pupil_offset_x = 1 - (frame_count % 120) / 30;
        }
        
        if (frame_count % 150 == 0) {
            blink_state = 1;
        } else if (frame_count % 150 == 3) {
            blink_state = 2;
        } else if (frame_count % 150 == 6) {
            blink_state = 0;
        }
        
        wave_offset = sin(frame_count * 0.1) * 2;
        
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(center_y - 5, center_x - 8, "  .-\"\"\"\"\"\"\"\"-.");
        mvprintw(center_y - 4, center_x - 8, " /            \\");
        mvprintw(center_y - 3, center_x - 8, "|              |");
        mvprintw(center_y - 2, center_x - 8, "|              |");
        mvprintw(center_y - 1, center_x - 8, "|              |");
        mvprintw(center_y,     center_x - 8, "|              |");
        mvprintw(center_y + 1, center_x - 8, "|              |");
        mvprintw(center_y + 2, center_x - 8, " \\            /");
        mvprintw(center_y + 3, center_x - 8, "  '-.______.-'");
        attroff(COLOR_PAIR(2) | A_BOLD);
        
        if (blink_state == 0) {
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(center_y - 2, center_x - 5, "   ");
            mvprintw(center_y - 1, center_x - 5, "   ");
            attroff(COLOR_PAIR(1) | A_BOLD);
            
            attron(COLOR_PAIR(5) | A_BOLD);
            mvprintw(center_y - 2, center_x - 5 + 1 + pupil_offset_x, "o");
            attroff(COLOR_PAIR(5) | A_BOLD);
            
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(center_y - 2, center_x + 3, "   ");
            mvprintw(center_y - 1, center_x + 3, "   ");
            attroff(COLOR_PAIR(1) | A_BOLD);
            
            attron(COLOR_PAIR(5) | A_BOLD);
            mvprintw(center_y - 2, center_x + 3 + 1 + pupil_offset_x, "o");
            attroff(COLOR_PAIR(5) | A_BOLD);
        } else if (blink_state == 1) {
            mvprintw(center_y - 2, center_x - 5, " - ");
            mvprintw(center_y - 2, center_x + 3, " - ");
        } else {
            mvprintw(center_y - 2, center_x - 5, "___");
            mvprintw(center_y - 2, center_x + 3, "___");
        }
        
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(center_y, center_x - 6, "o");
        mvprintw(center_y, center_x + 6, "o");
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        attron(COLOR_PAIR(4) | A_BOLD);
        int mouth_offset = (int)wave_offset;
        mvprintw(center_y + 1, center_x - 2, " \\_/ ");
        attroff(COLOR_PAIR(4) | A_BOLD);
        
        mvprintw(max_y - 2, 2, "Press 'q' to quit");
        attron(A_DIM);
        mvprintw(max_y - 1, 2, "Frame: %d", frame_count);
        attroff(A_DIM);
        
        refresh();
        
        if (getch() == 'q') {
            break;
        }
        
        frame_count++;
    }
    
    endwin();
    return 0;
}