package estrucDatos.examen2EDA.clinicaAlumnos.listas;

public interface UnorderedListADT<T> extends ListADT<T> {
	
	public void addToFront(T elem);
	// a�ade un elemento al comienzo 

	public void addToRear(T elem);
	// a�ade un elemento al final 
	
	public void addAfter(T elem, T target);
	// A�ade elem detr�s de otro elemento concreto, target,  que ya se encuentra en la lista

}
