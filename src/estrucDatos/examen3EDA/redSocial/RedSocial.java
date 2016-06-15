package estrucDatos.examen3EDA.redSocial;

import estrucDatos.examen2EDA.clinicaAlumnos.listas.SimpleLinkedList;

import java.util.HashMap;

/**
 * Created by toburi on 29/12/2015.
 * Creado por toburi el 29/12/2015.
 */
public class RedSocial implements iRedSocial{
    private HashMap<String, Socio> miembros; //clave: DNI

    @Override
    public SimpleLinkedList<Integer> amigos(Integer dni) {
        return null;
    }

    @Override
    public void anadir(Integer dniX, Integer dniY, Integer afinidad) {

    }

    @Override
    public boolean estanRelacionados(Integer dniX, Integer dniY) {
        if (!miembros.containsKey(dniX) && !miembros.containsKey(dniY)) return false;
        else if(dniX == dniY) return true;//suponemos que somos amigos de nosotros mismos
        else if(amigos(dniX).contains(dniY))return true;
        else {
            for (int i = 0; i < amigos(dniX).size(); i++) {
                if (amigos(dniX).find(i).equals(dniY))return true;
                //falta hacer el metodo get de SimpleLinkedList, no sabemos que metodos tiene
            }
        }
        return false;
    }

    private class Socio {
        HashMap<String, Integer> tablaAmigos;//clave: DNI, datos: afinidad
        SimpleLinkedList<String> listaAmigos;//contiene los DNIs de tablaAmigos
    }
}
