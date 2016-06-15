package ingSoftware.composite.piezas;

import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by toburi on 28/02/2016.
 * Creado por toburi el 28/02/2016.
 */
public class PiezaCompuesta implements Pieza {
    ArrayList<Pieza> listaPiezas;

    public PiezaCompuesta() {
        this.listaPiezas = new ArrayList<Pieza>();
    }

    public void anadir(Pieza pie) {
        listaPiezas.add(pie);
    }
    public void eliminar(Pieza pie) {
        listaPiezas.remove(pie);
    }

    @Override
    public void actualizarPrecio() {
        Pieza unPieza;
        Iterator<Pieza> it = listaPiezas.iterator();
        while (it.hasNext()){
            unPieza = it.next();
            unPieza.actualizarPrecio();
        }
    }
}
