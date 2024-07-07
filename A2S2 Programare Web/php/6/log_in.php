<?php
session_start();

switch ($_SERVER["REQUEST_METHOD"]) {
	case "POST": {
		if (
			   array_key_exists("username", $_POST)
			&& array_key_exists("password", $_POST)
		) {
			if (
				   $_POST["username"] === "admin"
				&& $_POST["password"] === "admin"
			) {
				$_SESSION["logged_in"] = true;
				$_SESSION["csrf_token"] = uniqid("", true);
				$_POST["csrf_token"] = $_SESSION["csrf_token"];
				header("Location: /6/moderate.php", true, 303);
			} else {
				echo "authentication error";
			}
		}
		
		break;
	}
}
?>

<!DOCTYPE html>
<html>
<body>

<form method="POST">
	<label>Username</label>
	<input type="text" name="username">
	<br>
	<label>Password</label>
	<input type="password" name="password">
	<br>
	<input type="submit" value="Log In">
</form>

</body>
</html>
