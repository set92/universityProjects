<?php
    require_once __DIR__.'/vendor/autoload.php';
    
    $id = $_POST['pokemon1'];
    $id2 = $_POST['pokemon2'];

    use PokePHP\PokeApi;
    $api = new PokeApi;

    $data = $api->pokemon($id);            
    $string = json_decode($data,true);
    for ($i = 0; $i <= 5; $i++) {
        $number = $string['stats'][$i]['base_stat'];
        echo $number;
        echo  "\n";
    }

    $data = $api->pokemon($id2);            
    $string = json_decode($data,true);
    for ($i = 0; $i <= 5; $i++) {
        $number = $string['stats'][$i]['base_stat'];
        echo $number;
        echo  "\n";

    }

?>