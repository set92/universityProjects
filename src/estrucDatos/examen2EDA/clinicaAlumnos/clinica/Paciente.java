package estrucDatos.examen2EDA.clinicaAlumnos.clinica;

import estrucDatos.examen2EDA.clinicaAlumnos.listas.UnorderedSimpleLinkedList;

public class Paciente {
	
	/* Un paciente tiene nombre, cama asociada y una lista de medicamentos */
	
	private String nombre;
	private int cama;
	private UnorderedSimpleLinkedList<Medicamento> laListaMedPac;

	public Paciente(String nom, int c, UnorderedSimpleLinkedList<Medicamento> listaMed) {
		nombre = nom;
		cama = c;
		laListaMedPac = listaMed;
	}
		public String getNombre() {
			return nombre;
		}

		public int getCama() {
			return cama;
		}

		public UnorderedSimpleLinkedList<Medicamento> getLista() {
			return laListaMedPac;
		}

		@Override
		public String toString() {
			return "Paciente [nombre=" + nombre + ", cama=" + cama
					+ ", laListaMedPac=" + laListaMedPac + "]";
		}	
}
