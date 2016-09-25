package estrucDatos.examen3EDA.herencia;

import estrucDatos.zzRepetidos.Herencia.Persona;

import java.util.LinkedList;

/**
 * Created by toburi on 21/12/2015.
 * Creado por toburi el 21/12/2015.
 */
public class GraphAL<T> {
    protected final int DEFAULT_CAPACITY = 100;
    protected int numVertices;
    protected LinkedList<Integer>[] adjList;
    protected T[] vertices;

    public int index(T t) {
        //Devuelve el indice de vertices correspondiente a t
        for (int i = 0; i < vertices.length; i++) {
            if (((Persona)vertices[i]).nombre.equals(((Persona)t).nombre)) return i;
        }
        return -1;
    }
}
