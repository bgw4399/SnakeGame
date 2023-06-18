#include <ncurses.h>
#include <unistd.h>
#include <deque>
using namespace std;

#include "Box.cpp"

class GameMap{
    private:
        Box* gmap[HEIGHT][WIDTH];
        deque<pair<int, int>> body_history;
        deque<pair<int, int>> item_history;

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
            if(!(x>=HEIGHT || x<0 || y>=WIDTH || y<0) && gmap[x][y]->is_convertable())
                gmap[x][y] = new T((Box *)gmap[x][y]);
        }

        void convert_to_portal(int x, int y, int ox, int oy){
            if(!(x>=HEIGHT || x<0 || y>=WIDTH || y<0))
                gmap[x][y] = new Portal((Box *)gmap[x][y], ox, oy);
        }

        bool is_empty(int x, int y){
            return gmap[x][y]->is_empty();
        }

        void map_encounter(int x, int y, Snake &s){
            gmap[x][y]->encounter(s);
            convert<SnakeBody>(x, y);
            body_history.push_back(make_pair(x, y));
            while(body_history.size() > s.length){
                auto item = body_history.front();
                convert<Box>(item.first,item.second);
                body_history.pop_front();
            } 
        }


        template <typename T>
        void item_insert(int x, int y){
            convert<T>(x, y);
            item_history.push_back(make_pair(x, y));
            if(item_history.size()==4){
                auto item = item_history.front();
                convert<Box>(item.first, item.second);
                item_history.pop_front();
            }
        }

        void show_map(){
            for(int i=0;i<HEIGHT;i++){
                for(int j=0;j<WIDTH;j++){
                    gmap[i][j]->show();
                }
            }
        }
};