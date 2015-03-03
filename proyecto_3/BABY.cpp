#include<iostream>
#include<cstring>
#include<queue>
#include<utility>
using namespace std;

int N;
const int mn = 16;
int baby[mn];
int sol[mn];

int memo[1<<mn];
const int oo = 10000;

int abs(int x){
    if(x<0) return -x;
    return x;
}

int distancia(int x, int y, int x_2, int y_2){
    return abs(x-x_2)+abs(y-y_2);
}

int dp(int mask){
    int nx = N-__builtin_popcount(mask);
    if(nx==N)
        return 0;
    int &ref = memo[mask];
    if(ref!=-1) 
        return ref;
    ref = oo;
    for(int i=0;i<N;i++){
        if((1<<i)&mask){
            ref = min(ref,distancia(i,baby[i],nx,sol[nx])+dp(mask-(1<<i)));
        //    cout <<"hola " << endl;
        }
    }
    
    return ref;
}

int main(){

    while(cin >> N && N){
        for(int i=0;i<N;i++){
            cin >> baby[i];
        } 
        
        for(int i=0;i<N;i++){
            cin >> sol[i];
        }
        memset(memo,-1,sizeof(memo));
        cout << dp((1<<N)-1) << endl;
    }

    
    return 0;
}

