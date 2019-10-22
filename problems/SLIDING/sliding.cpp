// https://en.wikipedia.org/wiki/Iterative_deepening_A*
#include<iostream>
#include<vector>
#include<math.h>
#include<utility>
#include<string>
#define MAXINT 2147483647
using namespace std;

struct Board{
    vector<int> board;
    int size2d;
    int zeroIdx;
    string action;

    Board(vector<int> _board, string _action="none"): board(_board), action(_action){
        size2d = sqrt(board.size() + 1);
        for(int i=0;i<board.size();i++){
            if(board[i]==0){
                zeroIdx = i;
                break;
            }
        }
    }

    int manhattanDistance(Board& other){
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

    void print(){
        cout<<"######"<<endl;
        for(int i=0;i<size2d;i++){
            for(int j=0;j<size2d;j++){
                cout<<board[i*size2d + j]<<" ";
            }
            cout<<endl;
        }
        cout<<"######"<<endl;
    }

    vector<Board> nextStates(){
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
            newStates.push_back(Board(newBoard, nextZeroIdx[i].second));
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

    bool operator!=(const Board& other){
        return !(*this == other);
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

    State pop(){
        State s = State(path, graphDist-1);
        s.path.pop_back();
        return s;
    }

    bool has(Board& b){
        for(int i=0;i<path.size();i++){
            if(path[i] == b){
                return true;
            }
        }
        return false;
    }

    Board lastBoard(){
        return path[path.size()-1];
    }
};

int search(State state, int bound, Board& finish){
    Board node = state.lastBoard();
    int totalDist = state.graphDist + node.manhattanDistance(finish);

    if(totalDist > bound){
        return totalDist;
    }

    if(node == finish){
        //cout<<"PATH_FOUND"<<endl;
        //cout<<"Cost:"<<state.graphDist<<endl;
        cout<<state.graphDist<<endl;
        //cout<<"Solution=:"<<endl;
        for(int i=1;i<state.path.size();i++){
            //state.path[i].print();
            cout<<state.path[i].action<<endl;
        }
        return 0;
    }

    int minBound = MAXINT;

    vector<Board> nextStates = node.nextStates();
    for(int i=0;i<nextStates.size();i++){
        if(!state.has(nextStates[i])){
            state = state.add(nextStates[i]);
            int res = search(state, bound, finish);
            
            if(res == 0){
                //found a path exit
                return res;
            }

            if(res < minBound){
                minBound = res;
            }
            state = state.pop();
        }
    }
    return minBound;
}

void solve(Board& start, Board& finish){
    // cout<<"START:"<<endl;
    // start.print();
    
    // cout<<"Finish:"<<endl;
    // finish.print();

    int bound = start.manhattanDistance(finish);

//    cout<<"Initial bound="<<bound<<endl;
//    vector<Board> succ = start.nextStates();
//    for(int i=0;i<succ.size();i++){
//        succ[i].print();
//    }

    bool found = false;
    do{
        int nextBound = search(State(start,0),bound, finish);
        
        //found a path
        if(nextBound == 0){
            found = true;
            break;
        }
        bound = nextBound;
    }while(bound != MAXINT);
    
    if(!found){
        cout<<"No Solution"<<endl;
    }
   

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

    Board start = Board(startPos);

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

    solve(start, finish);
    return 0;
}