package estrucDatos.examen2EDA.colegasDeActor;

import java.util.ArrayList;
import java.util.Queue;
import java.util.stream.Stream;

/**
 * Created by toburi on 22/11/2015.
 * Creado por toburi el 22/11/2015.
 */
public class NewList<T> extends ArrayList<T> implements Queue<T> {
    @Override
    public boolean offer(T t) {
        return false;
    }

    @Override
    public T remove() {
        return null;
    }

    @Override
    public T poll() {
        return null;
    }

    @Override
    public T element() {
        return null;
    }

    @Override
    public T peek() {
        return null;
    }

    @Override
    public Stream<T> stream() {
        return null;
    }

    @Override
    public Stream<T> parallelStream() {
        return null;
    }
}
