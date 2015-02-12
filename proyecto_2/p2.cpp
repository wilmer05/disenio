#include<bits/stdc++.h>

using namespace std;

/*
 * struct nodo
 * Tipo creado para representar un nodo de un grafo implementado con
 * listas de adyacencia
*/
struct nodo{

    int id;
    vector<int> arcos;
        
    nodo(){ arcos.clear();}
    
    nodo(int id_nodo):id(id_nodo){}
    
    nodo(int id_nodo, vector<int> arcos_nodo) : id(id_nodo), arcos(arcos_nodo){}
    
    bool operator<(const nodo &otro_nodo) const{
        return (arcos.size()<otro_nodo.arcos.size());
    }
   
};

//Una lista de nodos que representara nuestro grafo
vector<nodo> grafo;

//Posicion de un nodo en el grafo dado su id
vector<int> lugar;

//Linea leida del archivo de formato DIMACS
char comando[500];


//Matriz de adyacencia con distintos usos
vector<vector<int> > matriz_ady;

//Clique seleccionado del grafo
vector<int> clique;

//Cota superior e inferior que utilizara el algoritmo corregido de Brown
int q, w;

//Numero de nodos y arcos del grafo
int V, E;

//Color de un nodo dado su id
vector<int> color;

//Grado de saturacion de un nodo dado su id
vector<int> satur_degree;

//True si un nodo, dado su id, esta etiquetado
vector<bool> labeled;

//Rango de un nodo dado su id; el rango es el orden en el que se intentara
//colorear el grafo 
vector<int> rango;

/*
 * Funcion en la que se lee el grafo mediante listas de adyacencia
 * de un archivo en formato DIMACS para su futura coloracion.
*/
void leer_entrada(char *fname){

    char tmp1[20], tmp2[20];
    FILE *fp;
    char mystring [100];
    fp = fopen (fname, "r");
    if (fp == NULL) perror ("Error opening file");

    while(fgets(comando,500, fp)!=NULL){

        //c comentario
        //p edge nodos arcos  
        //e nodo1 nodo2
        if(strlen(comando)==0) continue;
        if(comando[0]=='c') continue;
        if(comando[0]=='p'){
            sscanf(comando,"%s %s %d %d",tmp1,tmp2,&V,&E);
            grafo.clear();
            grafo.resize(V);
            for(int i=0;i<V;i++) {
                grafo[i].id = i;
                matriz_ady.push_back(vector<int>(V,0));
            }
        }
        if(comando[0]=='e'){
            int nodo_1, nodo_2;
            sscanf(comando,"%s %d %d", tmp1, &nodo_1,&nodo_2);
            nodo_1--;
            nodo_2--;
            grafo[nodo_1].arcos.push_back(nodo_2);
            grafo[nodo_2].arcos.push_back(nodo_1);
            matriz_ady[nodo_1][nodo_2]=1;
            matriz_ady[nodo_2][nodo_1]=1;
        }
        
    }
}


/*
 * Busqueda de un clique en el grafo a colorear con los siguientes objetivos:
 *  - Tener un punto de inicio para la corrida del algoritmo de coloracion
 *  - Obtener una cota inferior para la cantidad de colores 
*/
void obtener_cota_inferior(){

    clique.clear();
    clique.push_back(grafo[V-1].id);
    for(int i=V-2;i>=0;i--){
        int cnt = 0;
        for(int j=0;j<clique.size();j++){
            cnt+=matriz_ady[clique[j]][grafo[i].id];
        }
        if(cnt==clique.size()){
            clique.push_back(grafo[i].id);
        }
            
    }
}


/*
 * Algoritmo que encuentra una cota maxima para la cantidad de colores que 
 * necesita un grafo para ser coloreado.
*/
int algoritmo_dsatur(){

    color.clear();
    satur_degree.clear();

    color.resize(V,0);
    satur_degree.resize(V,0);
    matriz_ady.clear();
    matriz_ady.resize(V);
    for(int i=0;i<V;i++) {
        matriz_ady[i] = vector<int>(V+1,0);

    }

    for(int i=0;i<V;i++){
        int best = -1;
        int nodo_best = -1;
        for(int j=V-1;j>=0;j--){
            
            if(!color[grafo[j].id]){
                
                if(best<satur_degree[grafo[j].id]){
                    best = satur_degree[grafo[j].id];
                    nodo_best = j;
                }
            }
        }
        
        if(best==-1) 
            break;
        for(int j=0;j<V;j++){
            if(!matriz_ady[grafo[nodo_best].id][j+1]){
                
                color[grafo[nodo_best].id]=j+1;
                break;
            }
        }
        int su_color = color[grafo[nodo_best].id];
        
        for(int j=0;j<grafo[nodo_best].arcos.size();j++){
        
            int ady = grafo[nodo_best].arcos[j];
            if(!matriz_ady[ady][su_color]){
                satur_degree[ady]++;
                matriz_ady[ady][su_color]=1;                
            }
            
        }
    }
    int maximo_color=-1;
    for(int i=0;i<V;i++){
        maximo_color = max(maximo_color,color[grafo[i].id]);

    }
    return maximo_color;

}


