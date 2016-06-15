package estrucDatos.examen3EDA.evaluador;

import java.util.HashMap;
import java.util.LinkedList;

/**
 * Created by toburi on 29/12/2015.
 * Creado por toburi el 29/12/2015.
 */
public class ListaVariables {
    HashMap<String, Integer> lasVariables;

    public void evaluar(LinkedList<Instruccion> lista){
        for (int i = 0; i < lista.size(); i++) {
            //Faltaria comprobar si no estan en el hashmap el num1, num2 y num3, es necesario hacerlo?
            int num2 = lasVariables.get(lista.get(i).nombre2);
            int num3 = lasVariables.get(lista.get(i).nombre3);
            String operador = lista.get(i).operador;

            switch (operador){
                case "+": lasVariables.put(lista.get(i).nombre1, num2 + num3);
                    break;
                case "-":lasVariables.put(lista.get(i).nombre1, num2 - num3);
                    break;
                case "/":lasVariables.put(lista.get(i).nombre1, num2 / num3);
                    break;
                case "*":lasVariables.put(lista.get(i).nombre1, num2 * num3);
                    break;

            }

        }

    }
}
