//
//  maze.cpp
//  mazeGame
//
//  Created by 陈浩贤 on 2016/11/23.
//  Copyright © 2016年 陈浩贤. All rights reserved.
//

#include "maze.hpp"

Maze::Maze(){
    this->pos=(Position *)malloc(sizeof(Position));
    x=0;
    y=1;
    arrived[y][x]=1;
    getMap();
}

void Maze::getMap(){
    FILE *p=fopen(FILENAME, "r");
    if (p==NULL) {
        printf("打开迷宫失败\n");
    }else{
        int i=0;
        while (fgets(map[i], WIDTH+1, p)!=NULL) {
            i++;
        }
    }
    fclose(p);
    
    
}
void Maze::printWall()
{
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            printf("%c",map[i][j]);
        }
    }
    
}
void Maze::drawPath(){
    
}

int Maze::run(char direction){
    char temp=map[y][x];
    
    if (direction=='d') {
        if (ifHitTheWall(map[y][x+1])==1) {
            map[y][x]=map[y][x+1];
            map[y][x+1]=temp;
            x++;
            go();
            return 1;
        }
        
    }else if (direction=='w'||direction=='W'){
        if (ifHitTheWall(map[y-1][x])==1) {
            map[y][x]=map[y-1][x];
            map[y-1][x]=temp;
            y--;
            go();
            return 1;
        }
        
    }else if (direction=='a'||direction=='A'){
        if (ifHitTheWall(map[y][x-1])==1) {
            map[y][x]=map[y][x-1];
            map[y][x-1]=temp;
            x--;
            go();
            return 1;
        }
        
    }else if (direction=='s'||direction=='S'){
        if (ifHitTheWall(map[y+1][x])==1) {
            map[y][x]=map[y+1][x];
            map[y+1][x]=temp;
            y++;
            go();
            return 1;
        }
        
    }
    if (ifFinishTheMaze()==1) {
        finished=1;
    }
    return 0;
}

int Maze::ifHitTheWall(char nextStep){
    switch (nextStep) {
        case '#':{
            return 0;
            break;
        }
        case ' ':{
            return 1;
        }
        default:
            return 2;
            break;
    }
    
}

int Maze::ifFinishTheMaze(){
    if (x==WIDTH-3&&y==HEIGHT-2) {
        printf("恭喜你跑得比西方记者还快!\n");
        return 1;
    }else {
        return 0;
    };
}

void Maze::go(){
    system("clear");
    printWall();
}

void Maze::push(int x,int y){
    Position *pos=(Path *)malloc(sizeof(Path));
    pos->x=x;
    pos->y=y;
    flag++;
    array[flag]=pos;
    arrived[y][x]=1;
}

Position* Maze::pop(){
    if (flag>=0) {
        return array[--flag];
    }else{
        return NULL;
    }
    
}

void Maze::autoFindPath(){
    while (finished!=1) {
        if (isArrived(x-1, y)==0) {
            if (run('a')) {
                push(x, y);
                continue;
            }
        }
        if (isArrived(x, y+1)==0){
            if (run('s')) {
                push(x, y);
                continue;
            }
        }
        if (isArrived(x+1, y)==0){
            if (run('d')) {
                push(x, y);
                continue;
            }
        }
        if (isArrived(x, y-1)==0){
            if (run('w')) {
                push(x, y);
                continue;
            }
        }
        Position *pos=pop();
        if (pos) {
            char temp=map[y][x];
            map[y][x]=map[pos->y][pos->x];
            map[pos->y][pos->x]=temp;
            y=pos->y;
            x=pos->x;
            go();
        }else{
            return;
        }
        
    }
}

int Maze::isArrived(int x,int y){
    if (x>=0&&y>=0) {
        return arrived[y][x];
    }else{
        return -1;
    }
    
}

Position* Maze::getPos(){
    this->pos->x=x;
    this->pos->y=y;
    
    return this->pos;
}
