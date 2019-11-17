// https://en.wikipedia.org/wiki/Iterative_deepening_A*
#include<iostream>
#include<vector>
#include<math.h>
#include<utility>
#include<string>
#include <queue> 
#define MAXINT 2147483647
using namespace std;

struct Board{
    vector<int> board;
    int size2d;
    int zeroIdx;
    string action;
    Board* finish;

    Board(vector<int> _board,Board* _finish = NULL, string _action="none"): board(_board), action(_action), finish(_finish){
        size2d = sqrt(board.size() + 1);
        for(int i=0;i<board.size();i++){
            if(board[i]==0){
                zeroIdx = i;
                break;
            }
        }
    }

    const int manhattanDistanceToFinish()const {
        if(finish != NULL){
            return manhattanDistance(*finish); 
        }
        return 0;
    }

    const int manhattanDistance(Board& other) const{
        int distance = 0;
        for(int i=0;i<board.size();i++){
            if(board[i] == 0){
                continue;
            }
            int otherIndex;
            for(int j=0;j<other.board.size();j++){
                if(board[i] == other.board[j]){
                    otherIndex = j;
                    break;
                }
            }

            distance += abs( (i/size2d) - (otherIndex/size2d) ) + abs( (i%size2d) - (otherIndex%size2d) );

        }
        return distance;
    }

    void print() const{
        cout<<"######"<<endl;
        for(int i=0;i<size2d;i++){
            for(int j=0;j<size2d;j++){
                cout<<board[i*size2d + j]<<" ";
            }
            cout<<endl;
        }
        cout<<"######"<<endl;
    }

    const vector<Board> nextStates() const{
        vector<pair<int, string> > nextZeroIdx;
        // zero up (num down)
        if ((zeroIdx - size2d >= 0) && (zeroIdx / size2d != 0)){
             nextZeroIdx.push_back(make_pair(zeroIdx-size2d, "down"));
        }

        // zero down (num up)
        if( (zeroIdx + size2d < board.size()) && (zeroIdx / size2d != size2d-1) ){
            nextZeroIdx.push_back(make_pair(zeroIdx+size2d, "up"));
        }

        // zero left (num right)
        if ( (zeroIdx - 1 >= 0) && (zeroIdx % size2d != 0)){
            nextZeroIdx.push_back(make_pair(zeroIdx -1, "right"));
        }
            
        // zero right (num left)
        if ( (zeroIdx < board.size()) && (zeroIdx % size2d != (size2d-1))){
            nextZeroIdx.push_back(make_pair(zeroIdx+1,"left"));
        }
        vector<Board> newStates;
        for(int i=0;i<nextZeroIdx.size();i++){
            vector<int> newBoard = board;
            //swap the state
            newBoard[zeroIdx] = newBoard[nextZeroIdx[i].first];
            newBoard[nextZeroIdx[i].first] = 0;
            newStates.push_back(Board(newBoard, finish, nextZeroIdx[i].second));
        }

        return newStates;
    }

    bool operator==(const Board& other){
        for(int i=0;i<board.size();i++){
            if(board[i] != other.board[i]){
                return false;
            }
        }
        return true;
    }

};

struct State{
    vector<Board> path;
    int graphDist;

    State(vector<Board> _path, int g):path(_path),graphDist(g){
    }

    State(Board b, int g):graphDist(g){
        path.push_back(b);
    }

    State add(Board b){
        State s = State(path, graphDist+1);
        s.path.push_back(b);
        return s;
    }

    // State pop(){
    //     State s = State(path, graphDist-1);
    //     s.path.pop_back();
    //     return s;
    // }
    
    // can be optimized significantly
    bool has(Board& b){
        for(int i=0;i<path.size();i++){
            if(path[i] == b){
                return true;
            }
        }
        return false;
    }

    const Board lastBoard () const{
        return path[path.size()-1];
    }

    bool isFinish(){
        return path[path.size()-1] == *(path[path.size()-1].finish);
    }


};


bool operator<(const State& p1, const State& p2) 
{  
        int a = p1.lastBoard().manhattanDistanceToFinish() + p1.graphDist;
        int b = p2.lastBoard().manhattanDistanceToFinish() + p2.graphDist;
        //min heap;
        return a>b; 
} 


void searchASTAR(State& start ,Board& finish){
    priority_queue<State> Q;

     Q.push(start);
 

     while(!Q.empty()){
        //  cout<<"getting new state()"<<endl;\
    

         State currentState = Q.top();
        //  cout<<"Qsize"<<Q.size()<<endl;

        //  cout<<"graph dist:"<< currentState.graphDist<<endl;
        //  cout<< currentState.lastBoard().manhattanDistanceToFinish() + currentState.graphDist<<endl;
        //  currentState.lastBoard().print();
         Q.pop();
         if(currentState.isFinish()){
             cout<<"FINISHED"<< endl;
             cout<<"min steps=: "<<currentState.graphDist<<endl;
             return;
         }

         vector<Board> nextStates = currentState.lastBoard().nextStates();
         
         for(int i=0;i<nextStates.size();i++){
            if(!currentState.has(nextStates[i])){
              Q.push(currentState.add(nextStates[i]));
            }
         }

     }
    
}

void searchBeam(State& start,Board& finish, int k){
     priority_queue<State> Q;

     Q.push(start);
 

     while(!Q.empty()){
        //  cout<<"getting new state()"<<endl;\
    

         State currentState = Q.top();
        //  cout<<"Qsize"<<Q.size()<<endl;

        //  cout<<"graph dist:"<< currentState.graphDist<<endl;
        //  cout<< currentState.lastBoard().manhattanDistanceToFinish() + currentState.graphDist<<endl;
        //  currentState.lastBoard().print();
         Q.pop();
         if(currentState.isFinish()){
             cout<<"FINISHED"<< endl;
             cout<<"min steps=: "<<currentState.graphDist<<endl;
             return;
         }

         vector<Board> nextStates = currentState.lastBoard().nextStates();
         
         for(int i=0;i<nextStates.size();i++){
            if(!currentState.has(nextStates[i])){
              Q.push(currentState.add(nextStates[i]));
            }
         }

         if(Q.size() > k){
             vector<State> topK;
            
            for(int i=0;i<k;i++){
                State st = Q.top();
                topK.push_back(st);
                Q.pop();
            }
            while(!Q.empty()){
                Q.pop();
            }

            for(int i=0;i<topK.size();i++){
                Q.push(topK[i]);
            }
         }

     }
}

void solve(Board& start, Board& finish){
    // cout<<"START:"<<endl;
    // start.print();
    
    // cout<<"Finish:"<<endl;
    // finish.print();

    
    State startState = State(start,0);
    // start.print();
    // finish.print();
   
   //searchASTAR(startState, finish);
   //searchBeam(startState, finish, 5);
   

}

int main(){

    int n;
    cin>>n;
    n +=1;

    int zeroPos;
    cin>>zeroPos;

    if(zeroPos == -1){
        zeroPos = n-1;
    }

    vector<int> startPos;
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        startPos.push_back(a);
    }



    vector<int> endPos;
    int c=1;
    for(int i=0;i<n;i++){
        if(i == zeroPos){
            endPos.push_back(0);
        }else{
            endPos.push_back(c++);
        }
    }

    Board finish = Board(endPos);
    Board start = Board(startPos, &finish);
    solve(start, finish);
    return 0;
}