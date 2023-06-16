#include <iostream>
#include <ncurses.h>
#include<unistd.h>

class Snake{
    public:
        int length;
    Snake(int length=0):length(length){};
};

class Box{
    public:
        void encounter(Snake& s){}
        WINDOW* show(int x, int y){
            WINDOW *local_win;
            local_win = newwin(10, 10, y, x);
            box(local_win, 0 , 0);
            attron(COLOR_CYAN);
            wrefresh(local_win);	
            return local_win;
        }
};

class Item1:public Box{
    public:
        void encounter(Snake& s){
            s.length++;
        }
        
        WINDOW* show(int x, int y){
            WINDOW *local_win;
            local_win = newwin(10, 10, y, x);
            box(local_win, 0 , 0);
            attron(COLOR_PAIR(3));
            wrefresh(local_win);	
            return local_win;
        }
};

class Item2:public Box{
    public:
        void encounter(Snake& s){
            s.length--;
        }

        WINDOW* show(int x, int y){
            WINDOW *local_win;
            local_win = newwin(10, 10, y, x);
            box(local_win, 0 , 0);
            attron(COLOR_CYAN);
            wrefresh(local_win);	
            return local_win;
        }
};

class SnakeBody:public Box{
    public:
        void encounter(Snake& s){
            //ScoreBoard::lose();
        }

        WINDOW* show(int x, int y){
            WINDOW *local_win;
            local_win = newwin(10, 10, y, x);
            box(local_win, 0 , 0);
            attron(COLOR_CYAN);
            wrefresh(local_win);	
            return local_win;
        }
};

class Wall:public Box{
    public:
        void encounter(Snake& s){
            //ScoreBoard::lose();
        }

        WINDOW* show(int x, int y){
            WINDOW *local_win;
            local_win = newwin(10, 10, y, x);
            box(local_win, 0 , 0);
            attron(COLOR_CYAN);
            wrefresh(local_win);	
            return local_win;
        }
};


int main(){
    initscr();
    start_color();
    cbreak();
    init_pair(3, COLOR_CYAN, COLOR_BLACK);   
    Box map[5][5];
    WINDOW* win = map[0][0].show(3, 5);

    Item2 item;
    WINDOW* win2 = item.show(10, 10);
    sleep(3);
    delwin(win);
    delwin(win2);

    endwin();
}  