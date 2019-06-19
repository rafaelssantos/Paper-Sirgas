<?php 
	require_once ('classes/StationsManager.php');

	$stations = StationsManager::getInstance()->getStations();

	
	
	echo json_encode($stations)
	
 ?>