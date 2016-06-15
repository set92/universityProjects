package estrucDatos.examen2EDA.clinicaAlumnos.listas;

public class OrderedSimpleLinkedList<T> extends SimpleLinkedList<T> implements OrderedListADT<T> {
	
	public void add(T elem){
		count++;
	    if (isEmpty()) {
	    	first = new Node<T>(elem);
			last = first;
	    }
	    else {
	    	Node<T> current = first;
	    	Node<T> ant = null;
	        Comparable<T> temp = (Comparable<T>)elem;

	    	while ((current != null) && (temp.compareTo(current.data) > 0) ) {
	    		ant = current; 
	    		current = current.next; 
	    	}
    		Node<T> newElem = new Node<T>(elem);	
    		newElem.next = current;

	    	if (ant == null) { // first position
	    		first = newElem;
	    	}
	    	else {
	    		ant.next = newElem;
	    		if (current == null) last = newElem;
	    	}
		
	    }
	}


}
