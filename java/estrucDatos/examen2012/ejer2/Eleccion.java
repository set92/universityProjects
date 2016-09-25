package estrucDatos.examen2012.ejer2;

import estrucDatos.examen2012.ejer2.clasesExtra.*;
import estrucDatos.examen2EDA.clinicaAlumnos.listas.Node;
import estrucDatos.examen2EDA.clinicaAlumnos.listas.SimpleLinkedList;

/**
 * Created by toburi on 03/01/2016.
 * Creado por toburi el 03/01/2016.
 */
public class Eleccion {
    SimpleLinkedList<Partido> partidos; // todos los partidos
    SimpleLinkedList<Candidato> candidatos; // todos los candidatos
    SimpleLinkedList<Distrito> distritos; // todos los distritos
    SimpleLinkedList<Municipio> municipios; // todos los municipios
    SimpleLinkedList<Provincia> provincias; // todas las provincias

    public void anadirCandidaturas(SimpleLinkedList<Candidatura> lc){
        Node<Candidatura> temp = lc.first;

        while (!lc.isEmpty()){
            partidos.add(temp.data.partido);
            candidatos.add(temp.data.apelCandidato);
            distritos.add(temp.data.idDistrito);
            municipios.add(temp.data.municipio);
            provincias.add(temp.data.prov);
            temp = temp.next;
        }
    }
// Pre: las listas de partidos, candidatos, distritos,
// municipios y provincias se encuentran vacías
// Post: se han añadido las candidaturas dadas, actualizando
// todos los datos
}
