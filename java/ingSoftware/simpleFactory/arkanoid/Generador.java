package ingSoftware.simpleFactory.arkanoid;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public class Generador {
    public Generador() {
    }
    public Ladrillo generarLadrillos(int tipo){
        Ladrillo miLadrillo = LadrilloFactory.getMiLadrilloFactory().createLadrillo(tipo);
        miLadrillo.golpear();
        miLadrillo.rebotar();
        return miLadrillo;
    }

}
