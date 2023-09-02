<?php
$servername = "localhost:3306";
$username = "root";
$password = "Ashin!1234";
$dbname = "Dev_Schema";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "Call GetAllBooks";
$result = $conn->query($sql);

echo json_encode($result->fetch_all(MYSQLI_ASSOC)), "\n";
//$mysqli->next_result();
// here we go - the next query works!
//$next_query = $mysqli->query("SELECT 'next' as `from` from dual");
//echo json_encode($next_query->fetch_assoc()), "\n";

$conn->close();
?>
