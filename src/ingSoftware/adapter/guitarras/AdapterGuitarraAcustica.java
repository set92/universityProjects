package ingSoftware.adapter.guitarras;

/**
 * Created by toburi on 25/02/2016.
 * Creado por toburi el 25/02/2016.
 */
public abstract class AdapterGuitarraAcustica implements Guitarra {
    private GuitarraAcustica guiAcus = new GuitarraAcustica();

    @Override
    public void encender() {
        guiAcus.tocar();
    }

    @Override
    public void apagar() {
        guiAcus.apagar();
    }
}
