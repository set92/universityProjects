<?php
if (!file_exists($BD_FILE)) {
    echo('<p>No hay comentarios aún...</p>');
} elseif (!($bd = simplexml_load_file($BD_FILE))) {
    echo('<p>Error al leer comentarios.</p>');
} else {
    $bd = simplexml_load_file($BD_FILE);
    foreach ($bd->usuario as $visita) {

        echo('<div class="cabecera_comentario">');
            echo('<span class="nombre">' . $visita->nombre . ' (' . $visita->fecha . ')</span>');
        echo('</div>');

        echo('<div class="comentario">');
            echo('<span id="' . $visita['id'] . '">');
                echo($visita->comentario);
            echo('</span>');
        echo('</div>');

        echo('<br/>');
    }
}
?>