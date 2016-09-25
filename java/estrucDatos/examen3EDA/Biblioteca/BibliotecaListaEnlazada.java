package estrucDatos.examen3EDA.Biblioteca;

import java.util.LinkedList;

/**
 * Created by toburi on 29/12/2015.
 * Creado por toburi el 29/12/2015.
 */
public class BibliotecaListaEnlazada {
    LinkedList<Socio> listaSocios;
    LinkedList<Libro> listaLibros;

    public void transferirSocio (int carnetViejo, int carnetNuevo, String nombreNuevo){
        Socio socioOut = listaSocios.get(carnetViejo);
        Socio socioIn = new Socio();
        socioIn.nombre = nombreNuevo;
        socioIn.numero = carnetNuevo;
        socioIn.listaLibrosPrestados = socioOut.listaLibrosPrestados;
        for (Libro l : socioIn.listaLibrosPrestados) {
            l.quienLoTiene = socioIn;
        }
        listaSocios.add(socioIn);
        listaSocios.remove(socioOut);
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
