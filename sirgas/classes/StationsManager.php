<?php 





class StationsManager {
	
	private static $instance;



	public function loadDefault(){
		$station['lat'] = -22.119905;
		$station['long'] = -51.408534;
		$station['name'] = "PPTE";
		$station['status'] = true;
		$stations[]  = $station;

		$station['lat'] = -21.929118;
		$station['long'] = -50.49237;
		$station['name'] = "SPTU";
		$station['status'] = true;
		$stations[]  = $station;

		return $stations;
	}



	public function loadFromJson($filePathJson){
	}	



	public function updateStatus($stations, $statusFilePath) {

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
