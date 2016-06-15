package ingSoftware.builder.fabricaCoches;

/**
 * Created by toburi on 24/02/2016.
 * Creado por toburi el 24/02/2016.
 */
public class CocheBuilderBMW extends CocheBuilder {

    @Override
    public void elegirTipoRuedas() {
        System.out.println("Elegidas ruedas marca X");
    }

    @Override
    public void elegirMotor() {
        System.out.println("Elegidas motor de 120 caballos");
    }

    @Override
    public void elegirNumPuertas() {
        System.out.println("Elegidas 4 puertas");
    }

    @Override
    public void elegirSiAireAcondicionado() {
        System.out.println("Elegido coche con aire acondicionado");
    }

    @Override
    public void montar() {
        System.out.println("BRRR BRRZZ MONTANDO COCHE");
    }
}
