package estrucDatos.zzRepetidos.Herencia;

import estrucDatos.examen3EDA.herencia.GraphAL;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class GrafoPersonas extends GraphAL<Persona>{

    public static void main(String[] args) {
        GrafoPersonas gr1 = new GrafoPersonas();

        gr1.vertices = new Persona[12];
        gr1.vertices[0] = new Persona("amaia"); gr1.vertices[1] = new Persona("xabi"); gr1.vertices[2] = new Persona("jon");
        gr1.vertices[3] = new Persona("iker"); gr1.vertices[4] = new Persona("markel"); gr1.vertices[5] = new Persona("gorka");
        gr1.vertices[6] = new Persona("santi"); gr1.vertices[7] = new Persona("kepa"); gr1.vertices[8] = new Persona("bego");
        gr1.vertices[9] = new Persona("pedro");gr1.vertices[10] = new Persona("pilar");gr1.vertices[11] = new Persona("luis");

        gr1.adjList = new LinkedList[12];

        gr1.adjList[0] = new LinkedList<>(Arrays.asList(9,1,4));
        gr1.adjList[1] = new LinkedList<>(Arrays.asList(9,3,0,5,6));
        gr1.adjList[2] = new LinkedList<>(Arrays.asList(9));
        gr1.adjList[3] = new LinkedList<>(Arrays.asList(9,7,8,1));
        gr1.adjList[4] = new LinkedList<>(Arrays.asList(0,5));
        gr1.adjList[5] = new LinkedList<>(Arrays.asList(4,11));
        gr1.adjList[6] = new LinkedList<>(Arrays.asList(1,10));
        gr1.adjList[7] = new LinkedList<>(Arrays.asList(3));
        gr1.adjList[8] = new LinkedList<>(Arrays.asList(3));
        gr1.adjList[9] = new LinkedList<>(Arrays.asList(2,0,3,1));
        gr1.adjList[10] = new LinkedList<>(Arrays.asList(6));
        gr1.adjList[11] = new LinkedList<>(Arrays.asList(5));

        Persona pedro = new Persona("pedro");
        System.out.println(gr1.repartir(100000,2,pedro));
    }

    public int repartir(int cantidad, int n, Persona p){
        Queue<Integer> porExaminar = new LinkedList<>();
        int cantPersonas = 0;
        boolean[] examinados = new boolean[vertices.length];

        int muerto = index(p);
        int pos;

        porExaminar.add(muerto);
        examinados[muerto] = true;

        while (!porExaminar.isEmpty()){

            for (int i = 0; i < n; i++) {
                pos = porExaminar.poll();
                for (int j = 0; j < adjList[pos].size(); j++) {
                    if (!examinados[j]){
                        porExaminar.add(j);
                        examinados[j] = true;
                        cantPersonas++;
                    }
                }
                n--;
            }
        }
        return cantidad/cantPersonas;
    }
}
