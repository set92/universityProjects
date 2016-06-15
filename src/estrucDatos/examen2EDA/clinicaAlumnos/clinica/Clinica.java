package estrucDatos.examen2EDA.clinicaAlumnos.clinica;

import estrucDatos.examen2EDA.clinicaAlumnos.listas.Node;
import estrucDatos.examen2EDA.clinicaAlumnos.listas.UnorderedSimpleLinkedList;

import java.util.Iterator;

public class Clinica {
    // Una clinica consta de una lista de pacientes y una lista de medicamentos

    private UnorderedSimpleLinkedList<Paciente> laListaPac;
    private UnorderedSimpleLinkedList<Medicamento> laListaMed;

    public Clinica() {
        laListaPac = new UnorderedSimpleLinkedList<Paciente>();
        laListaMed = new UnorderedSimpleLinkedList<Medicamento>();
    }

    public void addPaciente(String nom, int c) {
        Paciente nuevo = new Paciente(nom, c, new UnorderedSimpleLinkedList<Medicamento>());
        laListaPac.addToFront(nuevo);
    }

    public void escribirMedClinica() {
        // post: visualiza todos los medicamentos de la clinica junto con la
        // cantidad de pacientes que los toman
        Iterator<Medicamento> it = laListaMed.iterator();
        while (it.hasNext()) {
            Medicamento med = it.next();
            System.out.print(med.getNombre() + ": " + med.getCantidad() + "     ");
        }
        System.out.println();
        System.out.println();
    }

    public void escribirPacClinica() {
        // pre: true (no hay restricciones).
        // post: visualiza todos los pacientes de la clinica con sus respectivos
        // medicamentos
        System.out.println("Pacientes de la Clinica: ");
        System.out.println(laListaPac.toString());
        Iterator<Paciente> it = laListaPac.iterator();
        while (it.hasNext()){
            Paciente pac = it.next();
            System.out.println(pac.getNombre()+": "+ pac.getLista());
        }
        // COMPLETAR CODIGO-- RECUERDA COMENTAR LA COMPLEJIDAD
    }

    public void addMedicina(Medicamento med) {
        laListaMed.addToRear(med);
    }

    public void addMedicinaPaciente(String pPac, String nMed) {
        // Pre: pPac es un paciente de la clinica y no toma la medicina nMed
        // Post: se ha insertado la medicina nMed al paciente pPac. Si la
        // clinica tenia la medicina, entonces la cantidad de pacientes
        // que toman nMed ha aumentado. Si no, nMed se ha añadido a los
        // medicamentos de la clinica.
        boolean paciente = false;
        boolean medicamento = false;
        Node<Paciente> pact = new Node<Paciente>(laListaPac.first());
        Node<Medicamento> mact = new Node<Medicamento>(laListaMed.first());
        while (!paciente && !laListaPac.isEmpty()) {
            if (pPac.equals(pact.data)) paciente = true;
            else pact = pact.next;
        }

        while (!medicamento && !laListaMed.isEmpty()) {
            if (nMed.equals(mact.data)) paciente = true;
            else mact = mact.next;
        }
        if (!medicamento) {

            this.laListaMed.addToRear(mact.data);
        }
        mact.data.setCantidad(mact.data.getCantidad()+1);
        pact.data.getLista().addToRear(mact.data);
    }
    // Coste:
    //          m+n siendo m el número de pacientes y n el número de medicamentos. coste lineal. ??


    public void removeMedicinaPaciente(String pPac, String nMed) {
        // pre: true. (No hay restricciones. Puede que no exista pPac, que no
        // tome nMed, que la medicina no est� en la clinica, etc. En estos
        // casos el metodo no hara nada.)
        // post: Se ha eliminado la medicina nMed del paciente pPac y ha quedado
        // reflejado en la lista de medicinas de la clinica. Este metodo no
        // elimina medicinas de la clinica.
        boolean paciente = false;
        boolean medicamento = false;
        Node<Paciente> pact = new Node<Paciente>(laListaPac.first());
        Node<Medicamento> mact = new Node<Medicamento>(laListaMed.first());
        while (!paciente && !laListaPac.isEmpty()) {
            if (pPac.equals(pact.data)) paciente = true;
            else pact = pact.next;
        }

        while (!medicamento && !laListaMed.isEmpty()) {
            if (nMed.equals(mact.data)) medicamento = true;
            else mact = mact.next;
        }
        if (paciente && medicamento) {
            pact.data.getLista().remove(mact.data);
            mact.data.setCantidad(mact.data.getCantidad()-1);//dejar reflejado que se ha eliminado una medicina
        }
        //Coste:
        //          m+n siendo m el número de pacientes y n el número de medicamentos. coste lineal. ??
    }
}