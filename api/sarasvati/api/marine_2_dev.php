<?php
	error_reporting(E_ALL);
	ini_set('display_errors', 1);

	$servername = "localhost";
	$username = "root";
	$password = "root";
	$database = "sarasvati";

	$pdo = new PDO("mysql:host=$servername;dbname=$database", $username, $password);
	$statement = $pdo->prepare("SELECT * FROM user");
	$result = $statement->fetchAll(PDO::FETCH_ASSOC);
	echo "<pre>";
	var_dump($result);
	echo "<pre>";
	// return;
?>