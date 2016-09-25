package estrucDatos.examen2015.ejer1;

/**
 * Created by toburi on 18/05/2016.
 */
public class Matriz {
    Node first;

    public static void main(String[] args) {
        Matriz m1 = new Matriz();
        m1.first = new Node(2,2,3);
        m1.first.next = new Node(2,4,5);
        m1.first.next.next = new Node(3,1,1);
        m1.first.next.next.next = new Node(4,4,2);

        Matriz m2 = new Matriz();
        m2.first = new Node(1,1,9);
        m2.first.next = new Node(2,2,7);
        m2.first.next.next = new Node(3,3,2);
        m2.first.next.next.next = new Node(4,4,3);

        Matriz m3 = suma(m1,m2);
        Node actual = m3.first;
        while (actual != null){
            System.out.println(actual.fila+","+actual.col+","+actual.dato);
            actual = actual.next;
        }
    }

    public static Matriz suma(Matriz m1, Matriz m2){
        Matriz m3 = new Matriz();
        Node p1 = m1.first;
        Node p2 = m2.first;
        Node p3;
        //Hacemos primer elemento por separado
        if (p1.fila < p2.fila && p1.col < p2.col){
            m3.first = new Node(p1.fila,p1.col,p1.dato);
            p1 = p1.next;
        }else if (p1.fila > p2.fila && p1.col > p2.col){
            m3.first = new Node(p2.fila,p2.col,p2.dato);
            p2 = p2.next;
        }else{
            m3.first = new Node(p1.fila,p1.col,p1.dato+p2.dato);
            p1 = p1.next;
            p2 = p2.next;
        }
        //Creamos indicador a la matriz que devolveremos
        p3 = m3.first;
        while (p1 != null || p2 != null){
            if (p1 == null){
                p3.next = new Node(p2.fila,p2.col,p2.dato);
                p2 = p2.next;
            }else if (p2 == null){
                p3.next = new Node(p1.fila,p1.col,p1.dato);
                p1 = p1.next;
            }else if (p1.fila.equals(p2.fila) && p1.col.equals(p2.col)){
                p3.next = new Node(p1.fila,p1.col,p1.dato+p2.dato);
                p1 = p1.next;
                p2 = p2.next;
            }else if (p1.fila < p2.fila || p1.col < p2.col){
                p3.next = new Node(p1.fila,p1.col,p1.dato);
                p1 = p1.next;
            }else{
                p3.next = new Node(p2.fila,p2.col,p2.dato);
                p2 = p2.next;
            }

            p3 = p3.next;
        }
        return m3;
    }
}
