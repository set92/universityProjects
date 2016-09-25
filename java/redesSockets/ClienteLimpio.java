package redesSockets;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;

public class ClienteLimpio extends JFrame{
    private JTextField campoIntroducir;
    private JTextArea areaPantalla;
    private ObjectOutputStream salida;
    private ObjectInputStream entrada;
    private String mensaje = "";
    private String servidorChat;
    private Socket cliente;

    // inicializar servidorChat y configurar GUI
    public ClienteLimpio(String host) {
        super("ClienteLimpio");
        servidorChat = host; // maquina donde está el servidor
        Container contenedor = getContentPane();
        // crear campoIntroducir y registrar componente de escucha
        campoIntroducir = new JTextField();
        campoIntroducir.setEditable(false);
        campoIntroducir.addActionListener(
                new ActionListener() {
                    // enviar mensaje al servidor
                    public void actionPerformed(ActionEvent evento) {
                        enviarDatos(evento.getActionCommand());
                        campoIntroducir.setText("");
                    }
                }
        );
        contenedor.add(campoIntroducir, BorderLayout.NORTH);
        // crear areaPantalla
        areaPantalla = new JTextArea();
        contenedor.add(new JScrollPane(areaPantalla), BorderLayout.CENTER);
        setSize(300, 150);
        setVisible(true);
    } // fin del constructor de ClienteLimpio

    //****** Conectarse al servidor y procesar mensajes del servidor

    private void ejecutarCliente() {
        // conectarse al servidor, obtener flujos, procesar la conexión
        try {
            conectarAServidor(); // Paso 1: crear un socket para realizar la conexión
            obtenerFlujos(); // Paso 2: obtener los flujos de entrada y salida
            procesarConexion(); // Paso 3: procesar la conexión
        }
        // el servidor cerró la conexión
        catch (EOFException excepcionEOF) {
            System.err.println("El cliente termino la conexión");
        }
        // procesar los problemas que pueden ocurrir al comunicarse con el servidor
        catch (IOException excepcionES) {
            excepcionES.printStackTrace();
        } finally {
            cerrarConexion(); // Paso 4: cerrar la conexión
        }
    } // fin del método ejecutarCliente

    //****** conectarse al servidor
    private void conectarAServidor() throws IOException {
        mostrarMensaje("Intentando Realizar Conexión\n");
        // crear Socket para realizar la conexión con el servidor
        cliente = new Socket(InetAddress.getByName(servidorChat), 12345);
        // mostrar la información de la conexión
        mostrarMensaje("Conectado a: " + cliente.getInetAddress().getHostName());
    }// fin del método mostrar mensaje

    //****** obtener flujos para enviar y recibir datos
    private void obtenerFlujos() throws IOException {
        // establecer flujo de salida para los objetos
        salida = new ObjectOutputStream(cliente.getOutputStream());
        salida.flush(); // vacíar búfer de salida para enviar información de encabezado
        // establecer flujo de entrada para los objetos
        entrada = new ObjectInputStream(cliente.getInputStream());
        mostrarMensaje("\nSe recibieron los flujos de E/S\n");
    }// fin del método obtenerFlujos

    //****** procesar la conexión con el servidor
    private void procesarConexion() throws IOException {
        // habilitar campoIntroducir para que el usuario del cliente pueda enviar mensajes
        establecerCampoTextoEditable(true);
        do { // procesar mensajes enviados del servidor
            // leer mensaje y mostrarlo en pantalla
            try {
                mensaje = (String) entrada.readObject();
                mostrarMensaje("\n" + mensaje);
            }
            // atrapar los problemas que pueden ocurrir al leer del servidor
            catch (ClassNotFoundException excepcionClaseNoEncontrada) {
                mostrarMensaje("\nSe recibió un objeto de tipo desconocido");
            }
        } while (!mensaje.equals("SERVIDOR>>> TERMINAR"));
    } // fin del método procesarConexion

    // ******cerrar flujos y socket
    private void cerrarConexion() {
        mostrarMensaje("\nCerrando conexión");
        establecerCampoTextoEditable(false); // deshabilitar campoIntroducir
        try {
            salida.close();
            entrada.close();
            cliente.close();
        } catch (IOException excepcionES) {
            excepcionES.printStackTrace();
        }
    }// fin del método cerrarConexion

    //******enviar mensaje al servidor
    private void enviarDatos(String mensaje) {
        // enviar objeto al servidor
        try {
            salida.writeObject("CLIENTE>>> " + mensaje);
            salida.flush();
            mostrarMensaje("\nCLIENTE>>> " + mensaje);
        }
        // procesar los problemas que pueden ocurrir al enviar el objeto
        catch (IOException excepcionES) {
            areaPantalla.append("\nError al escribir el objeto");
        }
    }//fin del método enviarDatos

    // método utilitario que es llamado desde otros subprocesos para manipular a
    // areaPantalla en el subproceso despachador de eventos
    private void mostrarMensaje(final String mensajeAMostrar) {
        // mostrar mensaje del subproceso de ejecución de la GUI
        SwingUtilities.invokeLater
                (
                        new Runnable() { // clase interna para asegurar que la GUI se actualice apropiadamente
                            public void run() // actualiza areaPantalla
                            {
                                areaPantalla.append(mensajeAMostrar);
                                areaPantalla.setCaretPosition(
                                        areaPantalla.getText().length());
                            }
                        } // fin de la clase interna
                ); // fin de la llamada a SwingUtilities.invokeLater
    }//fin del método mostrarMensaje

    // método utilitario que es llamado desde otros subprocesos para manipular a
    // campoIntroducir en el subproceso despachador de eventos
    private void establecerCampoTextoEditable(final boolean editable) {// mostrar mensaje del subproceso de ejecución de la GUI
        SwingUtilities.invokeLater
                (
                        new Runnable() { // clase interna para asegurar que la GUI se actualice apropiadamente
                            public void run() // establece la capacidad de modificar campoIntroducir
                            {
                                campoIntroducir.setEditable(editable);
                            }
                        } // fin de la clase interna
                ); // fin de la llamada a SwingUtilities.invokeLater
    }

    public static void main(String args[]) {
        ClienteLimpio aplicacion;
        if (args.length == 0)
            aplicacion = new ClienteLimpio("127.0.0.1");
        else
            aplicacion = new ClienteLimpio(args[0]);
        aplicacion.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        aplicacion.ejecutarCliente();
    }
}
