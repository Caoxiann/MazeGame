//
//  maze.hpp
//  mazeGame
//
//  Created by 陈浩贤 on 2016/11/23.
//  Copyright © 2016年 陈浩贤. All rights reserved.
//

#ifndef maze_hpp
#define maze_hpp
#define WIDTH  19
#define HEIGHT 9
#define FILENAME "/Users/caoxiann/Desktop/c/mazeGame/mazeGame/mazeGame/maze.txt"

#include <stdio.h>
#include <stdlib.h>
typedef struct Position{
    int x;
    int y;
}Path;

class Maze{
public:
    Maze();
    void autoFindPath();
    Position *getPos();
    int run(char direction);
    char map[HEIGHT][WIDTH];
    Position *array[WIDTH*HEIGHT];
private:
    Position *pos;
    
    int arrived[HEIGHT][WIDTH];
    int flag=0;
    
    int x,y,finished;
    
    void getMap();
    void printWall();
    
    int ifHitTheWall(char nextStep);
    int ifFinishTheMaze();
    void go();
    Position* pop();
    void push(int x,int y);
    int isArrived(int x,int y);
    void drawPath();

};

#endif /* maze_hpp */
