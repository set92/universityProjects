package ingSoftware.state.maquina;

/**
 * Created by toburi on 03/03/2016.
 * Creado por toburi el 03/03/2016.
 */
public class Bien implements Estado {
    @Override
    public void pedir() {
        System.out.println("Se servira el producto");
        Maquina.getMaq().actualizarCambios();
        Maquina.getMaq().actualizarExistencias();
        if (!Maquina.getMaq().hayExistencias())Maquina.getMaq().cambiarEstado(new DineroInsuficiente());
    }
}
