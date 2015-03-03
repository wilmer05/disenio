#include<iostream>
#include<cstring>
#include<queue>
#include<utility>
using namespace std;
const int mn = 210;
int xs[mn];
int N;
int memo[mn][mn][mn];
int dp(int last_as, int last_des, int voy){
    if(voy>=N+2) 
        return 0;
    int &ref = memo[last_as][last_des][voy];
    if(ref!=-1) 
        return ref;
    ref = 1+dp(last_as,last_des,voy+1);
    if(xs[voy]>xs[last_as]){
        ref =min(ref,dp(voy,last_des,voy+1));
    }
    if(xs[voy]<xs[last_des]){
        ref =min(ref,dp(last_as,voy,voy+1));
    }
    
    return ref;
}

    
int main(){
    while(cin >> N && N!=-1){
        for(int i=0;i<N;i++){
            cin >> xs[i+2];
        }
        xs[0]=-1;
        xs[1]=10000000;
        memset(memo,-1,sizeof memo);
        cout << dp(0,1,2) << endl;
    }

    return 0;
}
    
