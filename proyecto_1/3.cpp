#include<bits/stdc++.h>
using namespace std;

int empleados,actividades;

//vector de intervalos de actividad
vector<pair<int,int> > intervalos;
int main(){
  
  //leo la cantidad de empleados
  cin >> empleados;
  while(empleados--){
    cin >> actividades;
    
    intervalos.clear();
    
    //leo los intervalos de actividades
    for(int i=0;i<actividades;i++){
      int a,b;
      cin >> a >> b;
      intervalos.push_back(make_pair(b,a));
    }
    
    //ordeno los intervalos
    sort(intervalos.begin(),intervalos.end());
    
    int total = 0;
    int last = -1;
    
    //Realizo el algoritmo greedy para maximizar la cantidad de actividades
    //a realizar
    for(int i=0;i<intervalos.size();i++){
      int begin,end;
      begin = intervalos[i].second;
      end = intervalos[i].first;
      
      if(begin>=last) 
        total++,last=end;
    }
    
    printf("%d\n",total);
    
  }
  
  return 0;
}
