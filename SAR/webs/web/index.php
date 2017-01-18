<!DOCTYPE html>
<html>
<head>
    <?php $BD_FILE = 'data/comentarios.xml'; ?>
    <title>Pokemon Comparator</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="author" content="Sergio Tobal y Mikel">
    <link rel="stylesheet" type="text/css" href="css/main.css"/>
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>

    <script type="text/javascript">
        function post() {
            var name = document.getElementById("nombre").value;
            var email = document.getElementById("email").value;
            var comment = document.getElementById("comentario").value;

            $.ajax({
                type: 'POST',
                url: 'post_comments.php',
                dataType: "text",
                data: {
                    user_comm: comment,
                    user_name: name,
                    user_email: email
                },
                success: function (response, status) {
                    document.getElementById("comentarios").innerHTML = response;
                    document.getElementById("comentario").value = "";
                    document.getElementById("nombre").value = "";
                    document.getElementById("email").value = "";
                }
            });
            return false;
        }
    </script>

</head>

<body>
<?php include "header.php" ?>

<div id="centerDivs">
    <h3>En el siguiente bloque de texto podras guardar tus notas, o los resultados de tus comparaciones</h3>
    <div id="notes" contenteditable="true"></div>

    <script src="js/notes.js"></script>

</div>

<div id="contenedor">

    <div id="leftComentarios">
        <h3>Comentarios acerca de PokeCompare:</h3>
        <div id="comentarios">
            <?php include "lista_comentarios.php" ?>
        </div>
    </div>

    <div id="rightComentarios">
        <h2>Añade tu propio comentario con AJAX:</h2>
        <form action="?" method="post" onsubmit="return post();">
            Nombre: <input type="text" id="nombre"/> <br/>
            E-mail: <input type="text" id="email"/> <br/>
            Comentario:<br/>
            <textarea id="comentario" rows="3" cols="30"></textarea> <br/>

            <input type="submit" value="Enviar"/>
        </form>
    </div>


</div>

<?php include "footer.php" ?>
</body>
</html>