#include "Box.cpp"
#include <ncurses.h>
#include <unistd.h>
#include<vector> 
using namespace std;

#define HEIGHT 30
#define WIDTH 50

class GameMap{
    private:
        Box* gmap[HEIGHT][WIDTH];
        vector<pair<int, pair<int, int>>> body_history;

    public:
        GameMap(){
            start_color();
            init_pair(1, COLOR_BLACK, COLOR_BLACK);
            init_pair(2, COLOR_WHITE, COLOR_WHITE);
            init_pair(3, COLOR_GREEN, COLOR_GREEN);
            init_pair(4, COLOR_RED, COLOR_RED);
            init_pair(5, COLOR_BLUE, COLOR_BLUE);
            init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    gmap[i][j] = new Box(j, i);
                }
            }
        }

        ~GameMap(){
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    delete gmap[i][j];
                }
            }
        }

        template <typename T>
        void convert(int x, int y){
            gmap[x][y] = new T((Box *)gmap[x][y]);
        }

        void encounter(int x, int y, Snake &s){
            int longer_body = gmap[x][y]->encounter(s); //Snake의 몸길이가 짧아졌는지, 늘어났는지, 그대로인지
            for (auto it = body_history.begin(); it != body_history.end(); it++){
                it->first = max(0, it->first+(longer_body)-1);

                if(it->first==0){ //시간이 지나 or Snake Body가 짧아진 경우
                    convert<Box>(it->second.first,it->second.second);
                    body_history.erase(it);
                    continue;
                }

                if(it->first==1){ // Item 먹고 Snake Body가 길어진 경우
                    convert<SnakeBody>(it->second.first,it->second.second);
                }
            }
            body_history.push_back(make_pair(s.length, make_pair(x, y)));
        }

        void show_map(){
            for(int i=0;i<HEIGHT;i++){
                for(int j=0;j<WIDTH;j++){
                    gmap[i][j]->show();
                }
            }
        }
};

int main(){
    initscr();
    cbreak();

    GameMap gmap;
    //make wall
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1) gmap.convert<Wall>(i,j);
        }
    }
    
    //item1
    gmap.convert<Item1>(3,2);
    gmap.convert<Item1>(5,4);
    
    //item2
    gmap.convert<Item1>(7,30);
    gmap.convert<Item1>(8,15);

    //snakebody
    gmap.convert<SnakeBody>(10,40);
    gmap.convert<SnakeBody>(10,41);
    gmap.convert<SnakeBody>(10,42);
    gmap.convert<SnakeBody>(10,43);
    
    gmap.show_map();
    sleep(1);

    //snakebody
    gmap.convert<Box>(10,40);
    gmap.convert<SnakeBody>(10,41);
    gmap.convert<SnakeBody>(10,42);
    gmap.convert<SnakeBody>(10,43);
    gmap.convert<SnakeBody>(10,44);

    gmap.show_map();
    sleep(1);
    endwin();
}