package ingSoftware.simpleFactory.pizzeria;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public class Pizzeria {
    public Pizzeria(){
    }
    public Pizza hacerPizza (String tipo){
        Pizza miPizza = PizzaFactory.getPizzaFactory().createPizza(tipo);
        miPizza.preparar();
        miPizza.hornear();
        miPizza.cortar();
        miPizza.meterEnCaja();
        return miPizza;
    }

    public static void main(String [ ] args) {
        Pizzeria miPizzeria = new Pizzeria();
        Pizza bbPizza = miPizzeria.hacerPizza("Barbacoa");
        System.out.println("La pizza esta hecha y es del tipo " + bbPizza.getClass().toString());
    }
}
