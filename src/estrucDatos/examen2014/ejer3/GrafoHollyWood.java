package estrucDatos.examen2014.ejer3;

import estrucDatos.examen2012.ejer3.GraphAL;

import java.util.*;

/**
 * Created by toburi on 03/01/2016.
 * Creado por toburi el 03/01/2016.
 */
public class GrafoHollyWood extends GraphAL<String> {

    public ArrayList<String> relacion(String actor1, String actor2){
        Queue<Integer> porExam = new LinkedList<>();
        boolean[] visitados = new boolean[numVertices];
        boolean hayCamino = false;

        int origen = buscarIndiceNodo(actor1);
        int fin = buscarIndiceNodo(actor2);

        porExam.add(origen);
        visitados[origen] = true;

        int[] camino = new int[numVertices];
        camino[origen] = -1; //no existe un camino a si mismo

        while (!porExam.isEmpty() && !hayCamino){
            int actual = porExam.poll();
            if (actual == fin) hayCamino = true;
            else{
                for (int nodo = 0; nodo < adjList[actual].size(); nodo++) {
                    if (!visitados[nodo]){
                        visitados[nodo]=true;
                        porExam.add(nodo);
                        camino[nodo]=actual;
                    }
                }
            }
        }
        ArrayList<String> aDevolver = new ArrayList<>();
        int temp = fin;
        while (temp != -1){
            aDevolver.add(vertices[temp]);
            temp = camino[temp];
        }
        Collections.reverse(aDevolver);
        return aDevolver;
    }

    private int buscarIndiceNodo(String actor1) {
        int i = 0;
        boolean enc = false;
        while (i <= DEFAULT_CAPACITY && !enc){
            if (vertices[i].equals(actor1)) enc = true;
            else i++;
        }
        return i;
    }
// post: el resultado es una lista que indica una relación entre actor1 y actor2 de longitud mínima
// El resultado será la lista vacía en caso de que los actores no estuvieran relacionados.
}
