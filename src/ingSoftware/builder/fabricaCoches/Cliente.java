package ingSoftware.builder.fabricaCoches;

/**
 * Created by toburi on 24/02/2016.
 * Creado por toburi el 24/02/2016.
 */
public class Cliente {
    public static void main(String[] args) {
        FabricaCoches fabCoches = new FabricaCoches();

        CocheBuilder fabCoches_BMW = new CocheBuilderBMW();
        fabCoches.setCocheBuilder(fabCoches_BMW);
        Coche car = fabCoches.getCoche();
    }
}
