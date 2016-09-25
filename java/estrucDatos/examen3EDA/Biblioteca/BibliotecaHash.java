package estrucDatos.examen3EDA.Biblioteca;

import java.util.Hashtable;
import java.util.LinkedList;

/**
 * Created by toburi on 29/12/2015.
 * Creado por toburi el 29/12/2015.
 */
public class BibliotecaHash {
    Hashtable<Integer,Socio> socios;
    Hashtable<String, Libro> libros;

    public void transferirSocio (int carnetViejo, int carnetNuevo, String nombreNuevo){
        Socio socioOut = socios.get(carnetViejo);
        Socio socioIn = new Socio();
        socioIn.nombre = nombreNuevo;
        socioIn.numero = carnetNuevo;
        socioIn.listaLibrosPrestados = socioOut.listaLibrosPrestados;
        for (Libro l : socioIn.listaLibrosPrestados) {
            l.quienLoTiene = socioIn;
        }
        socios.put(carnetNuevo, socioIn);
        socios.remove(socioOut);
    }

    private class Socio {
        String nombre;
        int numero;
        LinkedList<Libro> listaLibrosPrestados;
    }

    private class Libro {
        String titulo;
        String autor;
        Socio quienLoTiene;
    }

}
