<?php
	// error_reporting(E_ALL);
	// ini_set('display_errors', 1);
    
    include 'koneksi.php';
    
    $format = strtolower($_GET['format']) == 'json' ? 'json' : 'xml'; //xml is the default

	$statement = $pdo->prepare("SELECT * FROM environment");
	$statement->execute();
	$results = $statement->fetchAll(PDO::FETCH_ASSOC);

    if($statement->rowCount() > 0) {
        if($format == 'json') {
            header('Content-type: application/json');
            echo json_encode(array('Sarasvati'=> $results));
        } else {
            header('Content-Type: text/xml');
            $xml = new SimpleXMLElement('<Sarasvati />');
            foreach ($results as $key) {
                $env = $xml->addChild('Environment');
                // $user->addAttribute('id', $key['id']);
                // $user->addAttribute('username', $key['username']);
                // $user->addAttribute('password', $key['password']);
                // $user->addAttribute('username', $key['username']);
                $env->addChild('id', $key['id']);
                $env->addChild('id_user', $key['id_user']);
                $env->addChild('module_name', $key['module_name']);
                $env->addChild('serial_number', $key['serial_number']);
                $env->addChild('latitude', $key['latitude']);
                $env->addChild('longitude', $key['longitude']);
                $env->addChild('create_by', $key['create_by']);
                $env->addChild('update_by', $key['update_by']);
                $env->addChild('create_date', $key['create_date']);
                $env->addChild('update_date', $key['update_date']);
            }
            echo $xml->asXML();
        }
    }
?>