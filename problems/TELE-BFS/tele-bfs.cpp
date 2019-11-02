#include<iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;

struct Cell{
    pair<int,int> coord;

    Cell(){
        coord = make_pair(-1,-1);
    }

    Cell(int r,int c){
        coord = make_pair(r,c);
    }
};

struct Board{
    vector<vector<int> > &board;
    vector<Cell> teleport;

    Board(vector<vector<int> >& _board):board(_board){
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board.size();j++){
                Cell c = Cell(i,j);
                if(isTeleport(c)){
                    teleport.push_back(c);
                }
            }
        }
    }

    unsigned int size(){
        return board.size();
    }

    bool isInside(Cell& cell){
        return cell.coord.first < board.size() 
            && cell.coord.first >=0 
            && cell.coord.second < board.size() 
            && cell.coord.second >=0;
    }

    bool isWall(Cell& cell){
        return isInside(cell) && board[cell.coord.first][cell.coord.second] == 0;
    }

    bool isTeleport(Cell& cell){
        return isInside(cell) && board[cell.coord.first][cell.coord.second] == 2;
    }

    Cell findOtherTeleport(Cell& cell){
        //cout<<"Teleport"<<teleport.size()<<endl;
        if(teleport.size() == 0 ){
            return cell;
        }
        if(teleport[0].coord == cell.coord){
            return teleport[1];
        }else{
            return teleport[0];
        }
    }

};



struct State{
    Cell coord;
    vector<Cell> path;
 
    State(Cell _c){
        coord = _c;
        path.push_back(coord);
    }

    State nextState(Cell c){
        State s = State(c);
        s.path = path;
        //cout<<"Pushing back"<<c.coord.first<<" "<<c.coord.second<<endl;
        s.path.push_back(c);
        return s;
    }
};

void solve(Board& board, Cell& start, Cell& finish){
    //cout<<"solve()::begin"<<endl;
    queue<State> Q;
    vector<vector<bool> > used;
    used.resize(board.size(), vector<bool>(board.size(),0));
    Q.push(State(start));
    while(!Q.empty()){
        State current = Q.front();
        Cell currentCell = current.coord;
        //cout<<"#########"<<endl;
        //cout<<"CURRENT CELL:"<<" "<<currentCell.coord.first<<" "<<currentCell.coord.second<<endl;
        Q.pop();
        // if(used[currentCell.coord.first][currentCell.coord.second]){
        //     cout<<"USED skipping"<<endl;
        //      for(int i=0;i<current.path.size();i++){
        //         cout<<current.path[i].coord.first<<" "<<current.path[i].coord.second<<endl;
        //     }
        //     continue;
        // }
        used[currentCell.coord.first][currentCell.coord.second]=true;
        
        if(currentCell.coord == finish.coord){
            cout<<"Total distance "<< current.path.size()-1<<endl;

            for(int i=0;i<current.path.size();i++){
                cout<<current.path[i].coord.first<<" "<<current.path[i].coord.second<<endl;
            }

            break;
        }
        
        //teleport
        if(board.isTeleport(currentCell)){
            //cout<<"TELEPORTING"<<endl;
            Cell otherTeleport = board.findOtherTeleport(currentCell);
            //cout<<"other Teleport: "<<otherTeleport.coord.first<<" "<<otherTeleport.coord.second<<endl;

            //check if we jumped from a teleport
            //if other teleport is not used then jump there
            if(!used[otherTeleport.coord.first][otherTeleport.coord.second]){
                Q.push(current.nextState(otherTeleport));
                continue;
            }            
        }
        
        //cout<<"LOOKINF AT NEIGH"<<endl;
        int neigh[4][2] = { {0,1}, {-1,0}, {0,-1}, {1,0}};

        for(int i=0;i<4;i++){
            int r = neigh[i][0];
            int c = neigh[i][1];
            // cout<<"Moving with: "<<r<<" "<<c<<endl;
            // cout<<"Moving to: "<<currentCell.coord.first+r<<" "<<currentCell.coord.second +c<<endl;
            // cout<<"Current cell: "<<currentCell.coord.first<<" "<<currentCell.coord.second<<endl;
            Cell newCell = Cell(currentCell.coord.first + r, currentCell.coord.second +c);
            if(board.isInside(newCell) && !board.isWall(newCell) && !used[newCell.coord.first][newCell.coord.second]){
                //cout<<"Pushing New Cell in the board:" << newCell.coord.first<<" "<<newCell.coord.second<<endl;
                Q.push(current.nextState(newCell));                
            }
        }
        
       
     
    }
    cout<<"solve()::end"<<endl;
}


int main(){


    int n;
    cin>>n;
    vector<vector<int> > board;
    board.resize(n, vector<int>(n));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }
    // cout<<"BOARD"<<endl;
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<board[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    int sr,sc;
    cin>>sr>>sc;
    Cell start = Cell(sr,sc);
    int er,ec;
    cin>>er>>ec;
    Cell finish = Cell(er, ec);
    Board b = Board(board);
    solve(b, start, finish);

    return 0;
}