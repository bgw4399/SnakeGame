#include <iostream>
#include <Box.cpp>

using namespace std;

class Item :: public Box{
public:
    std::pair<int, int> generate_random_position(Snake& s) {
        // 게임 화면의 크기를 정의합니다.
        int game_width = 50;
        int game_height = 30;

        // C++11에서는 random_device와 uniform_int_distribution을 이용해 랜덤한 정수를 생성할 수 있습니다.
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> distr_width(0, game_width - 1);
        std::uniform_int_distribution<> distr_height(0, game_height - 1);

        std::pair<int, int> new_position;

        do {
            int x = distr_width(gen);
            int y = distr_height(gen);
            new_position = std::make_pair(x, y);
        } while(new_position == s.position); // 스네이크의 위치와 겹치지 않을 때까지 랜덤 위치를 생성합니다.

        // 이 함수는 랜덤 위치를 pair 형태로 반환합니다.
        return new_position;
    }

    class Item1 : public Item {
    public:
        void encounter(Snake& s) override {
            s.length++;
        }

        WINDOW* show(int y, int x) override {
            local_win = newwin(sizey, sizex, y*gaby, x*gabx);
            box(local_win, 0 , 0);
            wattron(local_win, COLOR_PAIR(1));
            wmove(local_win, 1,2);
            wprintw(local_win, "*");
            wrefresh(local_win);
            return local_win;
        }
    };

    class Item2 : public Item {
    public:
        void encounter(Snake& s) override {
            s.length--;
        }

        WINDOW* show(int y, int x) override {
            local_win = newwin(sizex, sizey, y*gaby, x*gabx);
            box(local_win, 0 , 0);
            wrefresh(local_win);
            return local_win;
        }
    };
