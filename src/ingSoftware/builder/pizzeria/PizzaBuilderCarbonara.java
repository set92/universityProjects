package ingSoftware.builder.pizzeria;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
/** ConcreteBuilder */
public class PizzaBuilderCarbonara extends PizzaBuilder {
    public void hacerMasa() { pizza.setMasa("fina"); }
    public void ponerSalsa() { pizza.setSalsa("blanca"); }
    public void ponerIngredientes() { pizza.setIngredientes("jamon"+"champíñones"); }
}
