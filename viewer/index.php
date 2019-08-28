<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        
        <title>Integrity Monitoring</title>
        
        <link rel="stylesheet" href="css/reset.css">
        <link rel="stylesheet" href="css/integrity.css">
		<!-- leaftlet css -->
		<link rel="stylesheet" href="https://unpkg.com/leaflet@1.5.1/dist/leaflet.css" integrity="sha512-xwE/Az9zrjBIphAcBb3F6JVqxf46+CDLwfLMHloNu6KEQCAWi6HcDUbeOfBIptF7tcCzusKFjFw2yuvEpDL9wQ==" crossorigin=""/>

        <!-- sp-map js -->
        <link rel="stylesheet" href="css/sp-map.css">
		
        <!-- jquery 3.4.1 -->
        <script src="javascript/jquery/jquery-3.4.1.min.js"></script>

        <!-- leaflet js -->
        <script src="javascript/lib/leaflet.js"></script>
    
        <!-- Load c3.css -->
        <link href="javascript/lib/c3-0.7.8/c3.min.css " rel="stylesheet">

        <!-- Load d3.js and c3.js -->
        <script src="javascript/lib/d3-5.11.0/d3.min.js" charset="utf-8"></script>
        <script src="javascript/lib/c3-0.7.8/c3.min.js"></script>
    </head>
    




    <body>
        <div class='header'>
            <img class='logo' src="images/unesp.jpg">
        </div>
        <div class='split-container'>
            <div class='left'>

            </div>
            <div class='right'>

            </div>
        </div>
    	<div id="sirgas-map"></div>
        <div class='spacer'></div>

        <div class='side-panel'>
            <h1>Indicadores de Integridade</h1>
            <div class='station-panel'>
                <h2>PPTE</h2>
                X = 3687624,367m <span>σ = 0,23m</span> <br>
                Y = -4620818,682m <span>σ = 0,21m</span> <br>
                Z = -2386880,380m <span>σ = 0,15m</span> <br>
                Status: OK <br>
            </div>
            <div class='station-panel'>
                <h2>ROSA</h2>
                X = 3551520,485m <span>σ = 0,26m</span> <br>
                Y = -4704836,112m <span>σ = 0,6m</span> <br>
                Z = -2428155,731m <span>σ = 0,13m</span> <br>
                Status: <em>WARNING</em> <br>
            </div>
            <div class='station-panel'>
                <h2>SPAR</h2>
                X = 3789545,410m <span>σ = 0,30m</span> <br>
                Y = -4587255,757m <span>σ = 0,12m</span> <br>
                Z = -2290619,365m <span>σ = 0,23m</span> <br>
                Status: OK <br>
            </div>
            <div class='station-panel'>
                <h2>SPDR</h2>
                X = 3692649,658m <span>σ = 0,16m</span> <br>
                Y = -4651331,119m <span>σ = 0,13m</span> <br>
                Z = -2319169,961m <span>σ = 0,12m</span> <br>
                Status: <em>WARNING</em> <br>
            </div>
            <div class='station-panel'>
                <h2>SPTU</h2>
                X = 3766123,314m <span>σ = 0,24m</span> <br>
                Y = -4567433,465m <span>σ = 0,07m</span> <br>
                Z = -2367323,834m <span>σ = 0,05m</span> <br>
                Status: OK <br>
            </div>
        </div>

        <div id="chart" style="width: 100%; height: 400px"></div>
        <script src="javascript/sp-map.js"></script>
    </body>
</html>