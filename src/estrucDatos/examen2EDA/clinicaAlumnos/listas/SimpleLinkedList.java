package estrucDatos.examen2EDA.clinicaAlumnos.listas;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class SimpleLinkedList<T> implements ListADT<T> {

	// Atributos
	public Node<T> first; // apuntador al primero
	public Node<T> last;  // apuntador al �ltimo
	protected int count;

    public T add(String vertice){
        return null;
    }
	// Constructor
	public SimpleLinkedList() {
		first = null;
		last = null;
		count = 0;
	}

	public T removeFirst() {
	//Elimina el primer elemento de la lista
    if (isEmpty())
        return null;
     
     Node<T> result = first; 
     first = first.next;
     if (first == null)
        last = null;
     count--;
     return result.data;
	}

	public T removeLast() {
	//Elimina el �ltimo elemento de la lista
		      if (isEmpty()) return null;
		      
		      Node<T> previous = null;
		      Node<T> current = first;

		      while (current.next != null)
		      {
		         previous = current; 
		         current = current.next;
		      }
		      
		      Node<T> result = last; 
		      last = previous;
		      if (last == null)
		         first = null;
		      else
		         last.next = null;
		      count--;
		      
		      return result.data;
		   }


	public T remove(T elem) {
	//Elimina un elemento concreto de la lista
	if (first == null) return null;
	else {
		if (first.data.equals(elem))
			{ Node<T> found = first;
			  first = first.next;
			  if (first == null) last = null;
			  count--;
			  return found.data;
			}
		else {
			Node<T> actual = first;
			Node<T> ant = null;
			while ((actual.next != null) && !(actual.data.equals(elem))) {
				ant = actual;
				actual = actual.next;
			}
			if (actual.data.equals(elem)) { 
				Node<T> found = actual;
				ant.next = actual.next;
				if (ant.next == null) last = null;
				count--;
				return found.data;
			}
			else return null;
		}
	}
};

	public T first() {
	//Da acceso al primer elemento de la lista
	      if (isEmpty())
	          return null;
	      else return first.data;
	}

	public T last() {
	//Da acceso al �ltimo elemento de la lista
	      if (isEmpty())
	          return null;
	      else return last.data;
	}

	public boolean contains(T elem) {
	//Determina si la lista contiene un elemento concreto
		      if (isEmpty())
		          return false;

		      boolean found = false;
		      Node<T> current = first;

		      while (current != null && !found) 
		         if (elem.equals (current.data))
		            found = true;
		         else
		            current = current.next;
		      return found;
		   }

	public T find(T elem) {
	//Determina si la lista contiene un elemento concreto, y develve su referencia, null en caso de que no est�
	      if (isEmpty())
	          return null;

	      boolean found = false;
	      Node<T> current = first;

	      while (current != null && !found) 
	         if (elem.equals (current.data))
	            found = true;
	         else
	            current = current.next;
	      if (found) return current.data; else return null;
	}

	public boolean isEmpty() 
	//Determina si la lista est� vac�a
	{ return first == null;};
	
	public int size() 
	//Determina el n�mero de elementos de la lista
	{ return count;};
	
	/** Return an iterator to the stack that iterates through the items . */ 
	   public Iterator<T> iterator() { return new ListIterator(); } 

	   // an iterator, doesn't implement remove() since it's optional 
	   private class ListIterator implements Iterator<T> { 

	      private Node<T> current = first; 

	      public boolean hasNext() { return current != null; } 

	      public void remove() { 
	             throw new UnsupportedOperationException(); } 

	      public T next() { // recorre el campo clave
	         if (!hasNext()) throw new NoSuchElementException(); 
	         T item = current.data; 
	         current = current.next; 
	         return item; 
	       } 
	   } // private class
		
		public void visualizarNodos() {
			System.out.println(this.toString());
		}

		@Override
		public String toString() {
			String result = new String();
			Iterator<T> it = iterator();
			while (it.hasNext()) {
				T elem = it.next();
				result = result + "[" + elem.toString() + "] \n";
			}	
			return "SimpleLinkedList " + result + "]";
		}

}
