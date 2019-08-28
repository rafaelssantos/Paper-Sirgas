<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        
        <title>Integrity Monitoring</title>
        
        <link rel="stylesheet" href="css/reset.css">
        <link rel="stylesheet" href="css/main.css">
        <link rel="stylesheet" href="https://unpkg.com/leaflet@1.5.1/dist/leaflet.css" integrity="sha512-xwE/Az9zrjBIphAcBb3F6JVqxf46+CDLwfLMHloNu6KEQCAWi6HcDUbeOfBIptF7tcCzusKFjFw2yuvEpDL9wQ==" crossorigin=""/> 
        <link href="javascript/lib/c3-0.7.8/c3.min.css " rel="stylesheet">
   

		
        <script src="javascript/jquery/jquery-3.4.1.min.js"></script>
        <script src="javascript/lib/leaflet.js"></script>
        <script src="javascript/lib/d3-5.11.0/d3.min.js" charset="utf-8"></script>
        <script src="javascript/lib/c3-0.7.8/c3.min.js"></script>
        <script src="javascript/monitor.js"></script>

    </head>
    




    <body>
        <div class='header'>
            <img class='logo' src="images/unesp.jpg">
        </div>
        <div class='split-container'>
            <div class='left'>
                <div id="stations-map"></div>
            </div>
            <div class='right'>
   
            </div>
        </div>
        
        <div class='chart-container'>
            <div class='toolbar'>
                <select id='cbStation'>
                    <option value='PPTE0'>PPTE0</option>
                    <option value='ROSA0'>ROSA0</option>
                    <option value='SPAR0'>SPAR0</option>
                    <option value='SPDR0'>SPDR0</option>
                    <option value='SPTU0'>SPTU0</option>
                </select>
            </div>
            <div id='neu-chart'>

            </div>
        </div>
    </body>
</html>