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

class entreprise {

  var $labelsArray;
  var $fieldsArray;
  var $valuesArray;

  function entreprise($valuesArray=''){
    $this->labelsArray = array('id','Nom','Activit&eacute;','Implantations','Effectif','Siege','url','notes');
    $this->fieldsArray = array('idSte','nomSte','activite','implantations','effectif','siege','url','notes');
    $this->valuesArray=$valuesArray;
  }
}

function jtengine_listSte() {
  $result = jtmysql_getListOfAllSte();
  jtui_display_listOfSte($result);
  jtmysql_free($result);
}

function jtengine_display_steEditForm($valueArray){
  if ($valueArray != ''){
    $values=array_values($valueArray);
  }
  jtui_display_steEditForm($values);
}

function jtengine_registerSte($valueArray){

  //should check parameters as $valueArray is a $_POST array
  $nomSte =       addslashes($valueArray['nomSte']);
  
  if ($nomSte =='') {
    jtui_display_update(-1,'cr&eacute;ation','le nom de l\'entreprise ne peut �tre vide');
    return;
  }
  $activite =     addslashes($valueArray['activite']);   
  $implantations =addslashes($valueArray['implantations']);
  $effectif =     addslashes($valueArray['effectif']);    
  $siege =        addslashes($valueArray['siege']);       
  $url =          addslashes($valueArray['url']);          
  $notes =        addslashes($valueArray['notes']);          

  $nbRows = jtmysql_registerSte($nomSte,$activite,$implantations,$effectif,$siege,$url,$notes);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
    jtui_display_update($nbRows,'cr&eacute;ation',$message);
  }else {
    $idSte=jtmysql_get_idSte_from_nomSte($nomSte);
    jtui_display_update($nbRows,'cr&eacute;ation',$message,'viewSte','idSte',$idSte);
  }
  

}

function jtengine_modifySte($valueArray){

  //should check parameters as $valueArray is a $_POST array

  $idSte  =       addslashes($valueArray['idSte']);
  $nomSte =       addslashes($valueArray['nomSte']);

  if ($nomSte =='') {
    jtui_display_update(-1,'mise � jour','le nom de l\'entreprise ne peut �tre vide','viewSte','idSte',$idSte);
    return;
  }
  $activite =     addslashes($valueArray['activite']);   
  $implantations =addslashes($valueArray['implantations']);
  $effectif =     addslashes($valueArray['effectif']);    
  $siege =        addslashes($valueArray['siege']);       
  $url =          addslashes($valueArray['url']);          
  $notes =        addslashes($valueArray['notes']);          

  $nbRows = jtmysql_modifySte($idSte,$nomSte,$activite,$implantations,$effectif,$siege,$url,$notes);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }

  jtui_display_update($nbRows,'mise � jour',$message,'viewSte','idSte',$idSte);
}

function jtengine_display_ste($idSte){
  $valuesArray = jtmysql_getSte($idSte);
  $ste = new entreprise($valuesArray);
  jtui_display_viewSte($ste);
}

?>