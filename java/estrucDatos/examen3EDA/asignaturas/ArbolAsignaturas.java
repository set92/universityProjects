package estrucDatos.examen3EDA.asignaturas;

/**
 * Created by toburi on 21/12/2015.
 * Creado por toburi el 21/12/2015.
 */
public class ArbolAsignaturas extends BinarySearchTree<Asignatura>{
    //arbol ordenado alfabeticamente por el nombre de la asignatura

    //Post: devolver valor de la mejor nota del arbol
    public Integer mejorNota(){
        return mejorNota(root);
    }

    private Integer mejorNota(BinaryTreeNode<Asignatura> act) {
        if (act != null){
            int maxI = mejorNota(act.left);
            int maxD = mejorNota(act.right);
            return maximo(maxI, maxD, act.content);
            //Maximo es un metodo que calcula el mayor de 3 numeros
        }
    }

    private Integer maximo(int maxI, int maxD, Asignatura content) {
        return null;
    }

    private Integer mejorNotaOrd(BinaryTreeNode<Asignatura> act) {
        //Arbol esta ordenado por nota
        BinaryTreeNode<Asignatura> elem = act;
        while (elem.right != null){
            elem = elem.right;
        }
        return elem.content.nota;
    }
}
