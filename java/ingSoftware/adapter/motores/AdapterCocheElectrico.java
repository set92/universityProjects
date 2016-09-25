package ingSoftware.adapter.motores;

/**
 * Created by toburi on 25/02/2016.
 * Creado por toburi el 25/02/2016.
 */
public abstract class AdapterCocheElectrico implements Motor {
    CocheElectrico cocheElectrico = new CocheElectrico();

    @Override
    public void arrancar() {
        cocheElectrico.conectar();
    }

    @Override
    public void acelerar() {
        cocheElectrico.incrVelocidad();

    }

    @Override
    public void apagar() {
        cocheElectrico.detenerse();
        cocheElectrico.desconectar();

    }
}
