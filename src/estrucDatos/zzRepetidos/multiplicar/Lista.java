package estrucDatos.zzRepetidos.multiplicar;

/**
 * Created by setto on 04/06/2016.
 */
public class Lista<T> {
    Node<T> first;

    public static void main(String[] args) {

    }

    public void multiplicar(Integer n){
        Node<T> act = first;
        int cont = n;
        while (act.next != first){
            if (act.data != act.next.data){
                while (cont >= 0){
                    Node<T> nuevo = new Node<>();
                    nuevo.prev = act.next.prev;
                    nuevo.next = act.next;
                    act.next = nuevo;
                    act.next.prev = nuevo;
                }
                act = act.next;
            }

        }
    }

    private class Node<T> {
        String data;
        Node<T> next;
        Node<T> prev;
    }
}
