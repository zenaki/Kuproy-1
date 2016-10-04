<?php  
$servername = "localhost";
$username = "root";
$password = "root";
$database = "sarasvati";

try {
	$pdo = new PDO("mysql:host=$servername;dbname=$database", $username, $password);
} catch (Exception $ex) {
	echo $ex->getMessage();
}
?>
