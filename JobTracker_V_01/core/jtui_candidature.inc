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

function jtui_display_listOfCandidature($result){
  $liste="<h2>Liste des candidatures</h2>\n";
  

  $table = jtui_display_tableWLinkOnFirst($result,'viewCandidature','idCandidature');

  $liste = $liste . $table;
  
  jtui_display_page($liste);
}

function jtui_display_candidatureEditForm($valuesArray='') {

  if ($valuesArray == ''){
    $editForm = " <h2>Saisie d'une nouvelle candidature</h2>\n";
    $action='registerCandidature';
    $candidature = new candidature();
    $defaultSte = '';
  } else {
    $editForm = " <h2>Modification d'une fiche candidature</h2>\n";
    $action='modifyCandidature';
    $candidature = new candidature($valuesArray);
    $defaultSte = $valuesArray[1];
  }

  $labelsArray = $candidature->labelsArray;
  $fieldsArray = $candidature->fieldsArray;

  $listofstebox=buildSelectBoxOfSte($defaultSte);

  $form = " <form method=\"post\" action=\"index.php?action=$action\">\n<table>\n";

  $lenght = count($labelsArray);

  for ($i = 0; $i < $lenght; $i++) {
    
    if($i == 5) {$i++;$i++;}; /* skip date init & MAJ */

    switch($fieldsArray[$i]) {
    case nomSte :
      $form = $form . "\t<tr>\n\t\t<td>$labelsArray[$i]</td>\n\t\t<td>\n" . $listofstebox;
      break;
    case notes :
      $form = $form . "\t<tr class=\"notesBox\">\n\t\t<td>$labelsArray[$i]</td>\n\t\t<td class=\"notesBox\">";
      $form = $form . "<textarea rows=\"8\" cols=\"80\" name=\"$fieldsArray[$i]\" >";
      if ($valuesArray != '') {
	$form = $form . "$valuesArray[$i]";
      }
      $form = $form . "</textarea>";
      break;
    default :
      $form = $form . "\t<tr>\n\t\t<td>$labelsArray[$i]</td>\n\t\t<td><input type=\"text\" name=\"$fieldsArray[$i]\" ";
      if ($valuesArray != '') {
	$form = $form . "value=\"$valuesArray[$i]\" ";
      }
      $form = $form . ">";
      break;
    }
    $form = $form . "</td>\n\t</tr>\n";
  }

  $form = $form . "</table>\n<br>\n";
  $form = $form . "<input type=\"hidden\" name=\"idCandidature\" value=\"$valuesArray[$lenght]\" >\n";
  $form = $form . "<input type=submit value=\"enregistrer\">\n</form>";

  $editForm = $editForm . $form;
  
  jtui_display_page($editForm);
}

function jtui_formatEvents($idCandidature){

  $eventsTable = "<table>\n";

  $result = jtmysql_getCandidatureEvents($idCandidature);

  $eventsTable = $eventsTable . "\t<tr>\n";
  $eventsTable = $eventsTable . "\t\t<th class=\"event\">Date</th>\n";
  $eventsTable = $eventsTable . "\t\t<th class=\"event\">Contact</th>\n";
  $eventsTable = $eventsTable . "\t\t<th class=\"event\">Description</th>\n";
  $eventsTable = $eventsTable . "\t\t<th class=\"event\">Document</th>\n";
  $eventsTable = $eventsTable . "\t\t<th class=\"event\"></th>\n";
  $eventsTable = $eventsTable . "\t</tr>\n";
  
  while($event=mysql_fetch_array($result,MYSQL_ASSOC)){
    $doc=$event['docPath'];
    $eventsTable = $eventsTable . "\t<tr>\n";
    $eventsTable = $eventsTable . "\t\t<td>$event[dateEvent]</td>\n";
    $eventsTable = $eventsTable . "\t\t<td>" . jtmysql_get_dnContact_from_idContact($event['idContact']) . "</td>\n";
    $eventsTable = $eventsTable . "\t\t<td>$event[descrEvent]</td>\n";
    $eventsTable = $eventsTable . "\t\t<td><a href=\"$doc\" TARGET=\"_blank\">" . basename($doc) . "</a></td>\n";
    $eventsTable = $eventsTable . "\t\t<td><form method=post action=index.php?action=editEvent>\n
 \t\t    <input type=hidden name=idEvent value=\"$event[idEvent]\"><input type=submit value=\"modifier\">\n
 \t\t    </form>\n\t\t</td>\n";
    $eventsTable = $eventsTable . "\t</tr>\n";
  }
  $eventsTable = $eventsTable . "</table>\n";

  jtmysql_free($result);

  return $eventsTable;
}

