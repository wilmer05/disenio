#include<bits/stdc++.h>
using namespace std;

int empleados,actividades;

vector<pair<int,int> > intervalos;
int main(){
  
  cin >> empleados;
  while(empleados--){
    cin >> actividades;
    intervalos.clear();
    for(int i=0;i<actividades;i++){
      int a,b;
      cin >> a >> b;
      intervalos.push_back(make_pair(b,a));
    }
    sort(intervalos.begin(),intervalos.end());
    
    int total = 0;
    int last = -1;
    
    for(int i=0;i<intervalos.size();i++){
      int begin,end;
      begin = intervalos[i].second;
      end = intervalos[i].first;
      if(begin>=last) total++,last=end;
    }
    
    printf("%d\n",total);
    
  }
  
  return 0;
}
