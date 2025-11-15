#include <ncurses.h>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Particle {
    int x, y;
    int lifetime;
    char symbol;
};

int main() {
    srand(time(NULL));
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
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    
    int center_x = max_x / 2;
    int center_y = max_y / 2;
    
    int pupil_offset_x = 0;
    int pupil_offset_y = 0;
    int blink_state = 0;
    int frame_count = 0;
    float wave_offset = 0.0;
    int emotion_state = 0;
    int eyebrow_offset = 0;
    float head_bob = 0.0;
    std::vector<Particle> particles;

    while (true) {
        clear();
        
        head_bob = sin(frame_count * 0.05) * 1.5;
        int bob_y = (int)head_bob;
        
        if (frame_count % 120 < 60) {
            pupil_offset_x = (frame_count % 120) / 30 - 1;
        } else {
            pupil_offset_x = 1 - (frame_count % 120) / 30;
        }
        
        pupil_offset_y = sin(frame_count * 0.08) > 0 ? 0 : 0;
        
        //mood changes in every 100 frames
        if (frame_count % 400 < 100) {
            emotion_state = 0;
        } else if (frame_count % 400 < 200) {
            emotion_state = 1;
        } else if (frame_count % 400 < 300) {
            emotion_state = 2;
        } else {
            emotion_state = 3;
        }
        
        if (frame_count % 150 == 0) {
            blink_state = 1;
        } else if (frame_count % 150 == 3) {
            blink_state = 2;
        } else if (frame_count % 150 == 6) {
            blink_state = 0;
        }
        
        wave_offset = sin(frame_count * 0.1) * 2;
        
        if (emotion_state == 0) {
            eyebrow_offset = 0;
        } else if (emotion_state == 1) {
            eyebrow_offset = -1;
        } else if (emotion_state == 2) {
            eyebrow_offset = 1;
        } else {
            eyebrow_offset = -2;
        }
        
        if (frame_count % 80 == 0 && emotion_state == 0) {
            for (int i = 0; i < 3; i++) {
                Particle p;
                p.x = center_x + (rand() % 20 - 10);
                p.y = center_y - 6 + (rand() % 4);
                p.lifetime = 20 + rand() % 10;
                p.symbol = (rand() % 2) ? '*' : '+';
                particles.push_back(p);
            }
        }
        
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(center_y - 5 + bob_y, center_x - 8, "  .-\"\"\"\"\"\"\"\"-.");
        mvprintw(center_y - 4 + bob_y, center_x - 8, " /            \\");
        mvprintw(center_y - 3 + bob_y, center_x - 8, "|              |");
        mvprintw(center_y - 2 + bob_y, center_x - 8, "|              |");
        mvprintw(center_y - 1 + bob_y, center_x - 8, "|              |");
        mvprintw(center_y + bob_y,     center_x - 8, "|              |");
        mvprintw(center_y + 1 + bob_y, center_x - 8, "|              |");
        mvprintw(center_y + 2 + bob_y, center_x - 8, " \\            /");
        mvprintw(center_y + 3 + bob_y, center_x - 8, "  '-.______.-'");
        attroff(COLOR_PAIR(2) | A_BOLD);
        
        attron(COLOR_PAIR(6) | A_BOLD);
        if (emotion_state == 3) {
            mvprintw(center_y - 4 + eyebrow_offset + bob_y, center_x - 5, "v");
            mvprintw(center_y - 4 + eyebrow_offset + bob_y, center_x + 4, "v");
        } else {
            mvprintw(center_y - 4 + eyebrow_offset + bob_y, center_x - 5, emotion_state == 1 ? "^" : "-");
            mvprintw(center_y - 4 + eyebrow_offset + bob_y, center_x + 4, emotion_state == 1 ? "^" : "-");
        }
        attroff(COLOR_PAIR(6) | A_BOLD);
        
        if (emotion_state == 3) {
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(center_y - 2 + bob_y, center_x - 5, "   ");
            mvprintw(center_y - 1 + bob_y, center_x - 5, "   ");
            attroff(COLOR_PAIR(1) | A_BOLD);
            
            attron(COLOR_PAIR(5) | A_BOLD);
            mvprintw(center_y - 2 + bob_y, center_x - 5 + 1 + pupil_offset_x, ".");
            attroff(COLOR_PAIR(5) | A_BOLD);
            
            mvprintw(center_y - 2 + bob_y, center_x + 3, " . ");
        } else if (blink_state == 0) {
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(center_y - 2 + bob_y, center_x - 5, "   ");
            mvprintw(center_y - 1 + bob_y, center_x - 5, "   ");
            attroff(COLOR_PAIR(1) | A_BOLD);
            
            attron(COLOR_PAIR(5) | A_BOLD);
            if (emotion_state == 1) {
                mvprintw(center_y - 2 + pupil_offset_y + bob_y, center_x - 5 + 1, "O");
            } else {
                mvprintw(center_y - 2 + pupil_offset_y + bob_y, center_x - 5 + 1 + pupil_offset_x, "o");
            }
            attroff(COLOR_PAIR(5) | A_BOLD);
            
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(center_y - 2 + bob_y, center_x + 3, "   ");
            mvprintw(center_y - 1 + bob_y, center_x + 3, "   ");
            attroff(COLOR_PAIR(1) | A_BOLD);
            
            attron(COLOR_PAIR(5) | A_BOLD);
            if (emotion_state == 1) {
                mvprintw(center_y - 2 + pupil_offset_y + bob_y, center_x + 3 + 1, "O");
            } else {
                mvprintw(center_y - 2 + pupil_offset_y + bob_y, center_x + 3 + 1 + pupil_offset_x, "o");
            }
            attroff(COLOR_PAIR(5) | A_BOLD);
        } else if (blink_state == 1) {
            mvprintw(center_y - 2 + bob_y, center_x - 5, " - ");
            mvprintw(center_y - 2 + bob_y, center_x + 3, " - ");
        } else {
            mvprintw(center_y - 2 + bob_y, center_x - 5, "___");
            mvprintw(center_y - 2 + bob_y, center_x + 3, "___");
        }
        
        attron(COLOR_PAIR(3) | A_BOLD);
        if (emotion_state == 2) {
            mvprintw(center_y + bob_y, center_x - 7, "O");
            mvprintw(center_y + bob_y, center_x + 7, "O");
        } else {
            mvprintw(center_y + bob_y, center_x - 6, "o");
            mvprintw(center_y + bob_y, center_x + 6, "o");
        }
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        attron(COLOR_PAIR(4) | A_BOLD);
        if (emotion_state == 0) {
            mvprintw(center_y + 1 + bob_y, center_x - 2, " \\_/ ");
           //happy
        } else if (emotion_state == 1) {
            //surprise
            mvprintw(center_y + 1 + bob_y, center_x - 2, "  O  ");
        } else if (emotion_state == 2) {
            //shy
            mvprintw(center_y + 1 + bob_y, center_x - 2, " ^_^ ");
        } else {
            //sad
            mvprintw(center_y + 1 + bob_y, center_x - 2, " v_v ");
        }
        attroff(COLOR_PAIR(4) | A_BOLD);
        
        attron(COLOR_PAIR(7) | A_BOLD);
        for (auto it = particles.begin(); it != particles.end();) {
            if (it->lifetime > 0) {
                mvprintw(it->y, it->x, "%c", it->symbol);
                it->lifetime--;
                it->y--;
                ++it;
            } else {
                it = particles.erase(it);
            }
        }
        attroff(COLOR_PAIR(7) | A_BOLD);
        
        const char* mood_text[] = {"Happy", "Surprised", "Shy", "Sad"};
        attron(COLOR_PAIR(5));
        mvprintw(center_y + 5 + bob_y, center_x - 4, "Mood: %s", mood_text[emotion_state]);
        attroff(COLOR_PAIR(5));
        //unlimted frames till i stop
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


//idk why i am doing this but its fun