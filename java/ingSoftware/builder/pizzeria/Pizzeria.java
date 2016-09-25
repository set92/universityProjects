package ingSoftware.builder.pizzeria;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public class Pizzeria {
    private PizzaBuilder pizzaBuilder;
    public void setPizzaBuilder(PizzaBuilder pb) { pizzaBuilder = pb; }
    public Pizza getPizza() {
        construirPizza();
        return pizzaBuilder.getPizza();
    }
    private void construirPizza() {
        pizzaBuilder.construirPizza();
        pizzaBuilder.hacerMasa();
        pizzaBuilder.ponerSalsa();
        pizzaBuilder.ponerIngredientes();
    }
}
