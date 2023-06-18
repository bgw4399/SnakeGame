#include <ncurses.h>
#include "ScoreBoard.h"

#define HEIGHT 30
#define WIDTH 50

class Box{
    protected:
        WINDOW *local_win;
        int x, y;
    public:
        Box(int x, int y, int sizex=2, int sizey=1, int gabx=2, int gaby=1):x(x), y(y){
            local_win = newwin(sizey, sizex, y*gaby, x*gabx);
        }

        Box(Box* box):local_win(box->local_win){
            delete box;
        }

        virtual void encounter(Snake& s){
            ;
        }

        virtual void show(){
            wbkgd(local_win, COLOR_PAIR(1));
            wrefresh(local_win);	
        }

        void delete_window(){
            delwin(local_win);
        }

        virtual bool is_empty(){
            return true;
        }

        virtual bool is_convertable(){
            return true;
        }
};

class Item1:public Box{
    public:
        Item1(Box* box):Box(box){
            ;
        };
        void encounter(Snake& s){
            if(s.length<10) s.length++;
            s.pos_item_cnt++;
        }
        
        void show(){
            wbkgd(local_win, COLOR_PAIR(5));
            wrefresh(local_win);
        }

        bool is_empty(){
            return false;
        }

        bool is_convertable(){
            return true;
        }
};

class Item2:public Box{
    public:
        Item2(Box* box):Box(box){
            ;
        };
        void encounter(Snake& s){
            s.length--;
            s.neg_item_cnt++;
            if(s.length<3){
                ScoreBoard::lose();
            }
        }

        void show(){
            wbkgd(local_win, COLOR_PAIR(4));
            wrefresh(local_win);
        }

        bool is_empty(){
            return false;
        }

        bool is_convertable(){
            return true;
        }
};

class SnakeBody:public Box{
    public:
        SnakeBody(Box* box):Box(box){
            ;
        };
        void encounter(Snake& s){
            ScoreBoard::lose();
        }

        void show(){
            wbkgd(local_win, COLOR_PAIR(3));
            wrefresh(local_win);
        }

        bool is_empty(){
            return false;
        }

        bool is_convertable(){
            return true;
        }
};

class Wall:public Box{
    public:
        Wall(Box* box):Box(box){
            ;
        };
        void encounter(Snake& s){
            ScoreBoard::lose();
        }

        void show(){
            wbkgd(local_win, COLOR_PAIR(2));
            wrefresh(local_win);
        }

        bool is_empty(){
            return false;
        }

        bool is_convertable(){
            return false;
        }
};

class Portal:public Box{
    public:
        int opposite_x, opposite_y;
        Portal(Box* box, int ox, int oy):Box(box), opposite_x(ox), opposite_y(oy){
            ;
        };
        void encounter(Snake& s){
            s.portal_enc_cnt++;
            s.pos_x = opposite_x;
            s.pos_y = opposite_y;
            
            if(x==0) s.direction = 's';
            else if(x==HEIGHT-1) s.direction = 'w';
            else if(y==0) s.direction = 'd';
            else if(y==WIDTH-1) s.direction = 'a';
            else{
                // portal이 맵 중간에 있을 때 미구현
            }
        }

        void show(){
            wbkgd(local_win, COLOR_PAIR(6));
            wrefresh(local_win);
        }

        bool is_empty(){
            return false;
        }

        bool is_convertable(){
            return false;
        }
};