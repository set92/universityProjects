package estrucDatos.examen1EDA.robot;

import java.util.ArrayList;

public class Camino {
	Node first;
	
	public CircularLinkedList<String> obtCoordenadas(ArrayList<String> acciones){
		CircularLinkedList<String> cl = new CircularLinkedList<String>();
        Node temp = first;

        for (int i = 0; i < acciones.size(); i++) {
            cl.last.next = new NodeCircularLinkedList<String>();
            cl.last.next.data = temp.coord;
            // TODO Enlazar el nuevo nodo en la lista circular

            cl.last = cl.last.next;

            if (acciones.get(i).equals("izquierda")) temp = temp.left;
            else if (acciones.get(i).equals("derecha")) temp = temp.right;
            else if (acciones.get(i).equals("adelante")) temp = temp.next;

        }
        return cl;
    }
}
