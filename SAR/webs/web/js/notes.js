document.getElementById('notes').innerHTML = localStorage['text'] || 'Escribe aqui tus notas, o las comparaciones recibidas ';

 setInterval(function() {
      localStorage['text'] = document.getElementById('notes').innerHTML;
 }, 2000);