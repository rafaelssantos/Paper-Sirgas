function updateChart(){

    $.ajax({
        type: "POST", 
        url: 'serv-retrive-neu.php',
        async: 'false',
        datatype: 'json',
        contentType: "application/json; charset=utf-8",
        cache: false,
        success: function(neuData) {
            var parsedNeuData = JSON.parse(neuData);

            var chart = c3.generate({
                bindto: "#neu-chart",
                data: {
                    json: parsedNeuData[localStorage['stationLabel']],
                    keys: {
                        x: 'datetime', // it's possible to specify 'x' when category axis
                        value: ['north', 'east', 'up']
                    }
                },
                axis: {
                    x: {
                        type: 'category',
                        tick: {
                            fit: false,
                            rotate: -45,
                            multiline: false
                        }
                    }
                }
            });
        }
    });

}





function updateMap(){
    /* Coordenadas centrais do estado de SP */
    var latSP = -22.3154;               //latitude centro de SP (Bauru)
    var longSP = -49.0615;      //longitude centro de SP (Bauru)

    if(window.map == undefined){
        window.map = L.map('stations-map').setView([latSP, longSP], 6.75);

        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw', {
            maxZoom: 18,
            attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' + '<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' + 'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
            id: 'mapbox.streets'
        }).addTo(window.map);

        L.control.scale().addTo(window.map);
    }

    window.layer = L.layerGroup();
    window.layer.addTo(window.map);

    var CustomIcon = L.Icon.extend({});
    // var suitableStIcon = new CustomIcon({iconUrl: 'images/marker-suitable.png'});
    // var notSuitableStIcon = new CustomIcon({iconUrl: 'images/marker-not-suitable.png'});

    var suitableStIcon= new L.icon({
        iconUrl: 'images/marker-suitable.png',
        iconAnchor: [10, 41]
        // popupAnchor: [0, -41]
    });


    var notSuitableStIcon= new L.icon({
        iconUrl: 'images/marker-not-suitable.png',
        iconAnchor: [10, 41]
        // popupAnchor: [0, -41]
    });


    
}


function refresh(){
    // updateMap();
    updateChart();


    window.timer = setTimeout(function(){
        if(window.layer != undefined){
            window.layer.remove();
        }
     // updateMap();
        updateChart();
    }, 5000);
}




$(document).ready(function(){
    if(localStorage['stationLabel'] == undefined){
        localStorage['stationLabel'] = "PPTE0";
    }

    $("#cbStation").val(localStorage['stationLabel']);

    $("#cbStation").change(function(){
        localStorage['stationLabel'] = $(this).children("option:selected").val();
        clearTimeout(window.timer);
        refresh();
    });

    refresh();
});