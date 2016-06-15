package estrucDatos.examen3EDA.asignaturas;

import estrucDatos.examen2EDA.clinicaAlumnos.listas.SimpleLinkedList;

import java.util.HashMap;
import java.util.Iterator;

/**
 * Created by toburi on 21/12/2015.
 * Creado por toburi el 21/12/2015.
 */
public class ListaAlumnos extends HashMap<String, ArbolAsignaturas>{

    //Post: devolver es la lista de alumnos de la lista lst con la mejor nota
    public SimpleLinkedList<String> obtenerAlumnosConMejorNota(SimpleLinkedList<String> lst){
        SimpleLinkedList<String> res = new SimpleLinkedList<String>();
        int maxNota = 1;
        Iterator<String> it = lst.iterator();
        while (it.hasNext()){
            String act = it.next();
            int notaMax = this.get(act).mejorNota();
            if (notaMax > maxNota){
                res = new SimpleLinkedList<String>();
                res.add(act);
                maxNota = notaMax;
            }else if (notaMax == maxNota){
                res.add(act);
            }
        }
        return lst;
    }
}
