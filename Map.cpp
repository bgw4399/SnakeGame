#include "Box.cpp"
#include <ncurses.h>
#include <unistd.h>

#define HEIGHT 30
#define WIDTH 50

class Map{
    private:
        Box* map[HEIGHT][WIDTH];
    public:
        Map(){
            start_color();
            init_pair(1, COLOR_BLACK, COLOR_BLACK);
            init_pair(2, COLOR_WHITE, COLOR_WHITE);
            init_pair(3, COLOR_GREEN, COLOR_GREEN);
            init_pair(4, COLOR_RED, COLOR_RED);
            init_pair(5, COLOR_BLUE, COLOR_BLUE);
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    map[i][j] = new Box(j, i);
                }
            }
        }
        ~Map(){
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    delete map[i][j];
                }
            }
        }

        template <typename T>
        void convert(int x, int y){
            map[x][y] = new T((Box *)map[x][y]);
        }

        void show_map(){
            for(int i=0;i<HEIGHT;i++){
                for(int j=0;j<WIDTH;j++){
                    map[i][j]->show();
                }
            }
        }
};

int main(){
    initscr();
    cbreak();

    Map map;
    //make wall
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1){
                map.convert<Wall>(i,j);
            }

        }
    }
    
    //item1
    map.convert<Item1>(3,2);
    map.convert<Item1>(5,4);
    
    //item2
    map.convert<Item1>(7,30);
    map.convert<Item1>(8,15);

    //snakebody
    map.convert<SnakeBody>(10,40);
    map.convert<SnakeBody>(10,41);
    map.convert<SnakeBody>(10,42);
    map.convert<SnakeBody>(10,43);
    
    map.show_map();
    sleep(3);

    //snakebody
    map.convert<Box>(10,40);
    map.convert<SnakeBody>(10,41);
    map.convert<SnakeBody>(10,42);
    map.convert<SnakeBody>(10,43);
    map.convert<SnakeBody>(10,44);

    map.show_map();
    sleep(3);
    endwin();
}