#include<bits/stdc++.h>
using namespace std;

vector<int> padre;
vector<int> cnt;
vector<pair<int,int> > arcos;
vector<vector<int> > next;
vector<bool> eliminado;
vector<bool> visitado;
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
  
  next.clear();
  next.resize(N);
    
  visitado.clear();
  visitado.resize(N,false);
  eliminado.clear();
  arcos.clear();
}

void dfs(int nodo, int parent){
  padre[nodo]=padre[parent];
  cnt[padre[nodo]]++;
  visitado[nodo]=1;
  for(int i=0;i<next[nodo].size();i++){
    if(parent!=next[nodo][i])
      dfs(next[nodo][i],nodo);
  }
  
}

int main(){
  cin >> casos;
  while(casos--){
    cin >> N;
    
    inicializar();
    
    for(int i=0;i<N-1;i++){
      int nod_1,nod_2;
      cin >> nod_1 >> nod_2;
      nod_1--;
      nod_2--;
      arcos.push_back(make_pair(nod_1,nod_2));
      eliminado.push_back(false);
    }
    
    cin >> C;
    char tmp[4];
    int eliminar;
    for(int i=0;i<C;i++){
      cin >> tmp;
      if(tmp[0]=='R'){
        cin >> eliminar;
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
        next[arcos[i].first].push_back(arcos[i].second);
        next[arcos[i].second].push_back(arcos[i].first);        
      }
    }
    
    int total = 0;
    int sum = 0;
    for(int i=0;i<N;i++){
      if(!visitado[i]){
        cnt[i]=0;
        padre[i]=i;
        dfs(i,i);
        //cout << "i= " << i << " " << cnt[i] << endl;
        total+=sum*cnt[i];
        sum+=cnt[i];
      }
    }
    //cout << "sum= " << sum << endl;
    //cout << "total= " << total << endl;
    
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
