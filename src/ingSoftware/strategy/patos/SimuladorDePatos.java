package ingSoftware.strategy.patos;

/**
 * Created by toburi on 03/03/2016.
 * Creado por toburi el 03/03/2016.
 */
public class SimuladorDePatos {
    public static void main(String[] args) {
        PatoPicoAncho pruebaDePato = new PatoPicoAncho();
        pruebaDePato.mostrarEnPantalla();
        pruebaDePato.nadar();
        pruebaDePato.hacerCuac();
        pruebaDePato.volar();

        pruebaDePato.enfadar(new CuacAlto());
        pruebaDePato.hacerCuac();
        pruebaDePato.enfadar(new CuacNormal());
        pruebaDePato.hacerCuac();
    }
}
