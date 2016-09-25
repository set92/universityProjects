package ingSoftware.composite.piezas;

/**
 * Created by toburi on 28/02/2016.
 * Creado por toburi el 28/02/2016.
 */
public class Cliente {
    public static void main(String[] args) {
        PiezaSencilla1 piezaSencilla1 = new PiezaSencilla1();
        PiezaSencilla2 piezaSencilla2 = new PiezaSencilla2();

        PiezaCompuesta piezaCompuesta = new PiezaCompuesta();
        piezaCompuesta.anadir(piezaSencilla1);
        piezaCompuesta.anadir(piezaSencilla2);

        PiezaCompuesta otraPiezaCompuesta = new PiezaCompuesta();
        PiezaSencilla2 otraPiezaSimple = new PiezaSencilla2();
        otraPiezaCompuesta.anadir(otraPiezaSimple);

        piezaCompuesta.anadir(otraPiezaCompuesta);
        piezaCompuesta.actualizarPrecio();
    }
}
