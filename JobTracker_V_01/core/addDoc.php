<?php
/*******************************************************************************
 *
 * JobTracker : outil de gestion et suivi de candidature
 *
 * Copyright (C) 2004  MANSOUR
 *
 * Cette biblioth�que est libre, vous pouvez la redistribuer et/ou la modifier 
 * selon les termes de la Licence Publique G�n�rale GNU Limit�e publi�e par la 
 * Free Software Foundation (version 2 ou bien toute autre version ult�rieure 
 * choisie par vous).
 *
 * Cette biblioth�que est distribu�e car potentiellement utile, mais SANS AUCUNE
 * GARANTIE, ni explicite ni implicite, y compris les garanties de 
 * commercialisation ou d'adaptation dans un but sp�cifique. Reportez-vous � la 
 * Licence Publique G�n�rale GNU Limit�e pour plus de d�tails.
 *
 * Vous devez avoir re�u une copie de la Licence Publique G�n�rale GNU Limit�e 
 * en m�me temps que cette biblioth�que; si ce n'est pas le cas, �crivez � la 
 * Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307, Etats-Unis. 
 *
 *
 * pour prendre contact avec les d�veloppeurs : jobtracker-dev@lists.berlios.de
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
       $page .="Le nom de fichier ne doit pas �tre vide ! ";
     } else {
       $page .="Le fichier existe d�j� ! ";
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