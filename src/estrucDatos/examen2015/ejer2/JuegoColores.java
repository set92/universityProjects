package estrucDatos.examen2015.ejer2;

import java.util.ArrayList;
import java.util.Queue;
import java.util.Stack;

/**
 * Created by toburi on 18/05/2016.
 */
public class JuegoColores {
    Queue<Integer>[] jugadores;
    Stack<Integer> mesa;

    public int juego(int n, ArrayList<Tirada> tiradas){
        boolean terminado = false;
        while (!terminado){
            for (int k = 1; k <= jugadores.length; k++) {
                for (int i = 0; i <= tiradas.size(); i++) {
                    if (tiradas.get(i).dado1 == 6) {
                        terminado = true;

                    }else if (tiradas.get(i).dado1 % 2 == 0){
                        int ficha = jugadores[tiradas.get(i).dado2 - 1].poll();
                        mesa.push(ficha);
                    }else if (tiradas.get(i).dado2 % 2 != 0){
                        int ficha = mesa.pop();
                        jugadores[tiradas.get(i).dado2 - 1].add(ficha);
                    }
                }
            }
            if (n == 0){
                terminado = true;
                int negras = 0;
                for (int i = 0; i < jugadores.length; i++) {
                    for (int j = 0; j < jugadores[i].size(); j++) {

                    }
                }
            }
        }


        return 0;
    }
}
