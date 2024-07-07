<?php

$db = new SQLite3("data.db");

?>

<!DOCTYPE html>
<html>

<head>
<style>

body {
	box-sizing: border-box;
}

#make-comment {
	width: min(40ch, 100%);
	box-sizing: border-box;
}

#make-comment > textarea {
	width: 100%;
	resize: none;
	box-sizing: border-box;
	min-height: 10ch;
}

</style>
</head>

<body>

<article>

<h1>Java</h1>
<p>by Sun Tzu</p>

<p>
Java, oh Java, the language of the land<br>
Where everything must be verbose and grand<br>
Where every class must have a purpose clear<br>
And every method must adhere
</p>
<p>
To design patterns, oh how they love<br>
The Factory, the Singleton, the Observer above<br>
All other patterns, they are the stars<br>
Of the Java universe, reaching for the bars
</p>
<p>
Of abstraction, never satisfied<br>
Until everything is classified and qualified<br>
In the world of Java, there is no room<br>
For simplicity, everything must assume
</p>
<p>
A certain level of complexity and design<br>
But is it worth it, or is it just a shine<br>
A veneer of sophistication, a façade to hide<br>
The underlying chaos, the constant slide
</p>
<p>
Into the realm of over-engineering, where<br>
Everything is unnecessarily prepared<br>
For every eventuality, every edge case<br>
But at what cost, this obsessive chase
</p>
<p>
After the perfect code, the perfect design<br>
Perhaps it's time to step back and align<br>
With a simpler way, a way that's true<br>
To the essence of programming, and what we should do
</p>
<p>
Not get lost in the details, but see the big picture<br>
And find a balance, a way to mix and mixure<br>
The beauty of abstraction with the power of simplicity<br>
That is the path to true efficiency.
</p>

</article>

<h1>Comments</h1>

<form method="POST" action="/6/comment.php" id="make-comment">
	<input type="hidden" name="back" value="<?php echo $_SERVER["REQUEST_URI"] ?>">
	<textarea name="content"></textarea>
	<br>
	<input type="text" name="name" placeholder="name">
	<input type="submit" value="Post">
</form>

<div id="comments">
<?php
$statement = $db->prepare(
	"SELECT name, content FROM Comment WHERE approval_state = 1"
);
$result = $statement->execute();
?>

<?php while ($row = $result->fetchArray()) { ?>
	<div>
		<b><?php echo htmlentities($row["name"]) ?></b>
		<p><?php echo htmlentities($row["content"]) ?></p>
	</div>
<?php } ?>
</div>

</body>
</html>
