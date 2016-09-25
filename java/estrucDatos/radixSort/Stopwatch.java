package estrucDatos.radixSort;

/**
 * Created by toburi on 09/11/2015.
 * Creado por toburi el 09/11/2015.
 */
public class Stopwatch {

    private final long start;

    /** Create a stopwatch object. */
    public Stopwatch() {
        start = System.currentTimeMillis();
    }

    /**
     * Return elapsed time (in seconds) since this object was created.
     */
    public long elapsedTime() {
        long now = System.currentTimeMillis();
        return (now - start);
    }
}

