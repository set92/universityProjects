package ingSoftware.strategy.patos;

/**
 * Created by toburi on 03/03/2016.
 * Creado por toburi el 03/03/2016.
 */
public class PatoPicoAncho extends Pato {

    public PatoPicoAncho() {
        cVolar = new VolarNormal();
        cCuac = new CuacNormal();
    }

    public void enfadar(ComportamientoCuac pComportamientoCuac){
        cCuac = pComportamientoCuac;
    }

    @Override
    public void mostrarEnPantalla() {

    }

}
