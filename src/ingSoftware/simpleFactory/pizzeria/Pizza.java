package ingSoftware.simpleFactory.pizzeria;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public abstract class Pizza {
    public Pizza(){}
    public void preparar() {System.out.println("Pizza preparada.");}
    public void hornear() {System.out.println("Pizza en el horno.");}
    public void cortar() {System.out.println("Pizza cortada.");}
    public void meterEnCaja() {System.out.println("Pizza en la caja.");}
}
