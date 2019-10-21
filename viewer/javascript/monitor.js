// function updateChart(){
//     $.ajax({
//         type: "POST", 
//         url: 'serv-retrive-neu-series.php',
//         async: 'false',
//         datatype: 'json',
//         contentType: "application/json; charset=utf-8",
//         cache: false,
//         success: function(data) {
//             var epochs = JSON.parse(data);
            
//             if(window.chart == undefined){
//                 window.chart = c3.generate({
//                     bindto: "#neu-chart",
//                     data: {
//                         json: epochs[localStorage['stationLabel']],
//                         xFormat: '%Y-%m-%d %H:%M:%S', // 'xFormat' can be used as custom format of 'x'
//                         keys: {
//                             x: 'datetime', // it's possible to specify 'x' when category axis
//                             value: ['north', 'east', 'up']
//                         }
//                     },
//                     axis: {
//                         x: {
//                             // type: 'category',
//                             type: 'timeseries',
//                             tick: {
//                                 format: '%Y-%m-%d %H:%M:%S',
//                                 fit: false,
//                                 rotate: -45,
//                                 multiline: false
//                             }
//                         }
//                     }
//                  });
//             }
//             else {
//                 window.chart.unload();
//                 window.chart.flush();
//                 window.chart.load({
//                     json: epochs[localStorage['stationLabel']],
//                     keys: {
//                         x: 'datetime', // it's possible to specify 'x' when category axis
//                         value: ['north', 'east', 'up']
//                     },
//                     axis: {
//                         x: {
//                             // type: 'category',
//                             type: 'timeseries',
//                             tick: {
//                                 format: '%Y-%m-%d H:%M:%S',
//                                 fit: false,
//                                 rotate: -45,
//                                 multiline: false
//                             }
//                         }
//                     }
//                 });
//             }
//         }
//     });
// }


function updateChart(){
    $.ajax({
        type: "POST", 
        url: 'serv-retrive-neu-series.php',
        async: 'false',
        datatype: 'json',
        contentType: "application/json; charset=utf-8",
        cache: false,
        success: function(data) {
            var epochs = JSON.parse(data);
            var north = epochs[localStorage['stationLabel']].map(epoch => epoch.north).map(Number);
            var east = epochs[localStorage['stationLabel']].map(epoch => epoch.east).map(Number);
            var up = epochs[localStorage['stationLabel']].map(epoch => epoch.up).map(Number);
            var datetime = epochs[localStorage['stationLabel']].map(epoch => epoch.datetime);

            if(window.chart == undefined){
                window.chart = Highcharts.chart('neu-chart', {
                    chart: {
                        zoomType: 'xy'
                    },
                    title: {
                        text: 'Local tangent plane coordinates'
                    },
                    xAxis: [{
                        categories: datetime,
                        tickInterval: 20
                    }],
                    yAxis: [{
                        labels: {
                            format: '{value} m',
                            style: {
                                color: Highcharts.getOptions().colors[1]
                            }
                        },
                        title: {
                            text: 'Meter',
                            style: {
                                color: Highcharts.getOptions().colors[1]
                            }
                        }
                    }],

                    tooltip: {
                        shared: true
                    },

                    series: [{
                        name: 'North',
                        type: 'line',
                        data: north,
                        tooltip: {
                            pointFormat: '<span style="font-weight: bold; color: {series.color}">{series.name}</span>: <b>{point.y:.3f}m</b><br>'
                        }
                    },
                    {
                        name: 'East',
                        type: 'line',
                        data: east,
                        tooltip: {
                            pointFormat: '<span style="font-weight: bold; color: {series.color}">{series.name}</span>: <b>{point.y:.3f}m</b><br>'
                        }
                    },
                    {
                        name: 'Up',
                        type: 'line',
                        data: up,
                        tooltip: {
                            pointFormat: '<span style="font-weight: bold; color: {series.color}">{series.name}</span>: <b>{point.y:.3f}m</b><br>'
                        }
                    }]
                });
            }
            else{
                console.log("Here");
                window.chart.xAxis[0].update({categories: datetime});
                window.chart.series[0].setData(north);
                window.chart.series[1].setData(east);
                window.chart.series[2].setData(up);
            }
        }
    });
}




function updateMap(){
    /* Coordenadas centrais do estado de SP */
    var latSP = -21.5;               //latitude centro de SP (Bauru)
    var longSP = -51;      //longitude centro de SP (Bauru)

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

    var suitableStIcon= new L.icon({
        iconUrl: 'javascript/lib/leaflet/markers/marker-icon-green.png',
        iconAnchor: [10, 41]
        // popupAnchor: [0, -41]
    });


    var notSuitableStIcon= new L.icon({
        iconUrl: 'javascript/lib/leaflet/markers/marker-icon-orange.png',
        iconAnchor: [10, 41]
        // popupAnchor: [0, -41]
    });


    $.ajax({
        type: "POST", 
        url: 'serv-retrive-neu-last.php',
        async: 'false',
        datatype: 'json',
        contentType: "application/json; charset=utf-8",
        cache: false,
        success: function(data) {
            var epochs = JSON.parse(data);

            $.each(epochs, function(key, station){
        
                $("#"+ key +"-last-solution").text(station.datetime);
                if(station.status == 1){
                    $("#"+ key +"-status").text("OK"); 

                    L.marker([station.lat, station.long], {icon: suitableStIcon}).bindPopup(key).addTo(window.layer);
                }
                else{
                    $("#"+ key +"-status").text("WARNING"); 

                    L.marker([station.lat, station.long], {icon: notSuitableStIcon}).bindPopup(key).addTo(window.layer);
                }

                if(station.old == 1){
                    $("#"+key + "-tr").addClass("old-data-row");
                }
                else{
                    console.log
                    $("#"+key + "-tr").removeClass("old-data-row");
                }

                var percentage = 0;
                // console.log ($("#cbTime").val());

                var minutes = $("#cbTime").val();

                if(minutes == 30){
                    percentage = station.min30 * 100;
                }
                else if(minutes == 60){
                    percentage = station.min60 * 100;
                }
                else if(minutes == 120){
                    percentage = station.min120 * 100;
                }
                else{
                    percentage = station.minAll * 100;
                }
                percentage = percentage.toFixed(2);
                $("#" + key + "-percent").text(percentage+"%");
            });
        }
    });
}


function refresh(){
    updateMap();
    updateChart();


    window.timer = setTimeout(function(){
        if(window.layer != undefined){
            window.layer.remove();
        }
        
        refresh();
    }, 5000);
}






$(document).ready(function(){
    if(localStorage['stationLabel'] == undefined){
        localStorage['stationLabel'] = "PPTE0";
    }

    $("#cbStation").val(localStorage['stationLabel']);

    $("#cbStation").change(function(){
        localStorage['stationLabel'] = $(this).children("option:selected").val();
        window.chart.destroy();
        window.chart = null;
        clearTimeout(window.timer);
        refresh();
    });

    $("#cbTime").change(function(){
        // clearTimeout(window.timer);
        updateMap();
    });

    refresh();
});