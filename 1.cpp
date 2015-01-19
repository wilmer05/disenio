#include<bits/stdc++.h>
using namespace std;

long long R,U,V;
long long N,M;
int casos;

vector<long long> coords_x;
vector<long long> coords_y;
vector<long long> padre;
vector<pair<double,pair<int,int> > > lados;

int find(int nodo){
  return padre[nodo]=(padre[nodo]==nodo?nodo:find(padre[nodo]));
}

void unir(int nodo_1, int nodo_2){
  int representante_1 = find(nodo_1);
  int representante_2 = find(nodo_2);  
  padre[representante_2]=representante_1;
}

double dist(int p1, int p2){
  return sqrt(pow(coords_x[p1]-coords_x[p2],2.0)+ \
              pow(coords_y[p1]-coords_y[p2],2.0));
}

int main(){
  cin >> casos;
  for(int c=0;c<casos;c++){
    cin >> N >> R >> M >> U >> V;
    coords_x.resize(N);
    coords_y.resize(N);
    padre.resize(N);    
    lados.clear();
    for(int i=0;i<N;i++){
      padre[i]=i;
      cin >> coords_x[i] >> coords_y[i];
    }
    
    for(int i=0;i<N;i++){
      for(int j=i+1;j<N;j++){
        double distancia =  dist(i,j);
        double costo;
        if( (long long)ceil(distancia) > R)
          costo = V*distancia;
        else
          costo = U*distancia;
        
        lados.push_back(make_pair(costo,make_pair(i,j)));
      }
    }
    double costo_regular =0.0 ,costo_especial = 0.0;
    
    M=N-M;
    
    sort(lados.begin(),lados.end());
    for(int i=0;i<lados.size() && M;i++){
      int nodo_1,nodo_2;
      int representante_1,representante_2;
      
      double precio = lados[i].first;
      nodo_1=lados[i].second.first;
      nodo_2=lados[i].second.second;
      
      representante_1 = find(nodo_1);
      representante_2 = find(nodo_2);
      
      
      if(representante_1!=representante_2){
        unir(representante_1,representante_2);
        M--;
        if((long long)ceil(dist(nodo_1,nodo_2))>R)
          costo_especial+=precio;
        else 
          costo_regular+=precio;
      }
      
    }
    printf("Caso #%d: %.3lf %.3lf\n",c+1,costo_regular,costo_especial);   
  }
  
  

  return 0;
}
