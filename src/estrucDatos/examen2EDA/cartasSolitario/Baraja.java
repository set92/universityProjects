package estrucDatos.examen2EDA.cartasSolitario;

import java.util.Iterator;

/**
 * Created by toburi on 23/11/2015.
 * Creado por toburi el 23/11/2015.
 */
public class Baraja {
    private Carta[] cartas;

    //Constructor
    public Baraja(){
        Carta c;
        for (int i = 0; i < cartas.length; i++) {
            c = new Carta();
            c.valor = (int) (Math.random()*41);//TODO rango de 0 a 40?xk se coje de 0 a 41-1
            cartas[i]= new Carta();
        }
    }

    //devuelve un iterador para recorrer las cartas
    public Iterator<Carta> iterador(){
        Iterator<Carta> it = this.iterador();//TODO es asi?
        return it;
    }
}
