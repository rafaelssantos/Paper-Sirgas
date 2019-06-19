function updateMap(map){
    /* Coordenadas centrais do estado de SP */
    var latSP = -22.3154;               //latitude centro de SP (Bauru)
    var longSP = -49.0615;      //longitude centro de SP (Bauru)

    if(map === null){
        map = L.map('sirgas-map').setView([latSP, longSP], 6.75);

        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw', {
            maxZoom: 18,
            attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, ' + '<a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' + 'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
            id: 'mapbox.streets'
        }).addTo(map);
    }

    var layer = L.layerGroup();
    layer.addTo(map);

    var CustomIcon = L.Icon.extend({});
    var suitableStIcon = new CustomIcon({iconUrl: 'images/marker-suitable.png'});
    var notSuitableStIcon = new CustomIcon({iconUrl: 'images/marker-not-suitable.png'});




    $.ajax({
        type: "GET", 
        url: 'retrieve-stations.php',
        timeout: 3000,
        datatype: 'json',
        contentType: "application/json; charset=utf-8",
        cache: false,
        success: function(data) {
            var stations = JSON.parse(data);

            // Listando cada cliente encontrado na lista...
            $.each(stations, function(i, station){
                L.marker([station.lat, station.long], {icon: suitableStIcon}).bindPopup(station.name).addTo(layer);
            });
            console.log("OK");

            setTimeout(function(){
                layer.remove();
                updateMap(map);
            }, 2000);
        } 
    });
}




$(function () {
    updateMap(null);
});