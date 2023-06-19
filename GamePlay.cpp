#include <random>
#include <unistd.h>
#include <ncurses.h>

#include "Map.cpp"

class GamePlay{
    std::random_device rd;
    std::mt19937_64 generator;
    GameMap gmap;
    Snake s;
    ScoreBoard score;
    int timer, temp, level;
    public:
        GamePlay(int level):s(6), score(30, 7, WIDTH+3, 5), generator(rd()), level(level){
            // for (int i = 0; i < HEIGHT; i++) {
            //     for (int j = 0; j < WIDTH; j++) {
            //         if(i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1) gmap.convert<Wall>(i,j);
            //     }
            // }
            generate_random_map();
            timer = 0;            
        }

        void generate_random_map(){
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    if(i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1) gmap.convert<Wall>(i,j);
                    else gmap.convert<Box>(i,j);
                }
            }

            int cnt=0;
            while(cnt<level){
                if(generate_wall(generator() % 20, 1+(generator()%(WIDTH-2)), 1+(generator()%(HEIGHT-2)), generator()%2==0)) cnt++;
            }
        }

        void play(){
            int temp;
            ScoreBoard::start();
            while(1){
                gmap.show_map();
                score.show(s);
                sleep(s.tick);
                move();
                get_random_item();
                if(ScoreBoard::game_over) return;
            }
        }

        bool generate_wall(int length, int x, int y, bool is_vertical){
            if(!gmap.is_empty(x, y)) return false;
            if(length==0) return true;
            if(is_vertical){
                if(!generate_wall(length-1, x-1, y, is_vertical)) return false;
                gmap.convert<Wall>(x, y);
                return true;
            }
            else{
                if(!generate_wall(length-1, x, y+1, is_vertical)) return false;
                gmap.convert<Wall>(x, y);
                return true;
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

        void get_random_item(){
            if (timer%10==0){
                get_random_item_box();
            }

            if(s.length>=10){
                if(timer%300==0) get_portal_box();
            }
        }

        void get_random_item_box(){
            int pos_x = generator()%HEIGHT, pos_y = generator()%WIDTH;
            if(gmap.is_empty(pos_x, pos_y)){ // Box인지
                if(generator()%2) gmap.item_insert<Item1>(pos_x, pos_y);
                else gmap.item_insert<Item2>(pos_x, pos_y);
            }
            else{
                get_random_item_box();
            }
        }

        void get_portal_box(){
            int pos_x = generator()%HEIGHT, pos_y = generator()%WIDTH, pos_ox = generator()%HEIGHT, pos_oy = generator()%WIDTH;
            if(gmap.is_wall(pos_x, pos_y) && gmap.is_wall(pos_ox, pos_oy) &&!((pos_x==pos_ox)&&(pos_y==pos_oy))){
                gmap.portal_insert(pos_x, pos_y, pos_ox, pos_oy);
            }
            else{
                get_portal_box();
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
    GamePlay(1).play();
    GamePlay(2).play();
    GamePlay(3).play();
    GamePlay(4).play();
    GamePlay(5).play();
    endwin();
}