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

function jtui_display_page($page){
  jtui_display_header();
  jtui_display_title();
  jtui_display_navbar();
  print($page);
  jtui_display_footer();
}

function jtui_display_homepage() {

  $menu="
 <h2>Menu G&eacute;n&eacute;ral</h2>\n

 <h3>Candidatures</h3>\n 
 <ul>\n
  <li>\n
    <a href=\"./index.php?action=listOpenCandidature\">Afficher la liste des candidatures en cours</a>
 \n
  </li>\n
  <li>\n
    <a href=\"./index.php?action=listProspect\">Afficher la liste des candidatures en prospection</a>
 \n
  </li>\n
  <li>\n
    <a href=\"./index.php?action=listAllCandidature\">Afficher toutes les candidatures</a>
 \n
  </li>\n
<!--  <li>\n
    <a href=\"./index.php?action=searchCandidature\">Rechercher une canidature</a>\n
  </li>\n
-->  <li>\n
    <a href=\"./index.php?action=addCandidature\">Saisir une nouvelle candidature</a>
 \n
  </li>\n
 </ul>\n

 <h3>Entreprises</h3>\n 
 <ul>\n
  <li>\n
    <a href=\"./index.php?action=listSte\">Afficher la liste des entreprises</a>\n
  </li>\n
<!--  <li>\n
    <a href=\"./index.php?action=searchSte\">Rechercher une entreprise</a>\n
  </li>\n
-->  <li>\n
    <a href=\"./index.php?action=addSte\">Saisir une nouvelle entreprise</a>\n
  </li>\n
 </ul>\n

 <h3>Contacts</h3>\n 
 <ul>\n
  <li>\n
    <a href=\"./index.php?action=listContact\">Afficher la liste des contacts</a>\n
  </li>\n
<!--  <li>\n
    <a href=\"./index.php?action=searchContact\">Rechercher un contact</a>\n
  </li>\n
-->  <li>\n
    <a href=\"./index.php?action=addContact\">Saisir un nouveau contact</a>\n
  </li>\n
 </ul>\n
 ";
  
  jtui_display_page($menu);
}

function jtui_display_update($nbRows,$op,$message,$action='',$label='',$value=''){
  if ($nbRows <= 0){
    $report=" <br>&eacute;chec de la $op : $message.\n";
  } else {
    $report=" <br>$op r&eacute;ussie : $nbRows entr&eacute;e modifi&eacute;e.\n";
  }

  if($action != ''){
    $report = $report . "<br><br><a href=./index.php?action=$action&$label=$value>voir la fiche</a>\n";
  }
  
  jtui_display_page($report);
}

?>