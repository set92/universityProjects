package estrucDatos.examen2EDA.cartasSolitario;

/**
 * Created by toburi on 23/11/2015.
 * Creado por toburi el 23/11/2015.
 */
public class Jugador {
    private String nombre;
    private Bicola<Carta> mano;

    public Jugador(String pNombre){
        this.nombre=pNombre;
        mano = new Bicola<Carta>();
    }

    public Bicola<Carta> getMano(){
        return this.mano;
    }
}
