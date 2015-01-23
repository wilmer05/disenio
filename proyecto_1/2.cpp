#include<bits/stdc++.h>
using namespace std;

vector<int> padre;
vector<int> cnt;
vector<pair<int,int> > arcos;
vector<bool> eliminado;
int casos;
int N,C;
stack<int> s_1,s_2;

int find(int nodo){
  return padre[nodo]=(padre[nodo]==nodo?nodo:find(padre[nodo]));
}

int unir(int nodo_1, int nodo_2){
  int representante_1 = find(nodo_1);
  int representante_2 = find(nodo_2);  
  padre[representante_2]=representante_1;
  
  int ret = cnt[representante_2]*cnt[representante_1];
  
  if(representante_2!=representante_1)
    cnt[representante_1]+=cnt[representante_2];
    
  return ret;
}

void inicializar(){
  padre.resize(N);
  cnt.resize(N);
    
  eliminado.resize(N-1);
  arcos.resize(N-1);
}

int main(){
  scanf("%d",&casos);
  while(casos--){
    scanf("%d",&N);
    
    inicializar();
    
    for(int i=0;i<N-1;i++){
      int nod_1,nod_2;
      scanf("%d %d",&nod_1,&nod_2);
      nod_1--;
      nod_2--;
      arcos[i]=make_pair(nod_1,nod_2);
      eliminado[i]=false;
      
      padre[i]=i;
      cnt[i]=1;
    }
    padre[N-1]=N-1;
    cnt[N-1]=1;
    
    scanf("%d",&C);
    char tmp[4];
    int eliminar;
    for(int i=0;i<C;i++){
      scanf("%s",tmp);
      if(tmp[0]=='R'){
        scanf("%d",&eliminar);
        eliminar--;
        eliminado[eliminar]=true;
        s_1.push(1);
        s_2.push(eliminar);
      }
      else
        s_1.push(0);
    }
    
    for(int i=0;i<N-1;i++){
      if(!eliminado[i]){
         s_1.push(1);
         s_2.push(i);
      }
    }
    
    int total = (N*(N-1))/2;
    int sum = 0;
    
    vector<int> respuesta;
    
    while(!s_1.empty()){
      int accion = s_1.top();
      s_1.pop();
      if (!accion) 
        respuesta.push_back(total);
      else{
        int a_unir = s_2.top();
        s_2.pop();
        total-=unir(arcos[a_unir].first,arcos[a_unir].second);
      }
    }
    
    reverse(respuesta.begin(),respuesta.end());
    for(int i=0;i<respuesta.size();i++)
      printf("%d\n",respuesta[i]);

    if(casos>=1) 
      printf("\n");    
  }


  return 0;
}
