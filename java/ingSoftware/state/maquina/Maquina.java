package ingSoftware.state.maquina;

/**
 * Created by toburi on 03/03/2016.
 * Creado por toburi el 03/03/2016.
 */
public class Maquina {
    private Estado estado;
    private static Maquina maq = new Maquina();
    private Maquina(){
        estado = new Bien();
    }

    public static Maquina getMaq() {
        return maq;
    }

    public void cambiarEstado(Estado pEstado){
        estado = pEstado;
    }
    public void pedirProducto(){
        // Responde de manera distinta según el estado
        estado.pedir();
    }

    public boolean hayExistencias(){
        return false;
    }
    public void actualizarExistencias(){

    }

    public void actualizarCambios(){

    }
}
