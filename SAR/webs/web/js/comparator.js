function inicializar() {
    var nombrePok1 = sessionStorage.getItem("pokemon1");
    var nombrePok2 = sessionStorage.getItem("pokemon2");

    function ajax() {
        return $.ajax({
            type: 'POST',
            url: 'comparator1.php',
            dataType: "text",
            data: {
                pokemon1: sessionStorage.getItem("pokemon1"),
                pokemon2: sessionStorage.getItem("pokemon2")
            },
            success: function (response, status) {
                response;
            }
        });
    }

    ajax().done(function (result) {
        var stringArray = result.split(/(\s+)/).filter(Number);

        var array1 = stringArray.slice(0, 6);
        var array2 = stringArray.slice(6, 12);

        mostrarDatos(nombrePok1, array1, nombrePok2, array2);
    }).fail(function () {
        alert("error, no se ha podido llamar a la API");
    });
}

var flag = true;
function checkPokemonSelected(obj) {
    if ($(obj).prop('checked')) {
        if (flag == true) {
            sessionStorage.setItem("pokemon1", $(obj).attr('name'));
            flag = false;
        } else {
            sessionStorage.setItem("pokemon2", $(obj).attr('name'));
        }

    } else if (!$(obj).prop('checked')) {
        if (flag == true) {
            sessionStorage.removeItem("pokemon1");
        } else {
            sessionStorage.removeItem("pokemon2");
        }

    }
}

//Recibimos como parametros los array de las estadisticas de los 2 pokemons
function mostrarDatos(nombre1, array1, nombre2, array2) {
    var ctx = document.getElementById("grafica").getContext("2d");
    ctx.fillStyle = "rgba(0, 0, 200, 0.5)";
        ctx.fillRect (30, 30, 55, 50);
    var data = {
        labels: ["HP", "Attack", "Defense", "Speed", "Special Attack", "Special Defense"],
        datasets: [
            {
                label: nombre1,
                backgroundColor: "rgba(179,181,198,0.2)",
                borderColor: "rgba(179,181,198,1)",
                pointBackgroundColor: "rgba(179,181,198,1)",
                pointBorderColor: "#fff",
                pointHoverBackgroundColor: "#fff",
                pointHoverBorderColor: "rgba(179,181,198,1)",
                data: [array1[0], array1[4], array1[3], array1[5], array1[1], array1[2]]
            },
            {
                label: nombre2,
                backgroundColor: "rgba(255,99,132,0.2)",
                borderColor: "rgba(255,99,132,1)",
                pointBackgroundColor: "rgba(255,99,132,1)",
                pointBorderColor: "#fff",
                pointHoverBackgroundColor: "#fff",
                pointHoverBorderColor: "rgba(255,99,132,1)",
                data: [array2[0], array2[4], array2[3], array2[5], array2[1], array2[2]]
            }
        ]
    };

    var options = {
        title: {
            display: true,
            text: "Comparacion entre los pokemons seleccionados"
        },
        scale: {
            ticks: {
                beginAtZero: true
            }
        }
    };

    var myRadarChart = new Chart(ctx, {
        type: 'radar',
        data: data,
        responsive: true,
        maintainAspectRatio: false,
        options: options
    });ctx.fillStyle = "rgba(0, 0, 200, 0.5)";
        ctx.fillRect (30, 30, 55, 50);
}