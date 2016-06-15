package estrucDatos.examen2EDA.colegasDeActor;

import java.util.ArrayList;

/**
 * Created by toburi on 22/11/2015.
 * Creado por toburi el 22/11/2015.
 */
public class ListaActores {
    ArrayList<Actor> lista;

    public void obtenerColegas() {
        // Precondición: el atributo susColegas de cada actor vale null
        // Postcondición: por cada actor, se han calculado los actores con los que
        // ha compartido el reparto de alguna película (susColegas),
        // clasificados por edades

        ArrayList<Actor> listAux;
        for (Actor a : lista) {
            a.susColegas = (NewList<Actor>[]) new NewList[10];//TODO ATENCION Como no deja new NewList<Actor>[10];
            //TODO Hacemos asi, parseandolo despues para que sea de ese tipo
            for (int i = 0; i < a.susColegas.length; i++) {
                a.susColegas[i]= new NewList<Actor>();
            }
            listAux = new ArrayList<Actor>();//actores relacionados con a
            //listAux no necesaria pero mas facil para meter elems y ver si estan o no
            for(Pelicula p : a.susPelis){
                for (int i = 0; i < a.susPelis.size(); i++) {
                    if (!a.equals(p.susActores.get(i))){//Si no es el mismo añadimos
                        if (!listAux.contains(p.susActores.get(i))){
                            listAux.add(p.susActores.get(i));
                            int e = p.susActores.get(i).edad / 10;
                            a.susColegas[e].add(p.susActores.get(i));
                        }
                    }
                }
            }
        }
    }

}
