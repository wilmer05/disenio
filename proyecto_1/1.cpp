#include<bits/stdc++.h>
using namespace std;

//variables de entrada
long long R,U,V;
long long N,M;
int casos;

//vectores para guardar las coordenadas de los puntos
vector<long long> coords_x;
vector<long long> coords_y;

//vector que indica el representante de un arbol
//Haciendo uso de la estructura de DSU
vector<long long> padre;

//vector para guardar los arcos del grafo
vector<pair<double,pair<int,int> > > lados;


//funcion find para la estructura DSU
//si el nodo es su representante entonces lo retorno
//sino retorno su representante
//Lo que hace es devolver el representante del arbol de un nodo
int find(int nodo){
  return padre[nodo]=(padre[nodo]==nodo?nodo:find(padre[nodo]));
}


//Funcion utilizada para unir dos arboles
//Lo que hace es asignar al representante de un nodo, el representante del otro
void unir(int nodo_1, int nodo_2){
  int representante_1 = find(nodo_1);
  int representante_2 = find(nodo_2);  
  padre[representante_2]=representante_1;
}


//Funcion que calcula la distancia entre dos puntos dados
double dist(int p1, int p2){
  return sqrt(pow(coords_x[p1]-coords_x[p2],2.0)+ \
              pow(coords_y[p1]-coords_y[p2],2.0));
}

int main(){

  //leo el numero de casos
  cin >> casos;
  for(int c=0;c<casos;c++){
    cin >> N >> R >> M >> U >> V;
    
    //modifico el tamanio de los vectores de coordenadas y ded padre
    coords_x.resize(N);
    coords_y.resize(N);
    padre.resize(N);    
    lados.clear();
    
    //lectura de puntos
    for(int i=0;i<N;i++){
      padre[i]=i;
      cin >> coords_x[i] >> coords_y[i];
    }
    
    //para cada par de puntos calculo el lado que hay entre ellos asi como 
    //su precio
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
    
    //acumuladores que tendran las respuestas del problema
    double costo_regular =0.0 ,costo_especial = 0.0;
    
    //Modifico M para ver cuantos arcos faltan porunir
    M=N-M;
    
    //Ordeno los lados por costo
    sort(lados.begin(),lados.end());
    
    //Para cada arco, si los nodos pertenecen a arboles distintos entonces los
    //uno, y sino le hago SKIP
    for(int i=0;i<lados.size() && M;i++){
      int nodo_1,nodo_2;
      int representante_1,representante_2;
      
      double precio = lados[i].first;
      nodo_1=lados[i].second.first;
      nodo_2=lados[i].second.second;
      
      
      //Veo el representante de cada arbol de cada nodo
      representante_1 = find(nodo_1);
      representante_2 = find(nodo_2);
      
      //si no estan en el mismo arbol, se unen
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
