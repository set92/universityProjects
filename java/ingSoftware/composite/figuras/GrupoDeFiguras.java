package ingSoftware.composite.figuras;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by toburi on 28/02/2016.
 * Creado por toburi el 28/02/2016.
 */
public class GrupoDeFiguras implements Figura {
    private List<Figura> figuras;
    public GrupoDeFiguras() {
        figuras = new ArrayList<Figura>();
    }
    public void anadir(Figura f) {
        figuras.add(f);
    }
    public void eliminar(Figura f) {
        figuras.remove(f);
    }
    public void pintar() {
        Figura unaFig;
        Iterator<Figura> it = figuras.iterator();
        while (it.hasNext()){
            unaFig = it.next();
            unaFig.pintar();
        }
    }
}
