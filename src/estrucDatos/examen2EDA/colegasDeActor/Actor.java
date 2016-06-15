package estrucDatos.examen2EDA.colegasDeActor;

import java.util.ArrayList;

/**
 * Created by toburi on 22/11/2015.
 * Creado por toburi el 22/11/2015.
 */
class Actor {
    String nombre;
    int edad;
    ArrayList<Pelicula> susPelis;
    NewList<Actor>[] susColegas;
    // Este atributo contiene, por cada actor, la lista de sus colegas
    // por cada rango de edad: En la posición 0 están los actores con
    // los que ha participado que tienen entre 0 y 9 años, en la
    // posición 1 entre 10 y 19, ...
    // El array tiene 10 elementos, es decir, se supone que no
    // hay actores con 100 o más años

    public ArrayList<Actor> felicitar() {
        ArrayList<Actor> al = new ArrayList<Actor>();
        for (int i = 0; i < 10; i++) {
            al.add(susColegas[i].get(0));
            susColegas[i].add(susColegas[i].poll());//hablar koldo, se puede meter mientras sacas el 1ro??
        }
        return al;
    }
}
