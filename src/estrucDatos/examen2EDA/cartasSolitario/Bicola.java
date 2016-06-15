package estrucDatos.examen2EDA.cartasSolitario;

/**
 * Created by toburi on 23/11/2015.
 * Creado por toburi el 23/11/2015.
 */
public class Bicola<T> {
    public Bicola(){}//Constructora

    //Inicializa la cola (vacia)
    public boolean estaVacia() {
        return false;
    }
    //Indica si la Bicola está vacia
    public void insertarIzq(T elemento) {}
    //añade el elemento T por el extremo derecho de la cola
    public void insertarDer(T elemento) {}
    //añade el elemento T por el extremo derecho de la bicola
    public void eliminarIzq() {}
    // borra el elemento del extremo izquierdo de la bicola
    public void eliminarDer() {}
    // borra el elemento del extremo derecho de la bicola
    public T obtenerIzq() {
        return null;
    }
    // obtiene el elemento.del extremo izquierdo de la bicola
    public T obtenerDer() {
        return null;
    }
    // obtiene el elemento.del extremo derecho de la bicola

}
