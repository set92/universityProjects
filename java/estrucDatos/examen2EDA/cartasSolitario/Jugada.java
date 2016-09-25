package estrucDatos.examen2EDA.cartasSolitario;

/**
 * Created by toburi on 23/11/2015.
 * Creado por toburi el 23/11/2015.
 */
public class Jugada {
    private Bicola<Jugador> jugadores;
    private Bicola<Carta> jugada;

    public void partida(){
        boolean terminar = false;
        Baraja b = new Baraja();
        jugadores = new Bicola<Jugador>();
        jugada = new Bicola<Carta>();
        Jugador j = jugadores.obtenerIzq();

        while (!j.getMano().estaVacia()) {
            Carta c = j.getMano().obtenerIzq();
            if (c.valor == 6 || (c.palo.equals(jugada.obtenerIzq().palo) && c.valor == jugada.obtenerIzq().valor + 1)) {
                jugada.insertarIzq(c);
                j.getMano().eliminarIzq();
            }else {
                j.getMano().insertarDer(c);
                j.getMano().eliminarIzq();
            }
            j = jugadores.obtenerIzq();

        }
    }
}
