package estrucDatos.examen2015.ejer4;

/**
 * Created by toburi on 18/05/2016.
 */
public class ArbolDeJuego {

    private Nodo root;

    public void premiar(int puntos, String elem){
        if (root.content.s.equals(elem)) root.content.s += puntos;
        else postOrden(root, puntos, elem);
    }

    private void postOrden(Nodo raiz, int puntos, String elem) {
        if (raiz != null){
            postOrden(raiz.izq, puntos, elem);
            postOrden(raiz.der, puntos, elem);
            if (raiz.content.s.equals(elem)){
                raiz.content.puntos += puntos;
                while (puntos >= 1 && raiz != null){
                    puntos -= 1;
                    raiz.padre.content.puntos += puntos;
                    raiz = raiz.padre;
                }
            }
        }
    }

}
