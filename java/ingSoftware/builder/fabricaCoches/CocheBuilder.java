package ingSoftware.builder.fabricaCoches;

/**
 * Created by toburi on 24/02/2016.
 * Creado por toburi el 24/02/2016.
 */
public abstract class CocheBuilder {
    private Coche car;
    public Coche getCar() {return car;}
    public void construirCoche() {
        car = new Coche();
    }
    public abstract void elegirTipoRuedas();
    public abstract void elegirMotor();
    public abstract void elegirNumPuertas ();
    public abstract void elegirSiAireAcondicionado();
    public abstract void montar();

}
