/*
package estrucDatos.examen3EDA;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

*/
/**
 * Created by toburi on 11/12/2015.
 * Creado por toburi el 11/12/2015.
 *//*

public class GrafoClase {
    int numVertices = 0;

    public void recorridoEnAnchura(){
        //numVertices sale de la clase Grafo que esta en las diapositivas la clase, es un atributo
        boolean[] visitados = new boolean[this.numVertices];
        for (int i = 0; i < this.numVertices; i++) {
            visitados[i] = false;
        }
        for (int i = 0; i < this.numVertices; i++) {
            if (!visitados[i]) marcarAncho(i,visitados);
        }
    }

    //Coste Algoritmo -> 2n+n(2+m2) --> n*m
    // n = num nodos del grafo // m = grado medio por nodo
    public boolean estanConectados(T a, T b){
        //numVertices sale de la clase Grafo que esta en las diapositivas la clase, es un atributo
        boolean[] visitados = new boolean[this.numVertices];
        Queue<Integer> porVisitar = new LinkedList<Integer>();
        boolean enc = false;

        for (int i = 0; i < this.numVertices; i++) {
            visitados[i] = false;
        }
        int origen = buscarIndNodo(a);//Coste ---> n
        int destino = buscarIndNodo(b);//Coste ---> n

        porVisitar.add(origen);
        visitados[origen]=true;
        while (!porVisitar.isEmpty() && !enc){//Coste ---> n
            int act = porVisitar.remove();
            if (destino == act) enc = true;
            else{
                //Coste del for---> m
                for (int nodo = 0; nodo < this.adjList[act]; nodo++) {//adjlist esta en clase Graph de apuntes
                        if (!visitados[nodo]){
                            visitados[nodo]=true;//Igual que el proyecto, se pone aqui para que tarde poco
                            porVisitar.add(nodo);
                        }
                }
            }
        }
        return enc;
    }

    public ArrayList<T> devolverCaminoKoldo(T a, T b){
        //numVertices sale de la clase Grafo que esta en las diapositivas la clase, es un atributo
        boolean[] visitados = new boolean[this.numVertices];
        Queue<Integer> porVisitar = new LinkedList<Integer>();
        boolean enc = false;

        for (int i = 0; i < this.numVertices; i++) {
            visitados[i] = false;
        }
        int origen = buscarIndNodo(a);//Coste ---> n
        int destino = buscarIndNodo(b);//Coste ---> n

        porVisitar.add(origen);
        visitados[origen]=true;

        int[] camino = new int[numVertices];
        camino[origen] = -1;

        while (!porVisitar.isEmpty() && !enc){//Coste ---> n
            int act = porVisitar.remove();
            if (destino == act) enc = true;
            else{
                //Coste del for---> m
                for (int nodo = 0; nodo < this.adjList[act]; nodo++) {//adjlist esta en clase Graph de apuntes
                    if (!visitados[nodo]){
                        visitados[nodo]=true;//Igual que el proyecto, se pone aqui para que tarde poco
                        porVisitar.add(nodo);
                        camino[nodo]=act;
                    }
                }
            }
        }
        ArrayList<T> res = new ArrayList<T>();
        int act2 = destino;
        while (act2 != -1){
            res.add(vertices[act2]);//vertices es un array de los elementos
            act2 = camino[act2];
        }
        return res;
    }

    public boolean connectedBis(T a,T b){
        int origen = buscarIndNodo(a);
        int destino = buscarIndNodo(b);
        //No hace falta lista de porVisitar ya que lo hacemos por profundidad
        boolean[] visitados = new boolean[numVertices];
        return connectedRecursivo(pos1,pos2,visitados);
    }

    public boolean connectedRecursivo(int x,int y, boolean[] visitados){
        boolean enc = false;
        if (x==y) return true;
        else{
            visitados[x]=true;
            for (int dest : adjList[x]) {
                if (!visitados[dest]){
                    enc = connectedRecursivo(dest,y,visitados);
                    if (enc) return true;
                }
            }
        }
        return false;
    }

    private int buscarIndNodo(T a) {
        return 0;
    }

    private void marcarAncho(int i, boolean[] visitados) {
        Queue<Integer> porVisitar = new LinkedList<Integer>();
        porVisitar.add(i);
        visitados[i]=true;
        while (!porVisitar.isEmpty()){
            int j = porVisitar.remove();
            actualizar(visitados,porVisitar,j);
        }
    }

    private void actualizar(boolean[] visitados, Queue<Integer> porVisitar, int j) {
        for (int nodo = 0; nodo < this.adjList[j]; nodo++) {//adjlist esta en clase Graph de apuntes
            if (!visitados[nodo]){
                visitados[nodo]=true;
                porVisitar.add(nodo);
            }
        }
    }
}
*/
