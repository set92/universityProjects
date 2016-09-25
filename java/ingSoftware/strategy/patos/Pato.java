package ingSoftware.strategy.patos;

/**
 * Created by toburi on 03/03/2016.
 * Creado por toburi el 03/03/2016.
 */
public abstract class Pato {
    ComportamientoVolar cVolar;
    ComportamientoCuac cCuac;

    public void nadar(){
        System.out.println("Nadando");
    }

    public abstract void mostrarEnPantalla();

    public void volar(){
        cVolar.volar();
    }

    public void hacerCuac(){
        cCuac.cuac();
    }
}
