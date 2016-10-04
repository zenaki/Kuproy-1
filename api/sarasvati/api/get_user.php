<?php
	// error_reporting(E_ALL);
	// ini_set('display_errors', 1);

    include 'koneksi.php';
   	
	$statement=$pdo->prepare("SELECT * FROM user");
	$statement->execute();
	$results=$statement->fetchAll(PDO::FETCH_ASSOC);
	$json=json_encode($results);
	echo $json;
?>