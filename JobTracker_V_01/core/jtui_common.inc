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