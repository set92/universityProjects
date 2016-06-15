package estrucDatos.examen2012.ejer4;

import estrucDatos.examen2012.ejer4.clasesExtra.BinaryTree;
import estrucDatos.examen2012.ejer4.clasesExtra.BinaryTreeNode;
import estrucDatos.examen2012.ejer4.clasesExtra.Medicina;

import java.util.HashMap;

/**
 * Created by toburi on 03/01/2016.
 * Creado por toburi el 03/01/2016.
 */
public class ArbolMedicinas extends BinaryTree<Medicina> {

    public HashMap<String, Integer> convertirArbolEnTH(){
        HashMap<String,Integer> aDevolver = new HashMap<>();
        BinaryTreeNode<Medicina> act = root;

        postOrden(act, aDevolver);

        return aDevolver;
    }

    private void postOrden(BinaryTreeNode<Medicina> raiz, HashMap<String, Integer> aDevolver) {
        if (raiz != null){
            postOrden(raiz.left,aDevolver);
            postOrden(raiz.right,aDevolver);
            if (aDevolver.containsKey(raiz.content.nombre)){
                aDevolver.put(raiz.content.nombre, (aDevolver.get(raiz.content.nombre))+raiz.content.ventas);
            }else{
                aDevolver.put(raiz.content.nombre, raiz.content.ventas);
            }

        }
    }
// Post: el resultado es una table hash con los elementos del árbol, donde
// cada elemento aparece una sola vez (el dato asociado a cada producto
// es el total de ventas de ese producto)

}
