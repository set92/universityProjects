package ingSoftware.facade.salaMultimedia;

/**
 * Created by toburi on 25/02/2016.
 * Creado por toburi el 25/02/2016.
 */
public class SalaMultimedia {
    private static SalaMultimedia salaMultimedia;
    private Altavoces altavoces;
    private DVD dvd;
    private Ordenador ordenador;
    private Pantalla pantalla;
    private Proyector proyector;

    private SalaMultimedia() {
        altavoces = new Altavoces();
        dvd = new DVD();
        ordenador = new Ordenador();
        pantalla = new Pantalla();
        proyector = new Proyector();
    }

    public static SalaMultimedia getSalaMultimedia(){
        return new SalaMultimedia();
    }

    public void salaPeliculas (){
        proyector.setModo(1);
        dvd.encender();
        altavoces.setVolumen(100);
        dvd.insertar("La aventura de los corderos degollados");
    }

    public void salaCharlas (){
        proyector.setModo(0);
        ordenador.encenderOrdenador();
        proyector.encenderProyector();
    }

}
