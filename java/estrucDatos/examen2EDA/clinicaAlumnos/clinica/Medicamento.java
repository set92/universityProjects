package estrucDatos.examen2EDA.clinicaAlumnos.clinica;

public class Medicamento {
	/*
	 * Un medicamento tiene nombre y cantidad de pacientes que lo están tomando
	 */
	
	private String nombre;
	private int numPac;

	public Medicamento(String nom, int n) {
		nombre = nom;
		numPac = n;
	}
		public String getNombre() {
			return nombre;
		}

		public int getCantidad() {
			return numPac;
		}

		public void setNombre(String nom) {
			 nombre = nom;
		}

		public void setCantidad(int n) {
			numPac = n;
		}
    	
		@Override
		public String toString() {
			return "Medicamento [nombre=" + nombre + ", numPac=" + numPac + "]";
		}

}
