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

function jtui_display_listOfSte($result) {

  $liste="<h2>Liste des entreprises</h2>\n";

  $table = jtui_display_tableWLinkOnFirst($result,'viewSte','idSte');
  
  $liste = $liste . $table;
  
  jtui_display_page($liste);
}

function jtui_display_steEditForm($valuesArray) {

  if ($valuesArray == '') {
    $form=" <h2>Saisie d'une nouvelle entreprise</h2>\n";
    $action='registerSte';
    $ste = new entreprise();
  } else {
    $form=" <h2>Modification d'une fiche entreprise</h2>\n";
    $action='modifySte';
    $ste = new entreprise($valuesArray);
  }

  $labelsArray = $ste->labelsArray;
  array_shift($labelsArray);
  $fieldsArray = $ste->fieldsArray;

  if ($valuesArray == '') {
    array_shift($fieldsArray);
  } else {
    $hiddenArray = array(array_shift($fieldsArray)=>array_shift($valuesArray));
  }

  $form = $form . jtui_display_form($action,$labelsArray,$fieldsArray,$valuesArray,$hiddenArray);
  
  jtui_display_page($form);
}

function jtui_display_viewSte($ste){

  $fieldsArray=$ste->fieldsArray;
  $valuesArray=$ste->valuesArray;  

  array_shift($ste->labelsArray);
  array_shift($ste->fieldsArray);
  array_shift($ste->valuesArray);
  
  $fiche="
 <h2>Fiche entreprise : $valuesArray[nomSte]</h2>\n
 ";

  $table = jtui_display_table($ste->labelsArray,$ste->fieldsArray,$ste->valuesArray);
  
  $fiche = $fiche . $table;
  
  $editbutton = " <br><form method=post action=index.php?action=editSte>\n";

  foreach($fieldsArray as $field) {
    $editbutton = $editbutton . "<input type=hidden name=\"$field\" value=\"$valuesArray[$field]\">\n";
  }
  
  $editbutton = $editbutton . "<input type=submit value=\"modifier\">\n</form>\n";
  
  $doclist = "<br><hr>\n<h3>Documents</h3>\n" . jtui_formatDocs('Ste',$valuesArray['idSte']);  

  $doclist .= "<br><form method=post action=index.php?action=addDoc>\n<input type=hidden name=idSte value=\"$valuesArray[idSte]\" >\n<input type=submit value=\"ajouter un document\">\n</form>\n";

  $fiche = $fiche . $editbutton . $doclist;
  
  jtui_display_page($fiche);
}

?>