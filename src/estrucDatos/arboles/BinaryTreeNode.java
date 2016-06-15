package estrucDatos.arboles;

/**
 * Created by toburi on 30/11/2015.
 * Creado por toburi el 30/11/2015.
 */
public class BinaryTreeNode<T> {
    protected T element;
    protected BinaryTreeNode<T> left, right;

    public BinaryTreeNode(T element) {
        this.element = element;
    }

}
