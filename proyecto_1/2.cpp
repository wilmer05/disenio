#include<bits/stdc++.h>
using namespace std;

//vector de padres para la estructura DSU de kruskal
vector<int> padre;

//Vector que cuenta cuantos nodos hay en cada arbol (por representante)
vector<int> cnt;

//vector que guarda los arcos del grafo
vector<pair<int,int> > arcos;

//vector que indica si un arco es eliminado por la entrada del problema
vector<bool> eliminado;

int casos;
int N,C;

//pilas utilizadas para guardar los queries y atenderlos en forma inversa
stack<int> s_1,s_2;

//funcion para buscar el representante del arbol de un nodo
int find(int nodo){
  return padre[nodo]=(padre[nodo]==nodo?nodo:find(padre[nodo]));
}

//Funcion utilizada para unir dos arboles, y aumentar el contador de nodos 
//de cada arbol
int unir(int nodo_1, int nodo_2){
  int representante_1 = find(nodo_1);
  int representante_2 = find(nodo_2);  
  padre[representante_2]=representante_1;
  
  int ret = cnt[representante_2]*cnt[representante_1];
  
  if(representante_2!=representante_1)
    cnt[representante_1]+=cnt[representante_2];
    
  return ret;
}


//funcion utilizada para inicializar cada vector del problema
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
    ///se lee la entrada
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
    
    //Leo cada uno de los queries de la entrada
    //si es R empilo 1 en s_1 y el valor del arco en s_2
    //sino empilo 0 en s_1 que indica que solo se quiere responder 
    //la cantidad de pares de nodos en arboles distintos
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
    
    //para cada uno de los arcos que no son eliminados por la entrada, 
    //los empilo y asi los saco de primero
    //para que se forme el arbol final de los queries y alli empiezo a hacer el
    //proceso de responder en orden inverso
    for(int i=0;i<N-1;i++){
      if(!eliminado[i]){
         s_1.push(1);
         s_2.push(i);
      }
    }
    
    //Inicialmente el numero de pares en cmponentes distintas es de 
    // N* (N-1) /2 ya que todos estan en arboles distintos
    int total = (N*(N-1))/2;
    int sum = 0;
    
    //vector que guardara las respuesta a los queries
    vector<int> respuesta;
    
    
    //Proceso los queries de la pila
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
    
    //respondo los queries en el orden que debe ser
    reverse(respuesta.begin(),respuesta.end());
    for(int i=0;i<respuesta.size();i++)
      printf("%d\n",respuesta[i]);

    if(casos>=1) 
      printf("\n");    
  }


  return 0;
}
