<?php

class candidature {

  var $labelsArray;
  var $fieldsArray;
  var $valuesArray;
  var $eventsArray;

  function candidature($valuesArray='',$eventsArray=''){
    $this->labelsArray = array('Référence','Entreprise','Département','Poste','Lieu','Date initiale','Dernière mise à jour','Etat','Origine','notes');
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
  jtui_display_update($nbRows,'création',$message);
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
  jtui_display_update($nbRows,'mise à jour',$message,'viewCandidature','idCandidature',$idCandidature);
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
  jtui_display_update($nbRows,'création',$message,'viewCandidature','idCandidature',$idCandidature);
  
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
  jtui_display_update($nbRows,'mise à jour',$message,'viewCandidature','idCandidature',$idCandidature);  
}

?>