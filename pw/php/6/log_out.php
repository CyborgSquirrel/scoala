<?php
session_start();

session_unset();
session_destroy();

header("Location: log_in.php", true, 303);
?>