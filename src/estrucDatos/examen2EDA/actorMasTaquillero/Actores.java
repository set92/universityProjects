package estrucDatos.examen2EDA.actorMasTaquillero;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by toburi on 22/11/2015.
 * Creado por toburi el 22/11/2015.
 */
public class Actores {
    ArrayList<Actor> listaActores;
    public Actor elMasTaquillero(ArrayList<Ganancia> pelisConGanancias) {
        HashMap<Actor, Integer> hm = new HashMap<Actor, Integer>();
        listaActores = new ArrayList<Actor>();
        int dineroAcum=0;

        for (Ganancia g : pelisConGanancias) {
            for (Actor a : g.p.susActores) {
                if (!hm.containsKey(a))hm.put(a,g.dinero);
                else hm.put(a,hm.get(a)+g.dinero);
            }
        }

        HashMap.Entry<Actor, Integer> masRico = null;
        for (HashMap.Entry<Actor, Integer> entry : hm.entrySet()) {
            if (masRico == null || entry.getValue().compareTo(masRico.getValue()) > 0) {
                //el compareTo al hacer >0 estamos mirando que entry sea > que masRico
                masRico = entry;//y luego le damos ese valor a masRico
            }
        }

        return masRico.getKey();

        // Pre: la lista “pelisConGanancias” contiene el dinero recaudado por una serie de películas
        // Post: se devolverá el actor que ha recaudado más dinero (el dinero de un actor será la suma
        // de lo recaudado en las películas de ese actor en la lista dada)
        // Si hubiera más de un actor con la misma recaudación máxima, se devolverá el primero de ellos
    }
}
