<?php
	error_reporting(E_ALL);
	ini_set('display_errors', 1);
    
    include 'koneksi.php';

    // $format = strtolower($_GET['format']) == 'json' ? 'json' : 'xml'; //xml is the default
    // $get = @$_GET['get'];
    // $username = @$_GET['username'];
    // $password = @$_GET['password'];
    // echo $get . ' ' . $username . ' ' . $password;
    // return;

    if (isset($_GET['get'])) {
        $format = (isset($_GET['format']) == 'json') ? 'json' : 'xml'; //xml is the default
        $get = $_GET['get'];
        if ($get == 'user') {
            // echo $get . ' ' . $format;
            $statement = $pdo->prepare("SELECT * FROM $get");
            $statement->execute();
            $results = $statement->fetchAll(PDO::FETCH_ASSOC);
            if($statement->rowCount() > 0) {
                // echo $format;
                if($format == 'json') {
                    header('Content-type: application/json');
                    echo json_encode(array('Sarasvati'=> $results), JSON_PRETTY_PRINT);
                    // echo json_encode(array('Sarasvati'=> $results));
                } else {
                    header('Content-Type: text/xml');
                    $xml = new SimpleXMLElement('<Sarasvati />');
                    foreach ($results as $key) {
                        $user = $xml->addChild('User');
                        $user->addAttribute('id', $key['id']);
                        $user->addChild('username', $key['username']);
                        $user->addChild('password', $key['password']);
                    }
                    echo $xml->asXML();
                }
            }
        } else if ($get == 'environment') {
            // echo $get;
            if (isset($_GET['api_key'])) {
                $api_key = $_GET['api_key'];
                $statement = $pdo->prepare("
                    SELECT 
                        $get.id,
                        $get.module_name,
                        $get.serial_number,
                        round($get.latitude,9) latitude,
                        round($get.longitude,9) longitude,
                        $get.server,
                        $get.file,
                        $get.web_client,
                        $get.interval,
                        gsm.operator,
                        gsm.device_name,
                        gsm.status,
                        gsm.communication,
                        gsm.number,
                        gsm.apn,
                        gsm.username,
                        gsm.password
                    FROM 
                        $get, user , gsm
                    WHERE 
                        $get.id_user = user.id AND
                        $get.id = gsm.id_env AND
                        user.api_key = '$api_key'
                ");
                $statement->execute();
                $results = $statement->fetchAll(PDO::FETCH_ASSOC);
                // $results = $statement->fetch(PDO::FETCH_LAZY);
                // $results = $statement->fetchAll(PDO::FETCH_OBJ);
                // echo "<pre>";
                // var_dump($results);
                // // echo count($results[1]);
                // echo "</pre>";
                // return;
                $result = array(); $module_c = -1; $gsm_c = 0; $var_id = 0;
                for ($i = 0; $i < count($results); $i++) {
                    if ($results[$i]["id"] == $var_id) {
                        // echo $var_id . " sama";
                        $gsm_c++;
                        $result["env"][$module_c]["gsm"][$gsm_c]["operator"] = $results[$i]["operator"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["device_name"] = $results[$i]["device_name"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["status"] = $results[$i]["status"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["communication"] = $results[$i]["communication"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["number"] = $results[$i]["number"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["apn"] = $results[$i]["apn"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["username"] = $results[$i]["username"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["password"] = $results[$i]["password"];
                    } else {
                        $var_id = $results[$i]["id"];
                        // echo $var_id;
                        $module_c++; $gsm_c = 0;
                        $result["env"][$module_c]["id"] = $results[$i]["id"];
                        $result["env"][$module_c]["module_name"] = $results[$i]["module_name"];
                        $result["env"][$module_c]["serial_number"] = $results[$i]["serial_number"];
                        $result["env"][$module_c]["latitude"] = $results[$i]["latitude"];
                        $result["env"][$module_c]["longitude"] = $results[$i]["longitude"];
                        $result["env"][$module_c]["server"] = $results[$i]["server"];
                        $result["env"][$module_c]["file"] = $results[$i]["file"];
                        $result["env"][$module_c]["web_client"] = $results[$i]["web_client"];
                        $result["env"][$module_c]["interval"] = $results[$i]["interval"];

                        $result["env"][$module_c]["gsm"][$gsm_c]["operator"] = $results[$i]["operator"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["device_name"] = $results[$i]["device_name"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["status"] = $results[$i]["status"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["communication"] = $results[$i]["communication"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["number"] = $results[$i]["number"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["apn"] = $results[$i]["apn"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["username"] = $results[$i]["username"];
                        $result["env"][$module_c]["gsm"][$gsm_c]["password"] = $results[$i]["password"];
                    }
                }
                // echo "<pre>";
                // var_dump($result);
                // echo "</pre>";
                // return;
                if($statement->rowCount() > 0) {
                    if($format == 'json') {
                        header('Content-type: application/json');
                        echo json_encode(array('Sarasvati'=> $result), JSON_PRETTY_PRINT);
                        // echo json_encode(array('Sarasvati'=> $results));
                    } else {
                        header('Content-Type: text/xml');
                        $xml = new SimpleXMLElement('<Sarasvati />');
                        foreach ($result['env'] as $env_key) {
                            $env = $xml->addChild('Environment');
                            $env->addChild('module_name', $env_key['module_name']);
                            $env->addChild('serial_number', $env_key['serial_number']);
                            $env->addChild('latitude', $env_key['latitude']);
                            $env->addChild('longitude', $env_key['longitude']);
                            $env->addChild('server', $env_key['server']);
                            $env->addChild('file', $env_key['file']);
                            $env->addChild('web_client', $env_key['web_client']);
                            $env->addChild('interval', $env_key['interval']);

                            foreach ($env_key['gsm'] as $gsm_key) {
                                $gsm = $env->addChild('GSM', '');
                                $gsm->addChild('operator', $gsm_key['operator']);
                                $gsm->addChild('device_name', $gsm_key['device_name']);
                                $gsm->addChild('status', $gsm_key['status']);
                                $gsm->addChild('communication', $gsm_key['communication']);
                                $gsm->addChild('number', $gsm_key['number']);
                                $gsm->addChild('apn', $gsm_key['apn']);
                                $gsm->addChild('username', $gsm_key['username']);
                                $gsm->addChild('password', $gsm_key['password']);
                            }
                        }
                        echo $xml->asXML();
                    }
                }
            }
        } else if ($get == 'data') {
            // echo $get;
            if (isset($_GET['api_key'])) {
                $api_key = $_GET['api_key'];
                // $id = $_GET['id'];
                $statement = $pdo->prepare("
                    SELECT 
                        environment.id,
                        $get.register,
                        $get.value
                    FROM $get, environment, user 
                    WHERE environment.id_user = user.id AND
                        user.api_key = '$api_key' AND
                        environment.id = $get.id_env
                ");
                $statement->execute();
                $results = $statement->fetchAll(PDO::FETCH_ASSOC);
                // echo "<pre>";
                // var_dump($results);
                // // echo count($results[1]);
                // echo "</pre>";
                // return;
                $result = array(); $module_c = -1; $id_tu = 0; $var_id = 0;
                for ($i = 0; $i < count($results); $i++) {
                    if ($results[$i]["id"] == $var_id) {
                        // echo $var_id . " sama";
                        // echo " => ".$results[$i]["register"]."</br>";
                        $id_tu++;
                        // $result[$module_c][$var_id][$id_tu]["register"] = $results[$i]["register"];
                        // $result[$module_c][$var_id][$id_tu]["value"] = $results[$i]["value"];
                        $result["data"][$module_c]["titik_ukur"][$id_tu]["register"] = $results[$i]["register"];
                        $result["data"][$module_c]["titik_ukur"][$id_tu]["value"] = $results[$i]["value"];
                    } else {
                        $var_id = $results[$i]["id"];
                        // echo $var_id;
                        // echo " => ".$results[$i]["register"]."</br>";
                        $module_c++; $id_tu = 0;
                        $result["data"][$module_c]["id"] = $var_id;
                        // $result[$module_c][$var_id][$id_tu]["register"] = $results[$i]["register"];
                        // $result[$module_c][$var_id][$id_tu]["value"] = $results[$i]["value"];
                        $result["data"][$module_c]["titik_ukur"][$id_tu]["register"] = $results[$i]["register"];
                        $result["data"][$module_c]["titik_ukur"][$id_tu]["value"] = $results[$i]["value"];
                        
                    }
                }
                // echo "<pre>";
                // var_dump($result);
                // echo "</pre>";
                // return;
                if($statement->rowCount() > 0) {
                    if($format == 'json') {
                        header('Content-type: application/json');
                        echo json_encode(array('Sarasvati'=> $result), JSON_PRETTY_PRINT);
                        // echo json_encode(array('Sarasvati'=> $results));
                    } else {
                        header('Content-Type: text/xml');
                        $xml = new SimpleXMLElement('<Sarasvati />');
                        foreach ($result['data'] as $key) {
                            $data = $xml->addChild('data');
                            $data->addAttribute('ID', $key['id']);
                            foreach ($key['titik_ukur'] as $data_key) {
                                $data_val = $data->addChild('titik_ukur', '');
                                $data_val->addAttribute('register', $data_key['register']);
                                $data_val->addAttribute('value', $data_key['value']);
                            }
                        }
                        echo $xml->asXML();
                    }
                }
            }
        } else {
            echo 'username dan password masih kosong';
        }
    }
?>