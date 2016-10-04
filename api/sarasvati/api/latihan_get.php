<?php
	error_reporting(E_ALL);
	ini_set('display_errors', 1);

	// include 'koneksi.php';

	if (isset($_GET['get'])) {
		$get = $_GET['get'];
		// echo $get;
		if ($get == 'user') {
			echo $get;
		} else if ($get == 'environment') {
			echo $get;
			// if (isset($_GET['username']) && isset($_GET['password']) {
   //              $username = $_GET['username'];
   //              $password = $_GET['password'];
   //              echo 'username = ' . $username . ' password = ' $password;
   //          } else {
   //          	echo $get . ' tetapi belum ada username dan password';
   //          }
		} else {
			echo 'bukan user dan bukan environment';
		}
	} else {
		echo 'kosong';
	}
?>