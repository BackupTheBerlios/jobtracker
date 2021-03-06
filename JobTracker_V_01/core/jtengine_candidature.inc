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

class candidature {

  var $labelsArray;
  var $fieldsArray;
  var $valuesArray;
  var $eventsArray;

  function candidature($valuesArray='',$eventsArray=''){
    $this->labelsArray = array('R�f�rence','Entreprise','D�partement','Poste','Lieu','Date initiale','Derni�re mise � jour','Etat','Origine','notes');
    $this->fieldsArray = array('refCandidature','nomSte','departement','poste','lieu','dateInit','dateMAJ','etat','origine','notes');
    $this->valuesArray = $valuesArray;
    $this->eventsArray = $eventsArray;
  }
}


function jtengine_listCandidature($status){
  $result = jtmysql_getListOfCandidature($status);
  jtui_display_listOfCandidature($result);
  jtmysql_free($result);
}

function jtengine_display_candidature($idCandidature){
  $valuesArray = jtmysql_getCandidature($idCandidature);
  $eventsArray = jtmysql_getCandidatureEvents($idCandidature);
  $valuesArray['nomSte']= jtmysql_get_nomSte_from_idSte($valuesArray['idSte']);
  $candidature = new candidature($valuesArray,$eventsArray);
  jtui_display_viewCandidature($idCandidature,$candidature);
}

function jtengine_display_candidatureEditForm($valuesArray){
  if ($valuesArray != ''){
    $values=array_values($valuesArray);
  }
  jtui_display_candidatureEditForm($values);
}

function jtengine_registerCandidature($valuesArray){

  $refCandidature = addslashes($valuesArray['refCandidature']);
  $idSte          = jtmysql_get_idSte_from_nomSte(addslashes($valuesArray['nomSte']));
  $dep            = addslashes($valuesArray['departement']);
  $poste          = addslashes($valuesArray['poste']);
  $lieu           = addslashes($valuesArray['lieu']);
  $dateInit       = date("Y-m-d");
  $dateMAJ        = date("Y-m-d H:i:s");
  $etat           = addslashes($valuesArray['etat']);
  $origine        = addslashes($valuesArray['origine']); 
  $notes          = addslashes($valuesArray['notes']);
 
  $nbRows         = jtmysql_registerCandidature($refCandidature,$idSte,$dep,$poste,$lieu,$dateInit,$dateMAJ,$etat,$origine,$notes);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }
  jtui_display_update($nbRows,'cr�ation',$message);
}


function jtengine_modifyCandidature($valuesArray){

  $idCandidature  = addslashes($valuesArray['idCandidature']);
  $refCandidature = addslashes($valuesArray['refCandidature']);
  $idSte          = jtmysql_get_idSte_from_nomSte(addslashes($valuesArray['nomSte']));
  $dep            = addslashes($valuesArray['departement']);
  $poste          = addslashes($valuesArray['poste']);
  $lieu           = addslashes($valuesArray['lieu']);
  $dateMAJ        = date("Y-m-d H:i:s");
  $etat           = addslashes($valuesArray['etat']);
  $origine        = addslashes($valuesArray['origine']); 
  $notes          = addslashes($valuesArray['notes']);
 
  $nbRows         = jtmysql_modifyCandidature($idCandidature,$refCandidature,$idSte,$dep,$poste,$lieu,$dateMAJ,$etat,$origine,$notes);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }
  jtui_display_update($nbRows,'mise � jour',$message,'viewCandidature','idCandidature',$idCandidature);
}

function jtengine_display_eventEditForm($valuesArray){
  if (array_key_exists('idEvent',$valuesArray)) {
    /* modify box */
    $idEvent    = $valuesArray['idEvent'];
    $values     = jtmysql_getEvent($idEvent);
    $idCandidature = $values['idCandidature'];
  }else {
    /* new add box */
    $idCandidature = $valuesArray['idCandidature'];
    $today=date("Y-m-d H:i:s");
    $values=array(idEvent=>'',idContact=>'',dateEvent=>$today,descrEvent=>'',docPath=>'');
  }

  jtui_display_eventEditForm($idCandidature,$values);
}

function jtengine_registerEvent($valuesArray){

  $dateEvent     = addslashes($valuesArray['dateEvent']);
  $dnContact     = addslashes($valuesArray['dnContact']);
  $idContact     = jtmysql_get_idContact_from_dnContact(addslashes($dnContact));
  $descrEvent    = addslashes($valuesArray['descrEvent']);
  $idCandidature = addslashes($valuesArray['idCandidature']);
  
  $newFile = addslashes($valuesArray['newFile']);
  if ($newFile != '') {
    $target=$newFile;
  } else if ($_FILES != '') {
    $refCandidature = jtmysql_get_refCandidature_from_idCandidature($idCandidature);
    $doc            = $_FILES['docPath'];
    $destDir        = "./data/" . $refCandidature;
    if(!is_dir($destDir)) {
      mkdir($destDir);
    }
    $target         =  $destDir . "/" . $doc['name'];
    if(!move_uploaded_file($doc['tmp_name'],$target)) {
      $target='';
    }
  } else {
    $target ='';
  }

  $nbRows        = jtmysql_registerEvent($idCandidature,$idContact,$dateEvent,$descrEvent,$target);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }
  jtui_display_update($nbRows,'cr�ation',$message,'viewCandidature','idCandidature',$idCandidature);
  
}

function jtengine_modifyEvent($valuesArray){
  $idEvent       = addslashes($valuesArray['idEvent']);
  
  $dateEvent     = addslashes($valuesArray['dateEvent']);
  $dnContact     = addslashes($valuesArray['dnContact']);
  if($dnContact != '') {
    $idContact     = jtmysql_get_idContact_from_dnContact($dnContact);
  }
  $descrEvent    = addslashes($valuesArray['descrEvent']);
  $idCandidature = addslashes($valuesArray['idCandidature']);

  if ($_FILES != '') {
    $refCandidature = jtmysql_get_refCandidature_from_idCandidature($idCandidature);
    $doc            = $_FILES['docPath'];
    $destDir        = "./data/" . $refCandidature;
    if(!is_dir($destDir)) {
      mkdir($destDir);
    }
    $target         =  $destDir . "/" . $doc['name'];
    if(!move_uploaded_file($doc['tmp_name'],$target)) {
      $target='';
    }
  } else {
    $target ='';
  }

  $nbRows        = jtmysql_modifyEvent($idEvent,$idContact,$dateEvent,$descrEvent,$target);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }
  jtui_display_update($nbRows,'mise � jour',$message,'viewCandidature','idCandidature',$idCandidature);  
}

?>