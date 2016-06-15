package estrucDatos.examen3EDA.herencia;

import estrucDatos.examen2EDA.clinicaAlumnos.listas.Persona;

import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by toburi on 21/12/2015.
 * Creado por toburi el 21/12/2015.
 */
public class GrafoPersonas extends GraphAL<Persona>{

    public int repartir(int cantidad, int n, Persona p){
        Queue<Pareja> porExam = new LinkedList<Pareja>();
        boolean[] visitados = new boolean[numVertices];

        int indice = index(p);
        int nivelAct = 0;

        porExam.add(new Pareja(indice, 0));
        visitados[indice]= true;

        int numElem = 0;

        while (nivelAct < n && !porExam.isEmpty()){
            Pareja x = porExam.remove();
            nivelAct = x.nivel;
            if (x.nivel < n){
                for (int y : adjList[x.posPersona]){
                    if (!visitados[y]){
                        porExam.add(new Pareja(y,nivelAct+1));
                        visitados[y] = true;
                        numElem++;
                    }
                }
            }
        }
        return cantidad/numElem;
    }

    private class Pareja {
        int posPersona;
        Integer nivel;
        public Pareja(int p, int nivel) {
            this.posPersona = p;
            this.nivel = nivel;
        }
    }

}
