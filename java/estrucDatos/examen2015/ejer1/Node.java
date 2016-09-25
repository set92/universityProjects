package estrucDatos.examen2015.ejer1;

/**
 * Created by toburi on 18/05/2016.
 */
public class Node {
    Integer dato;
    Integer fila;
    Integer col;
    Node next;

    public Node(Integer fila, Integer col, Integer dato) {
        this.dato = dato;
        this.fila = fila;
        this.col = col;
    }
}
