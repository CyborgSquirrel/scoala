<?php
session_start();

$db = new SQLite3("data.db");

if (
	   !array_key_exists("logged_in", $_SESSION)
	|| !$_SESSION["logged_in"]
) {
	header('HTTP/1.0 403 Forbidden');
?>

<!DOCTYPE html>
<html>
<body>

<p>403</p>
<p>please log in bro</p>

</body>
</html>
	
<?php } else { ?>

<!DOCTYPE html>
<html>
<body>

<h1>its moderatin' time</h1>

<form method="POST" action="log_out.php">
	<input type="submit" value="Log Out">
</form>

<?php
$statement = $db->prepare(
	"SELECT id, name, content FROM Comment WHERE approval_state = 0"
);
$result = $statement->execute();
?>

<?php while ($row = $result->fetchArray()) { ?>
	<div>
		<b><?php echo htmlentities($row["name"]) ?></b>
		<p><?php echo htmlentities($row["content"]) ?></p>
		<form method="POST" action="approve_comment.php">
			<input type="hidden" name="id" value="<?php echo $row["id"] ?>">
			<input type="hidden" name="back" value="<?php echo $_SERVER["REQUEST_URI"] ?>">
			<input type="submit" value="Approve">
		</form>
		<form method="POST" action="reject_comment.php">
			<input type="hidden" name="id" value="<?php echo $row["id"] ?>">
			<input type="hidden" name="back" value="<?php echo $_SERVER["REQUEST_URI"] ?>">
			<input type="submit" value="Incinerate 🔥">
		</form>
	</div>
<?php } ?>
</div>

</body>
</html>

<?php } ?>
