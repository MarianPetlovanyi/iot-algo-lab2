#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
struct Field{
    int x,y;
    int disFromStart;
    Field* prev;
    Field(){

    }
    Field(int ax, int ay, int adis, Field* aprev){
        x=ax;
        y=ay;
        disFromStart=adis;
        prev=aprev;
    }
};

bool checkCondition(int currX, int currY, int dim){
    if(currX>=1 && currX<=dim && currY>=1 && currY<=dim)
        return true;
    return false;
}
void setBool2dToZero(bool** arr, int dim){
    for(int i=1;i<=dim;i++){
        for(int j= 1; j<=dim; j++){
            arr[i][j]= false;
        }
    }
}
void tracing(Field* temp){
    Field* traceTemp=temp;
    std::vector<Field*> v;
    while (traceTemp->prev!= nullptr){
        v.push_back(traceTemp);
        traceTemp=traceTemp->prev;
    }
    std::cout<<"START ";
    for(int i=v.size()-1;i>=0;i--){

        if(i==0)
            std::cout<<"("<<v[i]->x<<", "<<v[i]->y<<") END.\n";
        else
            std::cout<<"("<<v[i]->x<<", "<<v[i]->y<<") -> ";
    }
}
int getMinDist(int startPos[], int finishPos[], int dim){
    int movesX[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int movesY[] = { -1, 1, 1, -1, 2, -2, 2, -2};
    bool** visited = new bool*[dim+1];
    for(int i=0; i<=dim;i++){
        visited[i]= new bool[dim+1];
    }
    setBool2dToZero(visited,dim);
    visited[startPos[0]][startPos[1]] = true;

    std::queue<Field*> q;
    Field* start = new Field(startPos[0], startPos[1], 0, nullptr);
    q.push(start);
    Field* temp;
    int x=0;
    int y=0;
    while(!q.empty()){
        temp=q.front();
        q.pop();
        if(temp->x == finishPos[0] && temp->y == finishPos[1]){
            tracing(temp);
            return temp->disFromStart;
        }
        for(int i=0; i<8;i++){
            x = temp->x + movesX[i];
            y = temp->y + movesY[i];

            if (checkCondition(x,y, dim) && !visited[x][y]){
                visited[x][y]=true;
                Field* toPush = new Field(x,y,temp->disFromStart+1, temp);
                q.push(toPush);
            }
        }
    }
    return 0;
}
int main() {
    int start[2];
    int finish[2];
    int dim;
    std::ifstream file("input.txt");
    std::string str, fullstr;
    while(!file.eof()){
        file>>str;
        fullstr = fullstr + " "+ str;
    }
    sscanf(fullstr.c_str(), "%*c%d%*c%d%*c%d%*c%d%*c%d",&dim, &start[0], &start[1],&finish[0], &finish[1]);
    std::cout<<getMinDist(start, finish, dim)<<"\n";
    return 0;
}
