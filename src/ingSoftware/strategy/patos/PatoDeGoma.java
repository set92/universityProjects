package ingSoftware.strategy.patos;

/**
 * Created by toburi on 03/03/2016.
 * Creado por toburi el 03/03/2016.
 */
public class PatoDeGoma extends Pato {

    public PatoDeGoma(ComportamientoVolar cVolar, ComportamientoCuac cCuac) {
        cVolar = new VolarRapido();
        cCuac = new CuacAlto();
    }

    @Override
    public void mostrarEnPantalla() {

    }
}
