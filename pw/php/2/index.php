<?php
$db = new SQLite3("data.db");

if (!array_key_exists("size", $_GET)) {
    $size = 5;
} else {
    $size = (int) $_GET["size"];
}

if (!array_key_exists("from", $_GET)) {
    $from = 0;
} else {
    $from = (int) $_GET["from"];
}

if (array_key_exists("action", $_GET)) {
    if ($_GET["action"] === "Next") {
        $from += $size;
    } else if ($_GET["action"] === "Prev") {
        $from -= $size;
    } else {
        return;
    }
}

$from = max(0, $from);
?>

<!DOCTYPE html>
<html>
<body>

<form method="GET">
    <label>intrari pe pagina</label>
    <select name="size">
        <option value="5" <?php if ($size == 5) { echo "selected"; } ?>>5</option>
        <option value="10" <?php if ($size == 10) { echo "selected"; } ?>>10</option>
        <option value="25" <?php if ($size == 25) { echo "selected"; } ?>>25</option>
    </select>
    <br>
    <input type="submit" value="Prev" name="action">
    <input type="submit" value="Next" name="action">
    <input type="hidden" name="from" value="<?php echo $from ?>">
</form>

<table>
    <thead>
		<th>nume</th>
		<th>producator</th> <th>procesor</th>
		<th>memorie</th>
		<th>capacitate</th>
		<th>tip disc</th>
		<th>placa video</th>
    </thead>
    <tbody>
        <?php
        $statement = $db->prepare(
            "SELECT name, producer, processor, memory, storage_capacity, storage_type, video_card FROM Laptop LIMIT ? OFFSET ?"
        );
        $statement->bindValue(1, $size, SQLITE3_INTEGER);
        $statement->bindValue(2, $from, SQLITE3_INTEGER);
        $result = $statement->execute();
        while ($row = $result->fetchArray()) { ?>
            <tr>
                <td><?php echo htmlentities($row["name"])             ?></td>
                <td><?php echo htmlentities($row["producer"])         ?></td>
                <td><?php echo htmlentities($row["processor"])        ?></td>
                <td><?php echo htmlentities($row["memory"])           ?></td>
                <td><?php echo htmlentities($row["storage_capacity"]) ?></td>
                <td><?php echo htmlentities($row["storage_type"])     ?></td>
                <td><?php echo htmlentities($row["video_card"])       ?></td>
            </tr>
        <?php } ?>
    </tbody>
</table>

</body>
</html> 