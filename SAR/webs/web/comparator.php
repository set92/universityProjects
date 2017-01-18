<!DOCTYPE html>
<html>
<head>
    <title>Pokemon Comparator</title>
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
    <link rel="stylesheet" type="text/css" href="css/main.css"/>
    <script src="/js/Chart.min.js"></script>

</head>

<body>
<?php include "header.php"; ?>

<canvas id="grafica" style="width:100%; height:30%"> Si estas viendo esto, significa que tu navegador no soporta el comparador. Usa otro navegador.</canvas>

<?php include "footer.php"; ?>

<script src="/js/comparator.js"></script>
<script>inicializar(); </script>

</body>
</html>