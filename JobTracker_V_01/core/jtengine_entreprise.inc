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
    jtui_display_update(-1,'cr&eacute;ation','le nom de l\'entreprise ne peut être vide');
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
    jtui_display_update(-1,'mise à jour','le nom de l\'entreprise ne peut être vide','viewSte','idSte',$idSte);
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

  jtui_display_update($nbRows,'mise à jour',$message,'viewSte','idSte',$idSte);
}

function jtengine_display_ste($idSte){
  $valuesArray = jtmysql_getSte($idSte);
  $ste = new entreprise($valuesArray);
  jtui_display_viewSte($ste);
}

?>