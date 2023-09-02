<?php
$servername = "localhost:3306";
$username = "root";
$password = "Rahul1245";
$dbname = "Dev_Schema";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $firstname = $_POST['firstname'];
    $lastname = $_POST['lastname'];
    $email = $_POST['email'];

    $sql = "INSERT INTO MyGuests (firstname, lastname, email) VALUES ('$firstname', '$lastname', '$email')";
    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully<br>";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Insert and Display Data</title>
    <style>
        footer {
            background-color: #f1f1f1;
            padding: 10px;
            text-align: center;
            margin-top: 50px;
        }
        nav {
            background-color: #333;
            overflow: hidden;
        }
        nav a {
            float: left;
            display: block;
            color: white;
            text-align: center;
            padding: 14px 16px;
            text-decoration: none;
        }
        nav a:hover {
            background-color: #ddd;
            color: black;
        }
    </style>
</head>
<body>

<nav>
    <a href="HomeWebsite.php">Home</a>
    <a href="AddingToDataBase.php">Insert Data</a>
    <a href="MultiplyPage.php">Multiplication Calculator</a>
</nav>

<form action="" method="post">
    Firstname: <input type="text" name="firstname"><br>
    Lastname: <input type="text" name="lastname"><br>
    Email: <input type="text" name="email"><br>
    <input type="submit" value="Insert">
</form>

<?php
// Retrieve and display all data
$sql = "SELECT id, firstname, lastname, email, reg_date FROM MyGuests";
$result = $conn->query($sql);

// Open or create the sample.txt file for writing
$file = fopen("sample.txt", "w");

if ($result->num_rows > 0) {
    echo "<table border='1'><tr><th>ID</th><th>Firstname</th><th>Lastname</th><th>Email</th><th>Registration Date</th></tr>";

    // Write the header to the sample.txt
    fwrite($file, "ID\tFirstname\tLastname\tEmail\tRegistration Date\n");

    while($row = $result->fetch_assoc()) {
        echo "<tr><td>" . $row["id"]. "</td><td>" . $row["firstname"]. "</td><td>" . $row["lastname"]. "</td><td>" . $row["email"]. "</td><td>" . $row["reg_date"]. "</td></tr>";

        // Write each row's data to sample.txt
        fwrite($file, $row["id"]. "\t" . $row["firstname"]. "\t" . $row["lastname"]. "\t" . $row["email"]. "\t" . $row["reg_date"]. "\n");
    }
    echo "</table>";
} else {
    echo "0 results";
    // In case of no results, write this to the sample.txt
    fwrite($file, "No results.");
}

// Close the file after writing
fclose($file);

$conn->close();

?>

<footer>
    <a href="HomeWebsite.php">Home</a>
    <a href="AddingToDataBase.php">Insert Data</a>
    <a href="MultiplyPage.php">Multiplication Calculator</a>
</footer>

</body>
</html>



<?php
// Retrieve and display all data
$sql = "SELECT id, firstname, lastname, email, reg_date FROM MyGuests";
$result = $conn->query($sql);

// Open or create the sample.txt file for writing
$file = fopen("sample.txt", "w");

if ($result->num_rows > 0) {
    echo "<table border='1'><tr><th>ID</th><th>Firstname</th><th>Lastname</th><th>Email</th><th>Registration Date</th></tr>";

    // Write the header to the sample.txt
    fwrite($file, "ID\tFirstname\tLastname\tEmail\tRegistration Date\n");

    while($row = $result->fetch_assoc()) {
        echo "<tr><td>" . $row["id"]. "</td><td>" . $row["firstname"]. "</td><td>" . $row["lastname"]. "</td><td>" . $row["email"]. "</td><td>" . $row["reg_date"]. "</td></tr>";

        // Write each row's data to sample.txt
        fwrite($file, $row["id"]. "\t" . $row["firstname"]. "\t" . $row["lastname"]. "\t" . $row["email"]. "\t" . $row["reg_date"]. "\n");
    }
    echo "</table>";
} else {
    echo "0 results";
    // In case of no results, write this to the sample.txt
    fwrite($file, "No results.");
}

// Close the file after writing
fclose($file);

$conn->close();

?>

</body>
</html>

