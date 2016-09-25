package estrucDatos.examen2EDA.clinicaAlumnos.clinica;

import java.util.Scanner;


public class PruebaClinica {

	public static void main(String[] args) {
		// Las siguientes instruccciones crean la clinica elPilar
		
		Scanner p = new Scanner(System.in);

		Clinica elPilar = new Clinica();

		String nombre;
		int cama;
		int numMed;
		String medicina;
		Medicamento med;
		
 		System.out.println("Cuantos medicamentos vas a introducir en la clinica?");
 		int cuantos = p.nextInt();
 		for (int i = 1; i <= cuantos; i++) {
			System.out.println("Introduce nombre del medicamento");
			nombre = p.next();
			med = new Medicamento(nombre, 0);
			elPilar.addMedicina(med);
 		}
 		System.out.println();

		System.out.println("Cuantos Pacientes vas a introducir en la clinica?");
		cuantos = p.nextInt();
		for (int i = 1; i <= cuantos; i++) {
			System.out.println("Introduce nombre del paciente");
			nombre = p.next();
			System.out.println("Introduce la cama del paciente");
			cama = p.nextInt();
			elPilar.addPaciente(nombre, cama);
			System.out.println("Cuantos medicamentos toma el paciente?");
			numMed = p.nextInt();
			for (int j = 1; j <= numMed; j++) {
				System.out.println("Dame nombre del medicamento:");
				medicina = p.next();
				elPilar.addMedicinaPaciente(nombre, medicina);
			}
			
		}

		// A continuacion se visualiza la clinica
		System.out.println();
		System.out.println();
		elPilar.escribirMedClinica();
		elPilar.escribirPacClinica();
		
		// para probar eliminar un medicamento a un paciente.
		
		System.out.println("Cuanto medicamentos quieres borrar?");
 		cuantos = p.nextInt();
 		for (int i = 1; i <= cuantos; i++) {
			System.out.println("Introduce nombre del paciente al que se la va a quitar un medicamento");
			nombre = p.next();
			System.out.println("Introduce nombre del medicamento a eliminar");
			medicina = p.next();
			elPilar.removeMedicinaPaciente(nombre, medicina);
 		}
 		System.out.println();
		
 	// A continuacion se visualiza la clinica
		System.out.println();
		System.out.println();
		elPilar.escribirMedClinica();
		elPilar.escribirPacClinica();


	}
}
