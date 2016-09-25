package estrucDatos.examen3EDA.campeonatoFutbol;

/**
 * Created by toburi on 14/01/2016.
 * Creado por toburi el 14/01/2016.
 */
public class Campeonato {
    private Nodo root;

    public String campeon() {
        postOrden(root);
        return root.info.ganador;
    }

    private void postOrden(Nodo raiz) {
        if (raiz.info.golesIzq != -1 ){
            postOrden(raiz.izq);
            postOrden(raiz.der);
            if (raiz.info.golesIzq > raiz.info.golesDer){
                raiz.info.ganador = raiz.izq.info.ganador;
            }else if (raiz.info.golesIzq < raiz.info.golesDer){
                raiz.info.ganador = raiz.der.info.ganador;
            }
            //Si es -1 me da igual, solo significa primer partido pero no es resultado ninguno
            //Faltaria el caso del empate o no hay que evaluarlo porque no hay empates y se
            //desempata con gol de oro o penaltis?
        }
    }
}

