package ingSoftware.builder.pizzeria;

import ingSoftware.builder.pizzeria.Pizzeria;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public class Cliente {
    public static void main(String[] args) {
        Pizzeria pizzeria = new Pizzeria();
        //PizzaBuilder pizzabuilder_queso = new PizzaBuilderQueso();
        PizzaBuilder pizzabuilder_carbonara = new PizzaBuilderCarbonara ();
        pizzeria.setPizzaBuilder(pizzabuilder_carbonara );
        Pizza pizza = pizzeria.getPizza();
    }
}
