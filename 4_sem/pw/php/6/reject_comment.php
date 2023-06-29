<?php

session_start();

$db = new SQLite3("data.db");

switch ($_SERVER["REQUEST_METHOD"]) {
	case "POST": {
		if (
			// logged in
			   array_key_exists("logged_in", $_SESSION)
			&& $_SESSION["logged_in"]
			// csrf token
			&& array_key_exists("csrf_token", $_SESSION)
			&& array_key_exists("csrf_token", $_POST)
			&& $_SESSION["csrf_token"] === $_POST["csrf_token"]
		) {
			$statement = $db->prepare(
				"DELETE FROM Comment WHERE id = ?"
			);
			$statement->bindValue(1, (int) $_POST["id"], SQLITE3_INTEGER);
			$statement->execute();

			header("Location: {$_POST['back']}", true, 303);
		}
	}
}

?>
