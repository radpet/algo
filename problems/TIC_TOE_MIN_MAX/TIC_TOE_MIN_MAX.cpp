#include<iostream>
#include<string>
#include<utility>
using namespace std;

char EMPTY_CELL = '#';
char PLAYER_1 = '1';
char PLAYER_2 = '2';

struct BoardState{
    string val;
    BoardState(string _val){
        val = _val;
    }

    string to_str(){
        return val;
    }

    bool operator== (BoardState &other){
        return val == other.val;
    }

} inplay("inplay"), draw("draw"), win_player_1("player_1"), win_player_2("player_2");

struct Board{
    
    char board[3][3];

    Board(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                board[i][j] = EMPTY_CELL;
            }
        }
    }

    void printBoard(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    char at(int row, int col){
        return board[row][col];
    }

    void clear(int row, int col){
        board[row][col] = EMPTY_CELL;
    }

    bool move(int row, int col,char player){
        if(board[row][col] != EMPTY_CELL){
            return false;
        }

        board[row][col] = player;

        return true;
    }
    /**
     * Returns BoardStatus::INPLAY if the board is not in a final state
     **/
    BoardState isWinningBoard(){
        for(int i=0;i<3;i++){
            if(board[i][0] != EMPTY_CELL && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
                return board[i][0] == PLAYER_1? win_player_1: win_player_2;
            }

            if(board[0][i] !=EMPTY_CELL && board[0][i] == board[1][i] && board[1][i] == board[2][i]){
                return board[0][i] == PLAYER_1? win_player_1: win_player_2;
            }
        }

       if(board[0][0]!= EMPTY_CELL && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
           return board[0][0] == PLAYER_1? win_player_1: win_player_2;
       }

       if(board[0][2]!= EMPTY_CELL && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
           return board[0][2] == PLAYER_1? win_player_1: win_player_2;
       }

       for(int i=0;i<3;i++){
           for(int j=0;j<3;j++){
               if(board[i][j] == EMPTY_CELL){
                   return inplay;
               }
           }
       }

       return draw;
    }

    bool hasNextMoves(){
        return isWinningBoard() == inplay;
    }

    string winner(){
        BoardState s= isWinningBoard();
        return s.to_str();
    }
};

struct MinMaxPlayer{
    Board board;
    bool playerATurn;
    MinMaxPlayer(Board _board, bool _playerATurn){
        board = _board;
        playerATurn = _playerATurn;
    }

    int minimax(Board b, int depth, bool maxPlayer, int alpha, int beta){
         if(!b.hasNextMoves()){
            //  cout<<"########"<<endl;
             BoardState s= b.isWinningBoard();

            //  cout<<"END GAME at depth:="<<depth<<endl;
            //  b.printBoard();

             if(s == win_player_1){
                //  cout<<"Win 1"<<endl;
                 return -10 + depth;
             }

             if(s == win_player_2){ // the ai is player 2, give it reward
                //  cout<<"WIN 2"<<endl;
                 return 10 - depth;
             }

             if(s == draw){
                //  cout<<"DRAW"<<endl;
                 return 0;
             }
         }

         if(maxPlayer){
            int best = -1000; 
                for (int i = 0; i<3; i++) { 
                    for (int j = 0; j<3; j++) { 
                        if (b.at(i,j)==EMPTY_CELL) { 
                            b.move(i,j, PLAYER_2); // player2 is the ai
                            best = max(best, minimax(b, depth+1, !maxPlayer, alpha, beta)); 
                            alpha = max(alpha, best); 

                            b.clear(i,j);

                            if (beta <= alpha) {
                                // cout<<"pruning"<<endl;;
                                break; 
                            }
                        } 
                    } 
                } 
                return best; 
         }else{
             int best = 1000; 
                for (int i = 0; i<3; i++) { 
                    for (int j = 0; j<3; j++) { 
                        if (b.at(i,j)==EMPTY_CELL) { 
                            b.move(i,j, PLAYER_1); 
        
                            best = min(best, minimax(b, depth+1, !maxPlayer, alpha, beta)); 
                            beta = min(beta, best);

                            b.clear(i,j);

                            if (beta <= alpha) {
                                // cout<<"pruning"<<endl;;
                                break; 
                            }
                        } 
                    } 
                } 
                return best;
         }
    }

    pair<int,int> nextMove(){
        int bestSoFar = -1000; 
        pair<int,int> move = make_pair(-1,-1);
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board.at(i,j) == EMPTY_CELL){
                    board.move(i,j, PLAYER_2); // the ai player is playerB

                    int val = minimax(board, 0, false, -1000, 1000); // first is max so should eval with min layer

                    board.clear(i,j);

                    if(val >= bestSoFar){
                        bestSoFar = val;
                        move = make_pair(i,j);
                    }
                }
            }
        }

        return move;
    }


};

struct Game{
    
    Board board;
    Game(){

    }

    void getNextMove(){
        bool moved = true;
        do{
            int r,c;
            cin>>r>>c;
            moved = board.move(r,c,PLAYER_1);
            if(!moved){
                cout<<"Bad move.Repeat!"<<endl;
            }
        }while(!moved);
    }

    void start(){
        bool playerATurn = true;
        while(board.hasNextMoves()){
            cout<<"Player "<<(playerATurn? "A":"B")<<" is on move"<<endl;
            board.printBoard();
            
            if(playerATurn){
                getNextMove();
            }else{
                cout<<"AI PLAYES"<<endl;
                MinMaxPlayer ai = MinMaxPlayer(board,PLAYER_2);
                pair<int, int> nextMove = ai.nextMove();
                board.move(nextMove.first, nextMove.second, PLAYER_2);
            }
            playerATurn = !playerATurn;
        }

        cout<<"And the winner is "<<board.winner()<<endl;
        board.printBoard();


    }
} g;

int main(){
    g.start();
}