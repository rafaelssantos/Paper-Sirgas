<?php 





class StationsManager {
	private static $instance;
	private $stations;




	public function getStations(){
		if(!isset($stations)){
			$stations = $this->loadDefault();
		}

		return $stations;
	}




	public function loadDefault(){
		$station['lat'] = -22.119905;
		$station['long'] = -51.408534;
		$station['name'] = "PPTE";
		$station['status'] = true;
		$stations[]  = $station;

		$station['lat'] = -22.523304;
		$station['long'] = -52.952088;
		$station['name'] = "ROSA";
		$station['status'] = false;
		$stations[]  = $station;

		$station['lat'] = -21.184666;
		$station['long'] = -50.439788;
		$station['name'] = "SPAR";
		$station['status'] = true;
		$stations[]  = $station;

		$station['lat'] = -21.461604;
		$station['long'] = -51.554257;
		$station['name'] = "SPDR";
		$station['status'] = false;
		$stations[]  = $station;

		$station['lat'] = -21.929118;
		$station['long'] = -50.49237;
		$station['name'] = "SPTU";
		$station['status'] = true;
		$stations[]  = $station;

		// file_put_contents("/home/rafaelssantos/teste/json", json_encode($station));
		return $stations;
	}




	public function loadFromJson($filePathJson){
	}	




	public function updateStatus($statusFilePath) {
	}



    private function __construct() {
        
    }
 


    public static function getInstance() {
        if (is_null(static::$instance)) {
            static::$instance = new StationsManager();            
        }
 
        return static::$instance;
    }
}
 




 ?>
