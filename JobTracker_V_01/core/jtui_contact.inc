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

function jtui_display_listOfContact($result) {

  $liste="<h2>Liste des contacts</h2>\n";

  $table = jtui_display_tableWLinkOnFirst($result,'viewContact','idContact');
  
  $liste = $liste . $table;
  
  jtui_display_page($liste);
}

function jtui_display_contactEditForm($valuesArray) {

  if ($valuesArray == '') {
    $form=" <h2>Saisie d'un nouveau contact</h2>\n";
    $action='registerContact';
    $cnt = new contact();
    $defaultSte = '';
  } else {
    $form=" <h2>Modification d'une fiche contact</h2>\n";
    $action='modifyContact';
    $cnt = new contact($valuesArray);
    $defaultSte = $valuesArray[1];
  }

  $labelsArray = $cnt->labelsArray;
  array_shift($labelsArray);
  $fieldsArray = $cnt->fieldsArray;

  if ($valuesArray == '') {
    array_shift($fieldsArray);
  } else {
    $hiddenArray = array(array_shift($fieldsArray)=>array_shift($valuesArray));
  }

  $listofstebox=buildSelectBoxOfSte($defaultSte);

  $output = " <form method=\"post\" action=\"index.php?action=$action\">\n";
  $output = $output . "<table>\n";

  $lenght = count($labelsArray);

  for ($i = 0; $i < $lenght; $i++) {

    $output = $output . "\t<tr>\n\t\t<td>$labelsArray[$i]</td>\n";
    $output = $output . "\t\t<td>";
    
    if($i==0){
      $output = $output . $listofstebox;
    } else if($fieldsArray[$i] == 'addresse' || $fieldsArray[$i] == 'notes'){
      $output = $output . "<textarea rows=\"2\" cols=\"30\" name=\"$fieldsArray[$i]\">";
      if ($valuesArray != '') {
	$output = $output . "$valuesArray[$i]";
      }
      $output = $output . "</textarea>";
    } else {
      $output = $output . "<input type=\"text\" name=\"$fieldsArray[$i]\" ";     
      if ($valuesArray != '') {
	$output = $output . "value=\"$valuesArray[$i]\"";
      }
      $output = $output . ">";
    }

    $output = $output . "</td>\n\t</tr>";
  }

  $output = $output . "</table>";
  $output = $output . "<br>\n";
  if ($hiddenArray != '') {
    while (list ($key, $val) = each ($hiddenArray)) {
      $output = $output . "<input type=\"hidden\" name=\"$key\" value=\"$val\">\n";
    }
  }
  $output = $output . "<input type=submit value=\"enregistrer\">";
  $output = $output . "</form>";
  
  $form = $form . $output;
 
  jtui_display_page($form);
}

function jtui_display_viewContact($cnt){

  $fieldsArray=$cnt->fieldsArray;
  $valuesArray=$cnt->valuesArray;  

  array_shift($cnt->labelsArray);
  array_shift($cnt->fieldsArray);
  array_shift($cnt->valuesArray);
  
  $fiche="
 <h2>Fiche contact : $valuesArray[nomContact]</h2>\n
 ";

  $table = jtui_display_table($cnt->labelsArray,$cnt->fieldsArray,$cnt->valuesArray);
  
  $fiche = $fiche . $table;
  
  $editbutton = " <br><form method=post action=index.php?action=editContact>\n";

  foreach($fieldsArray as $field) {
    $editbutton = $editbutton . "<input type=hidden name=\"$field\" value=\"$valuesArray[$field]\">\n";
  }
  
  $editbutton = $editbutton . "<input type=submit value=\"modifier\">\n</form>\n";
  
  $doclist = "<br><hr>\n<h3>Documents</h3>\n" . jtui_formatDocs('Cnt',$valuesArray['idContact']);  

  $doclist .= "<br><form method=post action=index.php?action=addDoc>\n<input type=hidden name=idContact value=\"$valuesArray[idContact]\" >\n<input type=submit value=\"ajouter un document\">\n</form>\n";

  $fiche = $fiche . $editbutton . $doclist;
  
  jtui_display_page($fiche);
}

?>