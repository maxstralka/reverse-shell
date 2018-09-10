
<?php
	// Setting MySQL Database parameters
	$dbhost = 'yourDB.eu-west-1.rds.amazonaws.com:3306';
	$dbuser = 'yourUsername';
	$dbpass = 'yourPassword';
	$conn = mysql_connect($dbhost, $dbuser, $dbpass);

	// Alert if MySQL connection can not be established
	if(! $conn ) {
		die('Could not connect: ' . mysql_error());
	}

	// Structure of URL to parse: /index.php?n=Peter&p=123
	// Extracting name (n) from URL
	if (isset($_GET['n'])) {
	  $username =  $_GET['n'];
	} else {
	  echo "Name not set\n";
	}

	// Extracting port number (p) from URL
	if (isset($_GET['p'])) {
		$port =  $_GET['p'];
	} else {
		echo "Port number not set\n";
	}

	// Creaing SQL Query string
	$sql = 'INSERT INTO NamesAndPorts '.
       '(username, port) '.
       'VALUES ( "'.$username.'", "'.$port.'" )';

	// Selecting shells database
	mysql_select_db('shells');

	// Send data to database
	$retval = mysql_query( $sql, $conn );
	
	// Alert if sending data did not work
	if(! $retval ) {
		die('Could not enter data: ' . mysql_error());
	}

	// Log "completed" message
	echo "OK\n";
	
	// Close mysql connection
	mysql_close($conn);
?>