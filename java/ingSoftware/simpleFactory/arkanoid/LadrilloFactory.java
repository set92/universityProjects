package ingSoftware.simpleFactory.arkanoid;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public class LadrilloFactory {
    private static LadrilloFactory miLadrilloFactory;
    private LadrilloFactory() {
    }
    public static LadrilloFactory getMiLadrilloFactory() {
        if (miLadrilloFactory == null) miLadrilloFactory = new LadrilloFactory();
        return miLadrilloFactory;
    }

    public Ladrillo createLadrillo (int tipo){
        Ladrillo miLadrillo = null;
        if (tipo == 1) { miLadrillo = new Ladrillo1Golpe();}
        else if (tipo == 2) { miLadrillo = new Ladrillo2Golpe();}
        else if (tipo == 3) { miLadrillo = new Ladrillo3Golpe();}
        return miLadrillo;
    }

}
