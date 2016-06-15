package ingSoftware.facade.compiladorJava;

/**
 * Created by toburi on 25/02/2016.
 * Creado por toburi el 25/02/2016.
 */
public class Compilador {
    private static Compilador compilador;
    private Scanner scanner;
    private Parser parser;
    private NodeBuilder nodeBuilder;
    private CodeGenerator codeGenerator;

    public Compilador() {
        this.scanner = new Scanner();
        this.parser = new Parser();
        this.nodeBuilder = new NodeBuilder();
        this.codeGenerator =  new CodeGenerator();
    }

    public static Compilador getCompilador(){
        return compilador;
    }

    private void compilar(){
        scanner.scan();
        parser.parse();
        nodeBuilder.build();
        codeGenerator.generate();
    }
}
