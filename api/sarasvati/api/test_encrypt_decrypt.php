<?php
	error_reporting(E_ALL);
	ini_set('display_errors', 1);

	$input = "Dendy Gema !";

	$encrypted = encryptIt( $input );
	$decrypted = decryptIt( $encrypted );

	echo 'Encrypt : ' . $encrypted . '<br />Decrypt : ' . $decrypted;

	function encryptIt( $q ) {
    	$cryptKey  = 'Test'  //'qJB0rGtIn5UB1xG03efyCp';  //
    	$qEncoded      = base64_encode( 
    		mcrypt_encrypt( 
    			MCRYPT_RIJNDAEL_256, 
    			md5( $cryptKey ), 
    			$q, 
    			MCRYPT_MODE_CBC, 
    			md5( md5( $cryptKey ) ) 
			) 
		);
    	return( $qEncoded );
	}

	function decryptIt( $q ) {
	    $cryptKey  =  'Test'  //'qJB0rGtIn5UB1xG03efyCp';  //
    	$qDecoded      = rtrim( 
    		mcrypt_decrypt( 
    			MCRYPT_RIJNDAEL_256, 
    			md5( $cryptKey ), 
    			base64_decode( $q ), 
    			MCRYPT_MODE_CBC, 
    			md5( md5( $cryptKey ) ) 
			), 
			"\0"
		);
    	return( $qDecoded );
	}
?>