<!DOCTYPE html>
<html>
<head>
    <title>Pokemon Comparator</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/jquery-ui.min.js"></script>
    <link rel="stylesheet" type="text/css" href="css/main.css"/>
    <link rel="stylesheet" type="text/css" href="http://code.jquery.com/ui/1.12.1/themes/smoothness/jquery-ui.css"/>
    <script src="/js/comparator.js"></script>

    <script>
        $(function () {
            $("#jQuery_accordion").accordion({
                collapsible: true,
                active: false,
                heightStyle: "content",
                activate: function (event, ui) {
                }
            });
            $('#jQuery_accordion').find('input[type="checkbox"]').click(function (e) {
                e.stopPropagation();
            });
        });

    </script>
    <?php
    require_once __DIR__ . '/vendor/autoload.php';

    use PokePHP\PokeApi;

    $api = new PokeApi;
    $data = $api->pokedex('1');
    $string = json_decode($data, true);
    ?>

</head>

<body>
<?php include "header.php"; ?>

<div id="centerDivs">
    <div id="jQuery_accordion">
        <!--Aqui se creara dinamicamente el acordeon-->
    </div>
</div>

<?php include "footer.php"; ?>

<?php for ($i = 0; $i <= 3; $i++) {
    $pokemon = $string['pokemon_entries'][$i]['pokemon_species']['name'];

    $jsonofspecies = $api->pokemonSpecies($i + 1);
    $decodedJson = json_decode($jsonofspecies, true);
    $flavor = $decodedJson['flavor_text_entries']['1']['flavor_text'];
    ?>
    <script>
        $("<h3> <?php echo $pokemon;?> <input name='<?php echo $pokemon;?>' onclick='checkPokemonSelected(this);' class='rightHeader<?php echo $i ?>' type='checkbox'/></h3>").appendTo("#jQuery_accordion");
        $("<div><p><?php echo str_replace("\n", " ", $flavor);?></p></div>").appendTo("#jQuery_accordion");
        $("#jQuery_accordion").accordion("refresh");
    </script>
<?php } ?>


</body>
</html>
