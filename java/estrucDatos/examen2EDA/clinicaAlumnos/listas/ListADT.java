package estrucDatos.examen2EDA.clinicaAlumnos.listas;

import java.util.Iterator;

public interface ListADT<T> {

public T removeFirst();
//Elimina el primer elemento de la lista

public T removeLast();
//Elimina el �ltimo elemento de la lista

public T remove(T elem);
//Elimina un elemento concreto de la lista

public T first();
//Da acceso al primer elemento de la lista

public T last();
//Da acceso al �ltimo elemento de la lista

public boolean contains(T elem);
//Determina si la lista contiene un elemento concreto

public T find(T elem);
//Determina si la lista contiene un elemento concreto, y develve su referencia, null en caso de que no est�

public boolean isEmpty();
//Determina si la lista est� vac�a

public int size();
//Determina el n�mero de elementos de la lista

public Iterator<T> iterator();

}
