package ingSoftware.composite.figuras;

/**
 * Created by toburi on 28/02/2016.
 * Creado por toburi el 28/02/2016.
 */
public class Cliente {
    public static void main(String[] args) {
        Circulo unC = new Circulo(2);
        Cuadrado unCuad = new Cuadrado(3);

        GrupoDeFiguras unGrupo = new GrupoDeFiguras();
        unGrupo.anadir(unC);
        unGrupo.anadir(unCuad);

        GrupoDeFiguras otroGrupo = new GrupoDeFiguras();
        Triangulo unTri = new Triangulo(3,6);
        otroGrupo.anadir(unTri);

        unGrupo.anadir(otroGrupo);
        unGrupo.pintar();
    }
}
