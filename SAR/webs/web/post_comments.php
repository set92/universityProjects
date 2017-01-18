<?php
$BD_FILE = 'data/comentarios.xml';

$ult_id = "comentario";

if (!file_exists($BD_FILE))
    $bd = new SimpleXMLElement('<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE comentarios SYSTEM "libro_visitas.dtd"><comentarios ult_id="' . $ult_id . '0"></comentarios>');
else $bd = simplexml_load_file($BD_FILE);

$nombre = $_POST['user_name'];
$email = $_POST['user_email'];
$comentario = $_POST['user_comm'];

$id = $ult_id . ((int)substr($bd['ult_id'], strlen($ult_id)) + 1);

$nuevo = $bd->addChild('usuario');
$nuevo['id'] = $id;

$nuevo->addChild('fecha', date(' G:i:s, j F, Y '));
$nuevo->addChild('nombre', $nombre);
$nuevo->addChild('email', $email);
$nuevo->addChild('comentario', $comentario);

$bd['ult_id'] = $id;
$bd->asXML($BD_FILE);

include "lista_comentarios.php";
?>