#include <ncurses.h>

class Snake{
    public:
        int length;
    Snake(int length=0):length(length){};
};

class Box{
    protected:
        WINDOW *local_win;
        
    public:
        Box(int x, int y, int sizex=2, int sizey=1, int gabx=2, int gaby=1){
            local_win = newwin(sizey, sizex, y*gaby, x*gabx);
        }
        Box(Box* box):local_win(box->local_win){
            delete box;
        }

        virtual void encounter(Snake& s){}
        virtual void show(){
            wbkgd(local_win, COLOR_PAIR(1));
            wrefresh(local_win);	
        }

        void delete_window(){
            delwin(local_win);
        }
};

class Item1:public Box{
    public:
        Item1(Box* box):Box(box){};
        void encounter(Snake& s){
            s.length++;
        }
        
        virtual void show(){
            wbkgd(local_win, COLOR_PAIR(5));
            wrefresh(local_win);
        }
};

class Item2:public Box{
    public:
        Item2(Box* box):Box(box){};
        void encounter(Snake& s){
            s.length--;
        }

        void show(){
            wbkgd(local_win, COLOR_PAIR(4));
            wrefresh(local_win);
        }
};

class SnakeBody:public Box{
    public:
        SnakeBody(Box* box):Box(box){};
        void encounter(Snake& s){
            //ScoreBoard::lose();
        }

        void show(){
            wbkgd(local_win, COLOR_PAIR(3));
            wrefresh(local_win);
        }
};

class Wall:public Box{
    public:
        Wall(Box* box):Box(box){};
        void encounter(Snake& s){
            //ScoreBoard::lose();
        }

        void show(){
            wbkgd(local_win, COLOR_PAIR(2));
            wrefresh(local_win);
        }
};