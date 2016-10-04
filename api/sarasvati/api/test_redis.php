<?php 
	error_reporting(E_ALL);
	ini_set('display_errors', 1);

	//Connecting to Redis server on localhost
   $redis = new Redis();
   $redis->connect('127.0.0.1', 6379);
   echo "Connection to server sucessfully";
   //check whether server is running or not
   // echo "Server is running: ".$redis->ping()."</br>";
   // $redis->lpush("tutorial-list", "Redis");
   // $redis->lpush("tutorial-list", "Mongodb");
   // $redis->lpush("tutorial-list", "Mysql");
   // Get the stored data and print it
   // $arList = $redis->lrange("tutorial-list", 0 ,5);
   $arList = $redis->keys("*");
   echo "Stored string in redis:: </br>";
   var_dump($arList);
?>