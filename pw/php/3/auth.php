<?php
session_start();

$db = new SQLite3("data.db");

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
			"SELECT id, name, password FROM Teacher WHERE name = ?"
		);
		$statement->bindValue(1, $post_name, SQLITE3_TEXT);
		$result = $statement->execute();
		$row = $result->fetchArray();
		if ($row !== false) {
			if ($row["password"] === $post_password) {
				$_SESSION["logged_in"] = true;
			} else {
				echo "wrong password";
			}
		} else {
			echo "wrong name";
		}
	} else if (
		$_POST["request"] === "log_out"
	) {
		session_unset();
		session_destroy();
	} else if (
		$_POST["request"] === "submit_grade"
		&&
		array_key_exists("logged_in", $_SESSION)
		&&
		$_SESSION["logged_in"]
		&&
		array_key_exists("student_id", $_POST)
		&&
		array_key_exists("subject_id", $_POST)
		&&
		array_key_exists("grade", $_POST)
	) {
		$post_student_id = (int) $_POST["student_id"];
		$post_subject_id = (int) $_POST["subject_id"];
		$post_grade = (float) $_POST["grade"];

		$statement = $db->prepare(
			"INSERT OR REPLACE INTO Grade(student_id, subject_id, value) VALUES (?, ?, ?)"
		);
		$statement->bindValue(1, $post_student_id, SQLITE3_INTEGER);
		$statement->bindValue(2, $post_subject_id, SQLITE3_INTEGER);
		$statement->bindValue(3, $post_grade, SQLITE3_FLOAT);
		$statement->execute();
	}
}

?>

<?php
if (
	array_key_exists("logged_in", $_SESSION)
	&&
	$_SESSION["logged_in"]
) {
?>

<!DOCTYPE html>
<html>
<body>

<h1>loged in</h1>
<form method="POST">
	<input type="hidden" name="request" value="log_out">
	<input type="submit" value="Log Out">
</form>

<br>

<form method="POST">
	<input type="hidden" name="request" value="submit_grade">
	<label for="subject_id">Subject</label>
	<select id="subject_id" name="subject_id">
		<?php
			$statement = $db->prepare(
				"SELECT id, name FROM Subject"
			);
			$result = $statement->execute();
		?>
    <?php while ($row = $result->fetchArray()) { ?>
			<option value="<?php echo $row["id"] ?>"> <?php echo $row["name"] ?> </option>
		<?php } ?>
	</select>
	<br>
	<label for="student_id">Student</label>
	<select id="student_id" name="student_id">
		<?php
			$statement = $db->prepare(
				"SELECT id, name FROM Student"
			);
			$result = $statement->execute();
		?>
    <?php while ($row = $result->fetchArray()) { ?>
			<option value="<?php echo $row["id"] ?>"> <?php echo $row["name"] ?> </option>
		<?php } ?>
	</select>
	<br>
	<input type="number" name="grade">
	<br>
	<input type="submit" value="Submit">
</form>

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

<?php
	$statement = $db->prepare(
		"SELECT"
		. "  Student.id 'student_id'"
		. ", Student.name 'student_name'"
		. ", Subject.id 'subject_id'"
		. ", Grade.value 'grade'"
		. " FROM Grade"
		. " FULL OUTER JOIN Student ON Student.id = Grade.student_id"
		. " FULL OUTER JOIN Subject ON Subject.id = Grade.subject_id"
		. " ORDER BY Student.name"
	);
	$result = $statement->execute();

	$grades = array();
	while ($row = $result->fetchArray()) {
		$student_id = (int) $row["student_id"];
		$subject_id = (int) $row["subject_id"];
		$student_name = $row["student_name"];
		if (!is_null($row["student_id"])) {
			if (!array_key_exists($student_id, $grades)) {
				$grades[$student_id] = array();
				$grades[$student_id]["grades"] = array();
				$grades[$student_id]["student_name"] = $student_name;
			}
			if (!is_null($row["subject_id"])) {
				$grades[$student_id]["grades"][$subject_id] = (float) $row["grade"];
			}
		}
	}
?>

<?php
	$statement = $db->prepare(
		"SELECT id, name FROM Subject ORDER BY name"
	);
	$result = $statement->execute();

	$subjects = array();
	while ($row = $result->fetchArray()) {
		array_push($subjects, $row);
	}
?>

<table>
	<thead>
		<th>Name</th>
		<?php foreach ($subjects as $subject) { ?>
			<th> <?php echo $subject["name"] ?> </th>
		<?php } ?>
	</thead>
	<tbody>
		<?php foreach ($grades as $student_id => $grade) { ?>
			<tr>
				<td> <?php echo $grade["student_name"] ?> </td>
				<?php foreach ($subjects as $subject) { ?>
					<td>
						<?php
							if (array_key_exists($subject["id"], $grade["grades"])) {
								echo $grade["grades"][$subject["id"]];
							} else {
								echo "N/A";
							}
						?>
					</td>
				<?php } ?>
			</tr>
		<?php } ?>
	</tbody>
</table>

</body>
</html>
	
<?php } ?>

