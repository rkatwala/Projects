<?php
$result = "";
$error = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $number1 = $_POST['number1'];
    $number2 = $_POST['number2'];

    // Execute the Python script to multiply numbers
    $command = "python3 multiply.py " . escapeshellarg($number1) . " " . escapeshellarg($number2) . " 2>&1";
    $result = shell_exec($command);
    
    if (!$result) {
        $error = "There was an error executing the Python script.";
    }
}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Multiplication Using Python</title>
</head>
<body>

<nav>
    <a href="HomeWebsite.php">Home</a>
    <a href="AddingToDataBase.php">Insert Data</a>
    <a href="MultiplyPage.php">Multiplication Calculator</a>
</nav>

<h2>Multiplication using Python</h2>
<form action="" method="post">
    Number 1: <input type="text" name="number1" required><br><br>
    Number 2: <input type="text" name="number2" required><br><br>
    <input type="submit" value="Multiply">
</form>

<footer>
    <a href="HomeWebsite.php">Home</a>
    <a href="AddingToDataBase.php">Insert Data</a>
    <a href="MultiplyPage.php">Multiplication Calculator</a>
</footer>


<?php
if ($error) {
    echo "<h3>Error: $error</h3>";
} elseif ($result !== "") {
    echo "<h3>Result: $result</h3>";
}
?>

</body>
</html>