function jtui_display_viewCandidature($idCandidature,$candidature){

  $labelsArray= $candidature->labelsArray;
  $fieldsArray= $candidature->fieldsArray;
  $valuesArray= $candidature->valuesArray;  
  
  $page = "<h2>Fiche candidature : $valuesArray[refCandidature]</h2>\n";  

  $fiche = "<table class=\"fichecandidature\">\n
\t<tr>\n\t\t<td class=\"label\">$labelsArray[1]</td>\n\t\t<td>$valuesArray[nomSte]</td>\n
\t\t<td class=\"label\">$labelsArray[0]</td>\n\t\t<td>$valuesArray[refCandidature]</td>\n\t</tr>\n
\t<tr>\n\t\t<td class=\"label\">$labelsArray[2]</td>\n\t\t<td>$valuesArray[departement]</td>\n
\t\t<td class=\"label\">$labelsArray[5]</td>\n\t\t<td>$valuesArray[dateInit]</td>\n\t</tr>\n
\t<tr>\n\t\t<td class=\"label\">$labelsArray[3]</td>\n\t\t<td>$valuesArray[poste]</td>\n
\t\t<td class=\"label\">$labelsArray[6]</td>\n\t\t<td>$valuesArray[dateMAJ]</td>\n\t</tr>\n
\t<tr>\n\t\t<td class=\"label\">$labelsArray[4]</td>\n\t\t<td>$valuesArray[lieu]</td>\n
\t\t<td class=\"label\">$labelsArray[7]</td>\n\t\t<td>$valuesArray[etat]</td>\n\t</tr>\n
\t<tr>\n\t\t<td class=\"label\"></td>\n\t\t<td></td>\n
\t\t<td class=\"label\">$labelsArray[8]</td>\n\t\t<td>$valuesArray[origine]</td>\n\t</tr>\n
\t<tr>\n\t\t<td class=\"label\">$labelsArray[9]</td>\n\t\t<td colspan=\"3\"><pre>$valuesArray[notes]</pre></td>\n\t</tr>\n
</table>\n";


  $editbutton = "<br> <form method=post action=index.php?action=editCandidature>\n";
  foreach($fieldsArray as $field) {
    $editbutton = $editbutton . "<input type=hidden name=\"$field\" value=\"$valuesArray[$field]\">\n";
  }  
  $editbutton = $editbutton . "<input type=hidden name=\"idCandidature\" value=\"$idCandidature\">\n";
  $editbutton = $editbutton . "<input type=submit value=\"modifier\">\n</form>\n";
  
  $historique = "<br><hr>\n<h3>Historique</h3>\n" . jtui_formatEvents($idCandidature);  

  $historique = $historique . "<br><form method=post action=index.php?action=addEvent>\n<input type=hidden name=idCandidature value=$idCandidature >\n<input type=submit value=\"ajouter un &eacute;venement\">\n</form>\n";

  $page = $page . $fiche . $editbutton . $historique ;

  jtui_display_page($page);  
}

function jtui_display_eventEditForm($idCandidature,$valuesArray){
  
  $refCandidature=jtmysql_get_refCandidature_from_idCandidature($idCandidature);
  $formname="eventForm";
  if ($valuesArray['idEvent'] == ''){
    $editForm = " <h2>Ajouter un nouvel &eacute;venement à la candidature : $refCandidature</h2>\n";
    $action='registerEvent';
  } else {
    $editForm = " <h2>Modification d'un &eacute;venement de la candidature : $refCandidature</h2>\n";
    $action ='modifyEvent';
    $idContact = $valuesArray['idContact'];
    $dnContact = jtmysql_get_dnContact_from_idContact($idContact);
  }

    $doc="$valuesArray[docPath]";

    if (is_file($doc)) {
      $docfield="<a href=\"$doc\" TARGET=\"_blank\">" . basename($doc) . "</a>";
    } else {
      $docfield  = "<pre>s&eacute;lectionner un fichier existant </pre><input type=file name=docPath \">";
      $docfield .= "<pre>ou cr&eacute;er un nouveau fichier texte</pre><input type=text name=newFile>";
      $docfield .= "<input type=button value=\"cr&eacute;er\" 
 onClick=\"window.open('./core/addDoc.php?form=$formname&elem=newFile&ref=$refCandidature','Nouveau document','width=440,height=250')\">";
    }
    
  $editForm = $editForm ."<form enctype=\"multipart/form-data\" method=post action=index.php?action=$action name=\"$formname\">
     <table>\n
     \t<tr>\n\t\t<td>Date</td>\n\t\t<td><input type=text name=dateEvent value=\"$valuesArray[dateEvent]\"></td>\n\t</tr>\n
     \t<tr>\n\t\t<td>Contact</td>\n\t\t<td>" . buildSelectBoxOfContact($dnContact) . "</td>\n\t</tr>\n
     \t<tr>\n\t\t<td>Description</td>\n\t\t<td><input type=text name=descrEvent value=\"$valuesArray[descrEvent]\"></td>\n\t</tr>\n
     \t<tr>\n\t\t<td>Document</td>\n\t\t<td>$docfield</td>\n\t</tr>\n
 </table>\n
 
 <br>\n
 <input type=hidden name=idCandidature value=\"$idCandidature\">\n
 <input type=hidden name=idEvent value=\"$valuesArray[idEvent]\">\n
 <input type=submit value=\"enregistrer\">\n
 </form>\n
 ";

  jtui_display_page($editForm);
}

?>