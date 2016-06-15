package estrucDatos.examen2013.ejer3;

import estrucDatos.examen2012.ejer3.GraphAL;
import estrucDatos.examen2EDA.clinicaAlumnos.listas.SimpleLinkedList;

import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by toburi on 03/01/2016.
 * Creado por toburi el 03/01/2016.
 */
public class GrafoCallejero extends GraphAL<String> {

    public SimpleLinkedList<String> buscarCamino(String inicio, String fin, LinkedList<String> enObras){
        Queue<Integer> porExam = new LinkedList<>();
        boolean[] visitados = new boolean[numVertices];
        boolean hayCamino = false;

        int origen = buscarIndNodo(inicio);
        int ptoFinal = buscarIndNodo(fin);

        porExam.add(origen);
        visitados[origen]=true;

        int[] camino = new int[numVertices];
        camino[origen] = -1; //no existe un camino a si mismo

        while (!porExam.isEmpty() && !hayCamino){
            int actual = porExam.poll();
            if (actual == ptoFinal) hayCamino = true;
            else{
                for (int nodo = 0; nodo < adjList[actual].size(); nodo++) {
                    if (!visitados[nodo]){
                        visitados[nodo] = true;
                        if (!enObras.contains(nodo)){
                            porExam.add(nodo);
                            camino[nodo] = actual;
                        }
                    }
                }
            }
        }
        SimpleLinkedList<String> aDevolver = new SimpleLinkedList<>();
        int temp = ptoFinal;
        while (temp != -1){
            aDevolver.add(vertices[temp]);
            temp = camino[temp];
        }
        return aDevolver;
    }

    private int buscarIndNodo(String inicio) {
        int i = 0;
        boolean enc = false;
        while (i <= DEFAULT_CAPACITY && !enc){
            if (vertices[i].equals(inicio)) enc = true;
            else i++;
        }
        return i;
    }

}
