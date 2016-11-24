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
typedef class Position{
public:
    int x;
    int y;
}Position;

typedef struct MazeTree{
//    Position *position;
    MazeTree *lchild;
    MazeTree *rchild;
    MazeTree *uchild;
    MazeTree *dchild;
    MazeTree *root;
    int x;
    int y;
}MazeTree;

class Maze{
public:
    Maze();
    void autoFindPath();
    int run(char direction);
    char map[HEIGHT][WIDTH];
    Position *array[WIDTH*HEIGHT];
    Position *getPosition();
    void autoMakeMaze();
private:
    int arrived[HEIGHT][WIDTH];
    int flag=0;
    int x,y,finished;
    Position *position;
    
    void getMap();
    void printWall();
    
    int ifHitTheWall(char nextStep);
    int ifFinishTheMaze();
    void go();
    
    Position* pop();
    void push(int x,int y);
    int isArrived(int x,int y);
    void drawPath();
    void clearMap();
    
    int blocked=1;
    MazeTree *trees[HEIGHT*WIDTH];
    Position *getRandomNextPos(Position *currentPos);
    int ifNeedToBreak(MazeTree *nextTree);
    void searchTree(MazeTree *tree);
    int isInTheTree(MazeTree *subTree);
    void isBlock();
    
};



#endif /* maze_hpp */