/*
 * Funcion auxiliar del algoritmo corregido de Brelaz que etiqueta nodos a 
 * los que se podria regresar durante un backtracking.
*/
void labeling(int val,int xk){

  vector<int> aux_label;
  aux_label.clear();
  aux_label.resize(V+1,0x3f3f3f3f);
  
  int va = lugar[xk];
  for(int i=0;i<grafo[va].arcos.size();i++){
    int tmp3 = grafo[va].arcos[i];
    
    int col = color[tmp3];
    if(col){
      aux_label[col] = min(aux_label[col],rango[tmp3]);
    }
  }
  for(int i=1;i<=V;i++){
    if(aux_label[i]<0x3f3f3f3f && aux_label[i]<val){
      labeled[clique[aux_label[i]]]=true;
    }
  }
  
}


/*
 * Algoritmo corregido de Brelaz que encuentra una coloracion optima para
 * un grafo.
*/
int algoritmo_corregido_de_Brown_modificado_por_Brelaz_implementado_por_nosotros(){
    
    //Color de cada nodo por id  
    color.clear();
    color.resize(V+1,0);
    
    //arreglo que indica si un nodo con cierto id esta etiquetado o no
    labeled.clear();
    labeled.resize(V+1,0);
        
    //Vector que realmente indica el rango de un nodo
    rango.clear();
    rango.resize(V+1,0);
            
    //para cada elemento del clique inicial, su color es su posicion
    //en el arrelgo de clique y la cantidad de nodos de ese color 1
    for(int i=0;i<clique.size();i++){
        color[clique[i]]=i+1;
        rango[clique[i]]=i;
        labeled[clique[i]]=true;
    }
    
    //para cada uno nodo de los nodos que no estan en el clique inicial
    for(int i=V-1;i>=0;i--){
        if(!color[grafo[i].id]){
    //los introduzco en el arreglo para recorrerlos posteriormente
            rango[grafo[i].id] = clique.size();
            clique.push_back(grafo[i].id);
        }
    }
    
    bool back = false;
    int k = w;
    vector<set<int> > U;
    U.resize(V);

    while(1){
    
        int xk = clique[k];

        if(!back){
        
            int s =0;
            for(int i=0;i<k;i++){
               s = max(s,color[clique[i]]);
            }

            int uk = s;
            int minimo = min(uk+1,q-1);
            U[xk].clear();
            for(int i=1;i<=minimo;i++){
                U[xk].insert(i);
            }
            int tmp = lugar[xk];
            for(int i=0;i<grafo[tmp].arcos.size();i++){
                if(rango[xk]> rango[grafo[tmp].arcos[i]]){
                  U[xk].erase(color[grafo[tmp].arcos[i]]);
                }  
            }
        }
        else{
            U[xk].erase(color[xk]);
            labeled[xk]=false;
        }
                
        if(U[xk].size()){
        
            color[xk]=*U[xk].begin();
            
            k++;            
            if(k<V){
                xk = clique[k];
            }
            
            if(k>=V){

                int s =0;
                for(int i=0;i<k;i++){
                   s = max(s,color[clique[i]]);
                }  

                q = s;
                if(q==w){
                    return q;
                }
                for(int i=0;i<V;i++){
                    if(color[clique[i]]==q){
                        k=i;
                        break;
                    }
                }
                xk = clique[k];
                for(int i =k;i<V;i++){
                    labeled[clique[i]]=false;
                }
                back = true;
            }
            else{ //k<V
                back = false;
            }
            
        } //U(xk) vacio
        else {
        
            back = true;
        }  
              
        if(back){
            
            labeling(k,xk);
            
            for(int i=k-1;i>=0;i--){
                if(labeled[clique[i]]){
                    k=i;
                    break;
                }
            }
            
            if(k<w){
                return q;
            }
        }
            
    }
   
}

/*
 * Funcion principal
*/

int main(int argc, char* argv[]){
     
    leer_entrada(argv[1]);
    sort(grafo.begin(),grafo.end());
    lugar.clear();
    lugar.resize(V);
    for(int i=0;i<V;i++){
        lugar[grafo[i].id]=i;
    }
    obtener_cota_inferior();
    w = clique.size();
    q =  algoritmo_dsatur();

    int q0 = q;
    cout << q0 << " " << flush;
    int answer = algoritmo_corregido_de_Brown_modificado_por_Brelaz_implementado_por_nosotros();
    cout << answer << endl;

   return 0;
}
