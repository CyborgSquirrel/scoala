<?php

session_start();

$db = new SQLite3("data.db");

switch ($_SERVER["REQUEST_METHOD"]) {
	case "POST": {
		if (
			   array_key_exists("logged_in", $_SESSION)
			&& $_SESSION["logged_in"]
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
