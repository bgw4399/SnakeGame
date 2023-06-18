#include <random>
#include <unistd.h>
#include <ncurses.h>

#include "Map.cpp"

class GamePlay{
    std::mt19937_64 generator;
    GameMap gmap;
    Snake s;
    int timer, temp;
    ScoreBoard score;
    public:
        GamePlay():s(6), score(30, 7, WIDTH+3, 5){
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    if(i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1) gmap.convert<Wall>(i,j);
                }
            }
            gmap.convert_to_portal(0, 3, 10, 0); // Gate 출현 방법 미구현
            gmap.convert_to_portal(10,0, 0, 3);
            timer = 0;            
        }

        void play(){
            int temp;
            while(1){
                gmap.show_map();
                score.show(s);
                sleep(s.tick);
                move();
                get_random_item();
                if(ScoreBoard::game_over) return;
            }
        }

        void move(){
            timer++;
            temp = getch();
            s.direction = (temp != -1) ? temp : s.direction;
            switch(s.direction){
                case 'w':
                gmap.map_encounter(--s.pos_x, s.pos_y, s);
                break;
                case 's':
                gmap.map_encounter(++s.pos_x, s.pos_y, s);
                break;
                case 'a':
                gmap.map_encounter(s.pos_x, --s.pos_y, s);
                break;
                case 'd':
                gmap.map_encounter(s.pos_x, ++s.pos_y, s);
                break;
            }
        }

        void get_random_item_box(){
            int pos_x = generator()%HEIGHT, pos_y = generator()%WIDTH;
            if(gmap.is_empty(pos_x, pos_y)){
                if(generator()%2) gmap.item_insert<Item1>(pos_x, pos_y);
                else gmap.item_insert<Item2>(pos_x, pos_y);
            }
            else{
                get_random_item_box();
            }
        }

        void get_random_item(){
            if (timer>10){
                get_random_item_box();
                timer = 0;
            }
        }


};

int ScoreBoard::game_over = 0;
int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    ScoreBoard::start();
    GamePlay game;
    game.play();
    endwin();
}