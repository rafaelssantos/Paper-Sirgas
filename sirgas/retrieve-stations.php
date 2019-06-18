<?php 
	require_once ('classes/StationsManager.php');

	$stations = StationsManager::getInstance()->loadDefault();
	
	echo json_encode($stations)
	
 ?>