package ingSoftware.strategy.cochesAudi;

/**
 * Created by toburi on 03/03/2016.
 * Creado por toburi el 03/03/2016.
 */
public class SimuladorCoches {
    public static void main(String[] args) {
        ComportamientoFrenar pFrenado;
        pFrenado = new FrenadoABS();
        CocheAudi miCoche = new CocheAudi(pFrenado);
    }
}
