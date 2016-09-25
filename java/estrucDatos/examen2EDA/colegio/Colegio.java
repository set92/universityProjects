package estrucDatos.examen2EDA.colegio;

import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by toburi on 22/11/2015.
 */
public class Colegio {
    Queue<Queue<String>> alumnos;

    public void repartirRegalos(Queue<String> regalos){
        Queue<String> alAux;
        while (!regalos.isEmpty()){
            alAux = new LinkedList<String>();
            Queue<String> curso = alumnos.poll();//tengo el curso 1
            String regalo = regalos.poll();
            while (!curso.isEmpty()){
                String alumno = curso.poll();//1er alumno
                System.out.println(alumno+","+regalo);
                alAux.add(alumno);
            }
            alumnos.add(alAux);
        }
    }
    // post: los regalos se han repartido uno a uno, entregando
    // el primer regalo a los alumnos del primer curso de la cola
    // de alumnos, y así sucesivamente
    // Se han escrito en la pantalla las asignaciones de regalos en forma
    // de pares (alumno, regalo)

}
