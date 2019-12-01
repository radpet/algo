 #include<iostream>
 #include<vector>
 #include<string>
 #include<random>
 using namespace std;

int MAX_COST = 5000;

struct Random{
    default_random_engine generator;
    uniform_int_distribution<int> distribution;
    Random(int _min, int _max){
        distribution = uniform_int_distribution<int> (_min, _max);
    }

    int randInt(){
        return distribution(generator);
    }
    
};

Random binaryRandom(0,1);

struct Item{
    string name;
    int value;
    int cost;

    Item(string _name="unknown"): name(_name){

    }

    Item(string _name, int _value, int _cost):name(_name), value(_value), cost(_cost){

    }

    Item& operator=(const Item& other)
    {
        if(&other == this){
            return *this;
        }
            
        this->name = other.name;
        this->value = other.value;
        this->cost = other.cost;
        
        return *this;
    }

};

struct Solution{
    vector<Item>items;
    vector<bool> used;

    Solution(vector<Item> _items): items(_items){
        used = vector<bool>(_items.size(),0);
    }

    Solution& operator=(const Solution& other)
    {
        if(&other == this){
            return *this;
        }
            
        this->items = other.items;
        this->used = other.used;
        
        return *this;
    }

    Solution uniformMutate(Solution& other){
        Solution newSolution = Solution(items);

        for(int i=0;i<items.size();i++){
            int p = binaryRandom.randInt();
            newSolution.used[i] = p? used[i] : other.used[i];
        }

        return newSolution;
    }

    int fitness(){
        int res = 0;
        for(int i=0;i<items.size();i++){
            res += used[i]*items[i].value;
        }

        // hack the goodness here for simplicity
        if(cost() > MAX_COST){
            return 0;
        }
        return res;
    }

    int cost(){
        int res = 0;
        for(int i=0;i<items.size();i++){
            res += used[i]*items[i].cost;
        }
        return res;
    }

    void fillRandom(){
        for(int i=0;i<items.size();i++){
            used[i] = binaryRandom.randInt();
        }
    }

    Solution randomMutate(){
        // flip used[i] with chance 50%
        for(int i=0;i<items.size();i++){
            if(binaryRandom.randInt()){
                used[i] = !used[i];
            }
        }
        return *this;
    }

    void printSolution(){
        cout<<"Solution fitness="<<fitness()<<" cost="<<cost()<<endl;
        for(int i=0;i<items.size();i++){
            cout<<"item_name="<<items[i].name<<" used="<<used[i]<<endl;
        }
    }

};

 bool cmpSolution(Solution s1, Solution s2) 
    { 
      return s1.fitness() > s2.fitness(); 
    }

struct Solver{
    int iter;
    int populationSize;
    int selectionSize;

    vector<Item> items;
    vector<Solution> solutions;

    Solver(vector<Item>_items): items(_items), iter(1000), populationSize(100), selectionSize(20){

    }

    void initSolutions(){
        for(int i=0;i<populationSize;i++){
            Solution s = Solution(items);
            s.fillRandom();
            solutions.push_back(s);
        }
    }

   

    void orderByFitness(){
         sort(solutions.begin(), solutions.end(), cmpSolution); 
    }

    vector<Solution> select(){
        vector<Solution> topK;
        for(int i=0;i<selectionSize;i++){
            topK.push_back(solutions[i]);
        }
        return topK;
    }
    
    vector<Solution> crossover(vector<Solution>& selection){
        vector<Solution> newSolutions;
        for(int i=0;i<selection.size() - 1;i++){
            newSolutions.push_back(selection[i].uniformMutate(selection[i+1]));
        }

        newSolutions.push_back(selection[0].uniformMutate(selection[selection.size()-1]));

        return newSolutions;
    }

    vector<Solution> mutate(vector<Solution> &solutions){
        vector<Solution> newSolutions;
        for(int i=0;i<solutions.size();i++){
            newSolutions.push_back(solutions[i].randomMutate());
        }
        return newSolutions;
    }

    void replaceWith(vector<Solution> with){
        for(int i=0;i<selectionSize;i++){
            solutions[solutions.size() - with.size() + i] = with[i];
        }
    }

    Solution solve(){
        cout<<"Solving"<<endl;
        initSolutions();
  
        for(int step=0;step<iter;step++){
            orderByFitness();

            vector<Solution> selection = select();
            vector<Solution> children = crossover(selection);
            vector<Solution> mutated = mutate(children);
            replaceWith(mutated);

        }

        orderByFitness();
        return solutions[0];
    }
};

void solve(vector<Item> &items){
    Solver solver = Solver(items);
    Solution sol = solver.solve();
    sol.printSolution();
}

int max(int a, int b) { return (a > b)? a : b; } 

int knapSack(int W, vector<Item> &items) 
{ 
   int i, w; 
   int K[items.size()+1][W+1]; 
  
   for (i = 0; i <= items.size(); i++) 
   { 
       for (w = 0; w <= W; w++) 
       { 
           if (i==0 || w==0){
                K[i][w] = 0; 
           }    
           else if (items[i-1].cost <= w) {
               if(items[i-1].value + K[i-1][w-items[i-1].cost] > K[i-1][w]){
                   K[i][w] = items[i-1].value + K[i-1][w-items[i-1].cost];
               }else{
                   K[i][w] = K[i-1][w];
               }
           }   
           else{
                K[i][w] = K[i-1][w]; 
           }
                 
       } 
   } 
  
   return K[items.size()][W]; 
} 

int main(){
     int n;

     cin>>n;
     vector<Item> items;

    for(int i=0;i<n;i++){
        string _name;
        int _value;
        int _cost;

        cin>>_name>>_cost>>_value;
        
        items.push_back(Item(_name, _value, _cost));
    }

    // int c = 0;
    // for(int i=0;i<100;i++){
    //     c+=binaryRandom.randInt();
    // }
    // cout<<"1: "<<c<<" "<<"0: "<<(100-c)<<endl;
    cout<<"DP solution="<<knapSack(MAX_COST, items)<<endl;
    solve(items);

     return 0;
 }