package estrucDatos.examen2EDA.clinicaAlumnos.listas;

public class UnorderedSimpleLinkedList<T> extends SimpleLinkedList<T> implements UnorderedListADT<T> {
	
	public void addToFront(T elem) {
	// a�ade un elemento al comienzo
		Node<T> n = new Node<T>(elem);
		n.next = first;
		first = n;
		if (n.next == null) last = n;
		count++;
	}

	public void addToRear(T elem) {
	// a�ade un elemento al final 
		Node<T> n = new Node<T>(elem);
		if (first == null) {first = n; last = n;}
		else {
		  last.next = n;
	  	  last = n;
		}
	    count++;
	}
	
	public void addAfter(T elem, T target) {
	// A�ade elem detr�s de otro elemento concreto, target,  que ya se encuentra en la lista
		// �COMPLETAR!
	}

}
