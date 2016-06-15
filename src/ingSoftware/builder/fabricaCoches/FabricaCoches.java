package ingSoftware.builder.fabricaCoches;

/**
 * Created by toburi on 24/02/2016.
 * Creado por toburi el 24/02/2016.
 */
public class FabricaCoches {
    private CocheBuilder cocheBuilder;
    public void setCocheBuilder(CocheBuilder cocheBuilder) {
        this.cocheBuilder = cocheBuilder;
    }
    public Coche getCoche(){
        montarCoche();
        return cocheBuilder.getCar();
    }

    private void montarCoche() {
        cocheBuilder.elegirMotor();
        cocheBuilder.elegirTipoRuedas();
        cocheBuilder.elegirNumPuertas();
        cocheBuilder.elegirSiAireAcondicionado();
        cocheBuilder.montar();
    }


}
