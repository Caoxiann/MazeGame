//
//  maze.cpp
//  mazeGame
//
//  Created by 陈浩贤 on 2016/11/23.
//  Copyright © 2016年 陈浩贤. All rights reserved.
//

#include "maze.hpp"
MazeTree *startPoint;
MazeTree *endPoint;
Maze::Maze(){
    position=(Position *)malloc(sizeof(Position));
    x=0;
    y=1;
    arrived[y][x]=1;
    startPoint=(MazeTree *)malloc(sizeof(MazeTree));
    
    startPoint->x=0;
    startPoint->y=1;
    startPoint->root=startPoint;
    
    endPoint=(MazeTree *)malloc(sizeof(MazeTree));
    endPoint->x=WIDTH;
    endPoint->y=HEIGHT-1;
    endPoint->root=endPoint;
    
    
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
    Position *pos=(Position *)malloc(sizeof(Position));
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

Position* Maze::getPosition(){
    position->x=x;
    position->y=y;
    return position;
}

void Maze::autoMakeMaze(){
    clearMap();

    
    int treeFlag=0;
    trees[treeFlag]=startPoint;
    Position *prePos=new Position;
    while (blocked) {
        prePos->x=trees[treeFlag]->x;
        prePos->y=trees[treeFlag]->y;
        
        Position *nextPos=getRandomNextPos(prePos);
        MazeTree *nextTree=(MazeTree *)malloc(sizeof(MazeTree));
        
        nextTree->root=nextTree;
        searchTree(startPoint);
        
        if (ifNeedToBreak(nextTree)) {
            MazeTree *preTree=trees[treeFlag];
            
            map[(nextPos->y+prePos->y)/2][(nextPos->x+prePos->x)/2]=' ';
            map[nextPos->y][nextPos->x]=' ';
            treeFlag++;
            trees[treeFlag]=nextTree;
        }
        printWall();
        printf("\n");
        isBlock();
    }
}

void Maze::clearMap(){
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH-1; j++) {
            map[j][i]='#';
        }
        map[i][WIDTH-1]='\n';
    }
}

Position* Maze::getRandomNextPos(Position *currentPos){
    Position *nextPos=(Position *)malloc(sizeof(Position));
    int i=1;
    switch (i) {
        case 0://左
            nextPos->x=currentPos->x-2;
            nextPos->y=currentPos->y;
            break;
        case 1://下
            nextPos->x=currentPos->x;
            nextPos->y=currentPos->y+2;
            break;
        case 2://右
            nextPos->x=currentPos->x+2;
            nextPos->y=currentPos->y;
            break;
        case 3://上
            nextPos->x=currentPos->x;
            nextPos->y=currentPos->y-2;
            break;
        default:
            break;
    }
    return nextPos;
}

int Maze::ifNeedToBreak(MazeTree *nextTree){
    
    if (nextTree->x<=0||nextTree->x>=WIDTH||nextTree->y<=0||nextTree->y>=HEIGHT) {//下一个位置是否为墙或在墙外
        return 0;
    }
    if (map[nextTree->y][nextTree->x]==' ') {
        return 0;
    }
    if (isInTheTree(nextTree)) {
        return 0;
    }
    
    return 1;
    
}

void Maze::searchTree(MazeTree *tree){
    
    if (ifHitTheWall(map[tree->y][tree->x-1])==1) {
        if (!tree->lchild) {
            tree->lchild=(MazeTree *)malloc(sizeof(MazeTree));
            tree->lchild->root=tree;
        }
        searchTree(tree->lchild);
    }
    if (ifHitTheWall(map[tree->y+1][tree->x])==1) {
        if (!tree->dchild) {
            tree->dchild=(MazeTree *)malloc(sizeof(MazeTree));
            tree->dchild->root=tree;
        }
        searchTree(tree->dchild);
    }
    if (ifHitTheWall(map[tree->y][tree->x+1])==1) {
        if (!tree->rchild) {
            tree->rchild=(MazeTree *)malloc(sizeof(MazeTree));
            tree->rchild->root=tree;
        }
        searchTree(tree->rchild);
    }
    if (ifHitTheWall(map[tree->y-1][tree->x+1])==1) {
        if (!tree->uchild) {
            tree->uchild=(MazeTree *)malloc(sizeof(MazeTree));
            tree->uchild->root=tree;
        }
        searchTree(tree->uchild);
    }
}

int Maze::isInTheTree(MazeTree *subTree){
    if (subTree->root==subTree) {
        return 0;
    }else{
        return 1;
    }
}

void Maze::isBlock(){
    if (endPoint->root==endPoint) {
        blocked=1;
    }else{
        blocked=0;
    }
}

