//#include <iostream>
#include <ncurses.h>
#include<unistd.h>
#include <array>

using namespace std;

class Snake{
    public:
        int length;
    Snake(int length=0):length(length){};
};

class Box{
    protected:
        int sizex, sizey, gabx, gaby;
        WINDOW *local_win;
        
    public:
        Box(int sizex=5, int sizey=3, int gabx=5, int gaby=3):sizex(sizex), sizey(sizey), gabx(gabx), gaby(gaby){}
        virtual void encounter(Snake& s){}
        virtual WINDOW* show(int y, int x){
            local_win = newwin(sizey, sizex, y*gaby, x*gabx);
            box(local_win, 0 ,0);
            wrefresh(local_win);	
            return local_win;
        }
        virtual ~Box(){
            delwin(local_win);
        }
};

class Item1:public Box{
    public:
        void encounter(Snake& s){
            s.length++;
        }
        
        virtual WINDOW* show(int y, int x){
            local_win = newwin(sizey, sizex, y*gaby, x*gabx);
            box(local_win, 0 , 0);
            wattron(local_win, COLOR_PAIR(1));
            wmove(local_win, 1,2);
            wprintw(local_win, "*");
            wrefresh(local_win);	
            return local_win;
        }
};

class Item2:public Box{
    public:
        void encounter(Snake& s){
            s.length--;
        }

        WINDOW* show(int y, int x){
            
            local_win = newwin(sizex, sizey, y, x);
            box(local_win, 0 , 0);
            wrefresh(local_win);	
            return local_win;
        }
};

class SnakeBody:public Box{
    public:
        void encounter(Snake& s){
            //ScoreBoard::lose();
        }

        WINDOW* show(int y, int x){
            
            local_win = newwin(sizex, sizey, y, x);
            box(local_win, 0 , 0);
            wrefresh(local_win);	
            return local_win;
        }
};

class Wall:public Box{
    public:
        void encounter(Snake& s){
            //ScoreBoard::lose();
        }

        WINDOW* show(int y, int x){
            
            local_win = newwin(sizex, sizey , y, x);
            box(local_win, 0 , 0);
            wrefresh(local_win);	
            
            return local_win;
        }
};

#define HEIGHT 10
#define WIDTH 30

int main(){
    initscr();
    start_color();
    cbreak();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    
    printw("Some text");
 
    //init_pair(3, COLOR_CYAN, COLOR_BLACK);   
    Box* map[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[i][j] = new Box();
        }
    }


    map[3][2] = new Item1();

    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            map[i][j]->show(i, j);
        }
    }
    sleep(3);
    endwin();
}  