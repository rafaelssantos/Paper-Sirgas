<?php 
	require_once ('classes/StationsManager.php');

	$stations = array();
	if(file_exists("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/PPTE0.json")){
		$stations["PPTE0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/PPTE0.json");
	}

	if(file_exists("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/ROSA0.json")){
		$stations["ROSA0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/ROSA0.json");
	}

	if(file_exists("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/SPAR0.json")){
		$stations["SPAR0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/SPAR0.json");
	}

	if(file_exists("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/SPDR0.json")){
		$stations["SPDR0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/SPDR0.json");
	}

	if(file_exists("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/SPTU0.json")){
		$stations["SPTU0"] = StationsManager::getInstance()->getJsonData("/home/rafaelssantos/workspaces/git/github/paper-sirgas/json/SPTU0.json");
	}

	echo json_encode($stations);
 ?>