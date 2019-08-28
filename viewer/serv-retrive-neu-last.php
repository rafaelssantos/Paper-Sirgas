<?php 
	require_once ('classes/StationsManager.php');
	$stations = array();
	
	$stations["PPTE0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/LAST_PPTE0.json");
	$stations["ROSA0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/LAST_ROSA0.json");
	
	$stations["SPAR0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/LAST_SPAR0.json");
	$stations["SPDR0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/LAST_SPDR0.json");
	$stations["SPTU0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/LAST_SPTU0.json");


	echo json_encode($stations);
 ?>