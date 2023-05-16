<?php

$db = new SQLite3("data.db");

switch ($_SERVER["REQUEST_METHOD"]) {
	case "POST": {
		$statement = $db->prepare(
			"INSERT INTO Comment(name, content, approval_state) VALUES (?, ?, 0)"
		);
		$statement->bindValue(1, $_POST["name"], SQLITE3_TEXT);
		$statement->bindValue(2, $_POST["content"], SQLITE3_TEXT);
		$statement->execute();

		header("Location: {$_POST['back']}", true, 303);
	}
}

?>
