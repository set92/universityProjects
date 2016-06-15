package estrucDatos.radixSort;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

/**
 * Created by toburi on 09/11/2015.
 * Creado por toburi el 09/11/2015.
 */
public class radixSort {

    public static double timeTrial(int N) {
        int MAX = 1000000;
        int digitos = (int)(Math.log10(MAX)+1);
        String[] a = {"azo","oza","zzz","dds","ssf"};
        Random randomGenerator = new Random();

        Stopwatch timer = new Stopwatch();
        radixSort ord = new radixSort();
        ord.ordenarKoldoStrings(a, 3);
        return timer.elapsedTime();
    }

    public static void main(String[] args) {
        for (int N = 250; true; N += N) {
            double time = timeTrial(N);
            System.out.printf("%7d %5.1f\n", N, time);
        }
    }

    public void radixSortfacil(int[] a){
        int i, m = a[0], exp = 1, n = a.length;
        int[] b = new int[10];
        for (i = 1; i < n; i++)
            if (a[i] > m) m = a[i];
        while (m / exp > 0) {
            int[] bucket = new int[10];

            for (i = 0; i < n; i++)
                bucket[(a[i] / exp) % 10]++;
            for (i = 1; i < 10; i++)
                bucket[i] += bucket[i - 1];
            for (i = n - 1; i >= 0; i--)
                b[--bucket[(a[i] / exp) % 10]] = a[i];
            for (i = 0; i < n; i++)
                a[i] = b[i];
            exp *= 10;
        }
    }

    public void ordenarKoldoNumeros(int[] a, int nCifras){
        Queue<Integer>[] colas = new LinkedList[10];
        for (int i = 0; i < colas.length; i++) {
            colas[i] = new LinkedList<Integer>();
        }
        int pot = 1, pos, m, elem;
        for (int i = nCifras-1; i >= 0; i--) {
            for (int j = 0; j < a.length; j++) {
                pos = (a[j]/pot)%10;
                colas[pos].add(a[j]);
            }
            m=0;
            for (int j = 0; j < colas.length; j++) {
                while (!colas[j].isEmpty()){
                    elem = colas[j].remove();
                    a[m]=elem;
                    m++;
                }
            }
            pot=pot*10;
        }
    }

    public void ordenarKoldoStrings(String[] a, int nLengthMax){
        Queue<String>[] colas = new LinkedList[10];
        for (int i = 0; i < colas.length; i++) {
            colas[i] = new LinkedList<String>();
        }
        int pot = 1, pos, m;
        String elem;
        for (int i = nLengthMax-1; i >= 0; i--) {
            for (int j = 0; j < a.length; j++) {
                pos = posi(a[j].charAt(i-1));
                colas[pos].add(a[j]);
            }
            m=0;
            for (int j = 0; j < colas.length; j++) {
                while (!colas[j].isEmpty()){
                    elem = colas[j].remove();
                    a[m]=elem;
                    m++;
                }
            }
            pot=pot*10;
        }
    }
    private int posi(Character c){
        return (int)c - (int)'a';
    }

    private int[] ordenarNumerosParecidoKoldo(int[] input, int place){
        int[] out = new int[input.length];
        int[] count = new int[10];

        for(int i=0; i < input.length; i++){
            int digit = getDigit(input[i], place);
            count[digit] += 1;
        }
        for(int i=1; i < count.length; i++){
            count[i] += count[i-1];
        }
        for(int i = input.length-1; i >= 0; i--){
            int digit = getDigit(input[i], place);

            out[count[digit]-1] = input[i];
            count[digit]--;
        }

        return out;
    }
    private static int getDigit(int value, int digitPlace){
        return ((value/digitPlace ) % 10);
    }
    
    private int[] ordenarRosetta(int[] old){
        for (int shift = Integer.SIZE - 1; shift > -1; shift--) { // Loop for every bit in the integers
            int[] tmp = new int[old.length]; // The array to put the partially sorted array into
            int j = 0; // The number of 0s

            // Move the 0s to the new array, and the 1s to the old one
            for (int i = 0; i < old.length; i++) {
                boolean move = old[i] << shift >= 0; // If there is a 1 in the bit we are testing, the number will be negative

                // If this is the last bit, negative numbers are actually lower
                if (shift == 0 ? !move : move) {
                    tmp[j] = old[i];
                    j++;
                } else {
                    // It's a 1, so stick it in the old array for now
                    old[i - j] = old[i];
                }
            }

            // Copy over the 1s from the old array
            for (int i = j; i < tmp.length; i++) {
                tmp[i] = old[i - j];
            }

            // And now the tmp array gets switched for another round of sorting
            old = tmp;
        }

        return old;
    }
}
