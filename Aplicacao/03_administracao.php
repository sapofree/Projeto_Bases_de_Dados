<?php
session_start();
?>
<html lang="pt">
<head>
    <meta charset="UTF-8" />
    <title>Administração</title>
</head>
<body style="background-color:azure;">
<?php
    if($_SESSION['central_status'] != "Logout")
        {
            ob_start(); // ensures anything dumped out will be caught
            $url = 'index.php'; // this can be set based on whatever

            // clear out the output buffer
            while (ob_get_status()) 
            {
                ob_end_clean();
            }

            // no redirect
            header( "Location: $url" );

        }
?>

    <h1>Aplicação</h1>
    <form action="index.php" style="float: left;">
        <input type="submit" value="Home">
    </form>
    <form action="02_consultas.php" style="float: left;">
        <input type="submit" value="Consultas">
    </form>
    <form action="03_administracao.php" style="float: left;">
        <input type="submit" value="Administração">
    </form>
    <?php
        if($_SESSION['central_status'] == "Logout" && $_SESSION['local_status'] == "Disconnect")
        {
            echo "<form action=\"05_login_local.php\" style=\"float: left;\">
            <input type=\"submit\" value=\"" . $_SESSION['local_name'] . "\">
            </form>";
        }else if($_SESSION['central_status'] == "Logout" && $_SESSION['local_status'] != "Disconnect")
        {
            echo "<form action=\"05_login_local.php\" style=\"float: left;\">
            <input type=\"submit\" value=\"Conectar Local\">
            </form>";
        }
    ?>
    <form action="04_login.php">
        <input type="submit" value="<?php echo $_SESSION['central_status']; ?>">
    </form>
    <?php
        if($_SESSION['central_status'] == "Logout" && $_SESSION['local_status'] == "Disconnect")
        {
            echo     "<form action=\"031_admin_cliente.php\" style=\"float: left;\">
                    <input type=\"submit\" value=\"Gestão Clientes\">
                    </form>
                    <form action=\"032_admin_molde.php\" style=\"float: left;\">
                    <input type=\"submit\" value=\"Gestão Moldes\">
                    </form>
                    <form action=\"033_admin_sensor.php\">
                    <input type=\"submit\" value=\"Gestão Sensores\">
                    </form>
                    <!-- <form action=\"034_admin_eliminar.php\">
                    <input type=\"submit\" value=\"Eliminar\">
                    </form> -->";
        }else
        {  
            echo "<form action=\"031_admin_cliente.php\">
            <input type=\"submit\" value=\"Gestão Clientes\">
            </form>";
        }
    ?>

<?php
    require('query.php');
?>

</body>
</html>