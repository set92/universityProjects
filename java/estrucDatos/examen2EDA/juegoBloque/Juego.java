package estrucDatos.examen2EDA.juegoBloque;

import java.util.Stack;

/**
 * Created by toburi on 23/11/2015.
 * Creado por toburi el 23/11/2015.
 */
public class Juego {
    Stack<Bloque>[] tablero; // array de pilas
    public static int NUMCOLUMNAS = 7;
    public Juego() { // constructora
        tablero = (Stack<Bloque>[]) new Stack[NUMCOLUMNAS];
        for (int i = 0; i <= NUMCOLUMNAS - 1; i++) {
            tablero[i] = new Stack<Bloque>();
        }
        // código para “llenar” aleatoriamente las pilas de “bloques”
    }

    public int jugar() {
        boolean fin = false;
        int puntos = 0;
        int pos = NUMCOLUMNAS/2;
        boolean out = false;

        while (!fin && !out){
            if ( (pos < 0) || (pos >= NUMCOLUMNAS))out = true;
            else if(tablero[pos].isEmpty())fin = true;
            else {
                Bloque b = tablero[pos].pop();
                puntos += b.puntos;
                if (b.direccion.equals('d')) pos += b.salto;
                else pos -= b.salto;
            }
        }
        if (fin) return puntos;
        else return -1;
    }
}

























