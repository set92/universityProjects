package ingSoftware.builder.pizzeria;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public abstract class PizzaBuilder {
    protected Pizza pizza;
    public Pizza getPizza() { return pizza; }
    public void construirPizza() {
        pizza = new Pizza();
    }
    public abstract void hacerMasa();
    public abstract void ponerSalsa();
    public abstract void ponerIngredientes ();
}
