#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;

const int mn = 210;
int memo[2][mn];
char tab[mn][mn];
int T;
int n,m;
const int oo = 0x3f3f3f3f;
int main(){
    cin >> T;
    while(T--){
        cin >> n >> m;
        for(int i=0;i<n;i++){
            cin >> tab[i];
        }
        int best;
        best = memo[0][0] = (tab[0][0]=='T');
        for(int i=1;i<m;i++){
            if(tab[0][i]=='#'){
                for(int j=i;j<m;j++){
                    memo[0][j]=-oo;             
                }
                break;
            }
            memo[0][i]=memo[0][i-1]+(tab[0][i]=='T');
            best = max(best,memo[0][i]);
        }
        for(int i=1;i<n;i++){
            int usar=1;
            int paso=1;
            int comienzo = 0;
            int last = m;
            if(i%2==1){
                paso=-1;
                comienzo=m-1;
                last = -1;
                usar=0;
            }
            if(tab[i][comienzo]=='#'){
                memo[1-usar][comienzo]=-oo;
            }
            else{
                memo[1-usar][comienzo]=memo[usar][comienzo]+(tab[i][comienzo]=='T');
            }
            best = max(best,memo[1-usar][comienzo]);
            for(int j=comienzo+paso;j!=last;j+=paso){
                memo[1-usar][j] = max(memo[usar][j],memo[1-usar][j-paso])+(tab[i][j]=='T');
                if(tab[i][j]=='#')
                    memo[1-usar][j]=-oo;
                best = max(best,memo[1-usar][j]);
            }
            
        }
        if(tab[0][0]=='#')
            best = 0;
        cout << best << endl;       
    }   
    return 0;
}
