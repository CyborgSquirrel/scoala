<?php
session_start();

$db = new SQLite3("data.db");

switch ($_SERVER["REQUEST_METHOD"]) {
	case "POST": {
		if (array_key_exists("request", $_POST)) {
			if (
				$_POST["request"] === "log_in"
				&&
				array_key_exists("name", $_POST)
				&&
				array_key_exists("password", $_POST)
			) {
				$post_name = $_POST["name"];
				$post_password = $_POST["password"];
		
				$statement = $db->prepare(
					"SELECT id, name, password FROM User WHERE name = ?"
				);
				$statement->bindValue(1, $post_name, SQLITE3_TEXT);
				$result = $statement->execute();
				$row = $result->fetchArray();
				if ($row !== false) {
					if ($row["password"] === $post_password) {
						$_SESSION["logged_in"] = true;
						$_SESSION["user_id"] = (int) $row["id"];
					} else {
						echo "wrong password";
					}
				} else {
					echo "wrong name";
				}

				header("Location: {$_SERVER['REQUEST_URI']}", true, 303);
			} else if (
				$_POST["request"] === "log_out"
			) {
				session_unset();
				session_destroy();

				header("Location: {$_SERVER['REQUEST_URI']}", true, 303);
			} else if (
				$_POST["request"] === "save_image"
				&&
				$_SESSION["logged_in"]
			) {
				$user_directory = "user_images/" . $_SESSION["user_id"];
				if (!is_dir($user_directory)) {
					mkdir($user_directory, 0777, true);
				}
		
				$file = $_FILES["image"];
				$file_basename = basename($file["name"]);
				$file_destination =  $user_directory . "/" . $file_basename;
				move_uploaded_file($file["tmp_name"], $file_destination);

				header("Location: {$_SERVER['REQUEST_URI']}", true, 303);
			} else if (
				$_POST["request"] === "delete_image"
				&&
				array_key_exists("logged_in", $_SESSION)
				&&
				$_SESSION["logged_in"]
			) {
				$user_directory = "user_images/" . $_SESSION["user_id"];

				$file_name = $_POST["image_name"];
				$file_path = $user_directory . "/" . $file_name;
				unlink($file_path);

				header("Location: {$_SERVER['REQUEST_URI']}", true, 303);
			}
		}
		break;
	}
	case "GET": {
		if (
			array_key_exists("logged_in", $_SESSION)
			&&
			$_SESSION["logged_in"]
		) {
			if (array_key_exists("user_id", $_GET)) {
				$user_id = (int) $_GET["user_id"];
			} else {
				$user_id = (int) $_SESSION["user_id"];
			}
		} else {
			// gotta log in
		}
	}
}

?>

<?php if (
	array_key_exists("logged_in", $_SESSION)
	&&
	$_SESSION["logged_in"]
) { ?>

<!DOCTYPE html>
<html>

<head>
<style>

#images-container {
	column-count: 3;
}

#images-container > div {
	break-inside: avoid;
	width: 80%;
	display: block;
	margin-bottom: 10px;
	margin-left: auto;
	margin-right: auto;
}

#images-container > div > img {
	width: 100%;
	display: block;
}

</style>
</head>

<body>

<h1>logde in</h1>

<form method="POST">
	<input type="hidden" name="request" value="log_out">
	<input type="submit" value="Log Out">
</form>

<?php
	$statement = $db->prepare(
		"SELECT name FROM User WHERE id = ?"
	);
	$statement->bindValue(1, $user_id, SQLITE3_INTEGER);
	$result = $statement->execute();
	$row = $result->fetchArray();
	$user_name = $row["name"];
?>
<p>this is <?php echo htmlentities($user_name); ?>'s page</p>


<?php if ($user_id === (int) $_SESSION["user_id"]) { ?>

<h1>submit a fiel!!</h1>

<form method="POST" enctype="multipart/form-data">
	<input type="hidden" name="request" value="save_image">
	<input type="file" name="image">
	<br>
	<input type="submit" value="Save">
</form>

<?php } ?>

<h1>my files!!1</h1>

<?php
	$user_directory = "user_images/" . $user_id;
	$files = [];
	if (is_dir($user_directory)) {
		$scan = scandir($user_directory);
		foreach ($scan as $file) {
			if ($file !== "." && $file !== "..") {
				array_push($files, $file);
			}
		}
	}
?>

<div id="images-container">
	<?php foreach ($files as $file) { ?>
		<div>
			<img src="<?php echo $user_directory . "/" . $file ?>">
			<?php if ($user_id === (int) $_SESSION["user_id"]) { ?>
				<form method="POST">
					<input type="hidden" name="request" value="delete_image">
					<input type="hidden" name="image_name" value="<?php echo $file ?>">
					<input type="submit" value="Deletus">
				</form>
			<?php } ?>
		</div>
	<?php } ?>
</div>
	
</body>

</html>

<?php } else { ?>

<!DOCTYPE html>
<html>
<body>

<form method="POST">
	<input type="hidden" name="request" value="log_in">
	<label>Username</label>
	<input type="text" name="name">
	<br>
	<label>Password</label>
	<input type="password" name="password">
	<br>
	<input type="submit" value="Log In">
</form>

</body>
</html>

<?php } ?>
