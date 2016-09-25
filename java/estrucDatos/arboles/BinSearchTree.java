package estrucDatos.arboles;

/**
 * Created by toburi on 30/11/2015.
 * Creado por toburi el 30/11/2015.
 */
public class BinSearchTree<T> {
    BinaryTreeNode<T> root;
    int count;

    public BinSearchTree(T[] a) {
        //pre: a esta ordenado ascendentemente
        root = BinSearchTree(a,0, a.length-1);
        count = a.length;
    }

    private BinaryTreeNode<T> BinSearchTree(T[] a,int com,int fin){
        if (com > fin) return null;
        else {
            int mitad = (com+fin)/2;
            BinaryTreeNode<T> nuevo = new BinaryTreeNode<>(a[mitad]);
            nuevo.left = BinSearchTree(a,com,mitad-1);
            nuevo.right = BinSearchTree(a,mitad+1,fin);
            return nuevo;
        }
    }
}
