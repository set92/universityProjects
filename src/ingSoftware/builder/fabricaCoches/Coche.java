package ingSoftware.builder.fabricaCoches;

/**
 * Created by toburi on 24/02/2016.
 * Creado por toburi el 24/02/2016.
 */
public class Coche {
    private String tipoRuedas;
    private String tipoMotor;
    private int numPuertas;
    private boolean aireAcondicionado;
    private boolean cadenaMusica;

    public void setTipoRuedas(String tipoRuedas) {
        this.tipoRuedas = tipoRuedas;
    }

    public void setTipoMotor(String tipoMotor) {
        this.tipoMotor = tipoMotor;
    }

    public void setNumPuertas(int numPuertas) {
        this.numPuertas = numPuertas;
    }

    public void setAireAcondicionado(boolean aireAcondicionado) {
        this.aireAcondicionado = aireAcondicionado;
    }

    public void setCadenaMusica(boolean cadenaMusica) {
        this.cadenaMusica = cadenaMusica;
    }
}
