<?php 
	require_once ('classes/StationsManager.php');
	$stations = array();
	
	$stations["PPTE0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/PPTE0.json");
	// $stations["ROSA0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/ROSA0.json");


	echo json_encode($stations);
 ?>