<?php
/*******************************************************************************
 *
 * JobTracker : outil de gestion et suivi de candidature
 *
 * Copyright (C) 2004  MANSOUR
 *
 * Cette bibliothèque est libre, vous pouvez la redistribuer et/ou la modifier 
 * selon les termes de la Licence Publique Générale GNU Limitée publiée par la 
 * Free Software Foundation (version 2 ou bien toute autre version ultérieure 
 * choisie par vous).
 *
 * Cette bibliothèque est distribuée car potentiellement utile, mais SANS AUCUNE
 * GARANTIE, ni explicite ni implicite, y compris les garanties de 
 * commercialisation ou d'adaptation dans un but spécifique. Reportez-vous à la 
 * Licence Publique Générale GNU Limitée pour plus de détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU Limitée 
 * en même temps que cette bibliothèque; si ce n'est pas le cas, écrivez à la 
 * Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307, Etats-Unis. 
 *
 *
 * pour prendre contact avec les développeurs : jobtracker-dev@lists.berlios.de
 *
 ******************************************************************************
 * Historique
 ******************************************************************************
 *
 *  __JAN04  MANSOUR         Version initiale
 *
 ******************************************************************************/
?>

<?php

switch ($_GET['action']) {
 case "save" :
   $callingform = $_POST['callingform'];
   $callingelem = $_POST['callingelem'];
   $ref         = $_POST['ref'];
   $title       = addslashes($_POST['title']);
   $content     = addslashes($_POST['content']);
   $destDir     = "../" . "./data/" . $ref ;
   if(!is_dir($destDir)) {mkdir($destDir);}
   $destfile    = $destDir . "/" . $title . ".txt";
   $docPath     = "./data/" . $ref . "/" . $title . ".txt";
   
   if($title =='' || is_file($destfile)) {
     $form  ="<form method='post' action='addDoc.php?action=save'>";
     $form .="<input type='text' name='title' value='$title' ><br>";
     $form .="<textarea rows='8' cols='50' name='content'>$content</textarea>";
     $form .="<input type='hidden' name='callingform' value='$callingform'>";
     $form .="<input type='hidden' name='callingelem' value='$callingelem'>";
     $form .="<input type='hidden' name='ref' value='$ref'>";
     $form .="<input type='submit' value='enregistrer'>";     
     $page="<html><body>";
     if($title == '') {
       $page .="Le nom de fichier ne doit pas être vide ! ";
     } else {
       $page .="Le fichier existe déjà ! ";
     }
     $page .="<br><br>" . $form . "</body></html>";
   } else {
     $ressource=fopen($destfile,'w+');
     fwrite($ressource,$content);
     fclose($ressource);
     $page  ="<html><head>";
     $page .="<script language='JavaScript'>";
     $page .="window.opener.document.forms[\"$callingform\"].elements[\"$callingelem\"].value=\"$docPath\";";
     $page .="window.close();";
     $page .="</script>";
     $page .="<body>";
     $page .="</body></html>";
   }
   print($page);
   break;
   
 default :
   $callingform = $_GET['form'];
   $callingelem = $_GET['elem'];
   $ref         = $_GET['ref'];
   $form  ="<form method='post' action='addDoc.php?action=save'>";
   $form .="<input type='text' name='title'><br>";
   $form .="<textarea rows='8' cols='50' name='content'></textarea>";
   $form .="<input type='hidden' name='callingform' value='$callingform'>";
   $form .="<input type='hidden' name='callingelem' value='$callingelem'>";
   $form .="<input type='hidden' name='ref' value='$ref'>"; 
   $form .="<input type='submit' value='enregistrer'>"; 
   $form .="<input type='button' value='annuler' onClick='window.close();'>";
   
   $page="<html><body>Veuillez saisir le nom du fichier et son contenu. <br><br>" . $form . "</body></html>";
   print($page);
   break;
}

?>