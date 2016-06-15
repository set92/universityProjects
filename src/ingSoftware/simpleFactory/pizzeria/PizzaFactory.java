package ingSoftware.simpleFactory.pizzeria;

/**
 * Created by toburi on 18/02/2016.
 * Creado por toburi el 18/02/2016.
 */
public class PizzaFactory {
    private static PizzaFactory mPizzaFactory;
    private PizzaFactory (){}
    public static PizzaFactory getPizzaFactory(){
        if (mPizzaFactory == null) {mPizzaFactory = new PizzaFactory();}
        return mPizzaFactory;
    }
    public Pizza createPizza (String tipo){
        Pizza miPizza = null;
        if (tipo.equals("Queso")) { miPizza = new PizzaQueso();}
        else if (tipo.equals( "Pepperoni")) { miPizza = new PizzaPepperoni();}
        else if (tipo.equals("Carbonara")) { miPizza = new PizzaCarbonara();}
        else if (tipo.equals("Barbacoa")) { miPizza = new PizzaBarbacoa();}
        return miPizza;
    }
    public class PizzaBarbacoa extends Pizza{
        public PizzaBarbacoa() {}
    }
    public class PizzaQueso extends Pizza{
        public PizzaQueso() {}
    }
    public class PizzaPepperoni extends Pizza{
        public PizzaPepperoni() {}
    }
    public class PizzaCarbonara extends Pizza{
        public PizzaCarbonara() {}
    }
}
