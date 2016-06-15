package estrucDatos.examen3EDA.redSocial;

import estrucDatos.examen2EDA.clinicaAlumnos.listas.SimpleLinkedList;

/**
 * Created by toburi on 29/12/2015.
 * Creado por toburi el 29/12/2015.
 */
public interface iRedSocial {
    public SimpleLinkedList<Integer> amigos(Integer dni);

    public void anadir(Integer dniX, Integer dniY, Integer afinidad);

    public boolean estanRelacionados(Integer dniX, Integer dniY);

}
