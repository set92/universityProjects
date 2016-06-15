package estrucDatos.examen2015.ejer3;

import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by toburi on 18/05/2016.
 */
public class Terremoto {
    protected final int DEFAULT_CAPACITY = 100;
    protected static int numVertices;
    protected static boolean[][] adjMatrix;
    protected static String[] vertices;

    public static int index(String t) {
        //Devuelve el indice de vertices correspondiente a t
        for (int i = 0; i < vertices.length; i++) {
            if (vertices[i].equals(t)) return i;
        }
        return -1;
    }

    public static void main(String[] args) {
        vertices = new String[10];
        vertices[0] = "londres"; vertices[1] = "wisconsin"; vertices[2] = "varsovia";
        vertices[3] = "amurrio"; vertices[4] = "eibar"; vertices[5] = "seattle";
        vertices[6] = "glasgow"; vertices[7] = "texas";

        adjMatrix = new boolean[10][10];

        for (int i = 0; i <= 7; i++) {
            for (int j = 0; j <= 7; j++) {
                if ((i == 0 && (j == 4 || j == 7 || j == 2)) ||
                        (i == 2 && (j == 0 || j == 5)) ||
                        (i == 7 && (j == 0 || j == 1 || j == 3 || j == 6)) ||
                        (i == 4 && (j == 0)) || (i == 6 && (j == 7))) {
                    adjMatrix[i][j] = true;
                } else {
                    adjMatrix[i][j] = false;
                }
            }
        }
        Terremoto t1 = new Terremoto();
        ArrayList t = t1.comarcasAfectadas(6, "londres");
        t.stream().forEach(System.out::println);
    }

    public ArrayList<String> comarcasAfectadas(int intensidad, String c) {
        ArrayList<String> afectados = new ArrayList<>();
        boolean[] examinados = new boolean[vertices.length];
        
        int inicio = index(c);
        afectados.add(c);
        examinados[inicio] = true;

        while (intensidad >= 1) {
            for (int i = 0; i < adjMatrix.length; i++) {
                if (!examinados[i] && adjMatrix[i][inicio]) {
                    afectados.add(vertices[i]);
                    examinados[i] = true;
                }
            }
            intensidad = intensidad / 2;
        }
        return afectados;
    }
}
