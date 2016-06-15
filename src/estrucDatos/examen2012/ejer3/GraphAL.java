package estrucDatos.examen2012.ejer3;

import java.util.LinkedList;

/**
 * Created by toburi on 03/01/2016.
 * Creado por toburi el 03/01/2016.
 */
public class GraphAL<T> {
    protected final int DEFAULT_CAPACITY = 100;
    protected int numVertices; // number of vertices in the graph
    protected LinkedList<Integer>[] adjList; // adjacency list
    protected T[] vertices; // values of vertices
}
