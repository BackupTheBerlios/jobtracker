<?php

class contact {

  var $labelsArray;
  var $fieldsArray;
  var $valuesArray;

  function contact($valuesArray=''){
    $this->labelsArray = array('id','Entreprise','Nom','Prenom','Fonction','Email','Tel','Mobile','Addresse','notes');
    $this->fieldsArray = array('idContact','nomSte','nomContact','prenomContact','fct','mail','tel','mobile','addresse','notes');
    $this->valuesArray=$valuesArray;
  }
}

function jtengine_listContact() {
  $result = jtmysql_getListOfAllContact();
  jtui_display_listOfContact($result);
  jtmysql_free($result);
}

function jtengine_display_contactEditForm($valueArray){
  if ($valueArray != ''){
    $values=array_values($valueArray);
  }
  jtui_display_contactEditForm($values);
}

function jtengine_registerContact($valueArray){

  //should check parameters as $valueArray is a $_POST array

  $nomContact    = addslashes($valueArray['nomContact']);

  if ($nomContact =='') {
    jtui_display_update(-1,'création','le nom du contact ne peut être vide');
    return;
  }

  $idSte         = jtmysql_get_idSte_from_nomSte(addslashes($valueArray['nomSte']));
  
  $prenomContact = addslashes($valueArray['prenomContact']);
  $fct           = addslashes($valueArray['fct']);
  $mail          = addslashes($valueArray['mail']);
  $tel           = addslashes($valueArray['tel']);
  $mobile        = addslashes($valueArray['mobile']);
  $addresse      = addslashes($valueArray['addresse']);
  $notes         = addslashes($valueArray['notes']);          
  
  $nbRows = jtmysql_registerContact($idSte,$nomContact,$prenomContact,$fct,$mail,$tel,$mobile,$addresse,$notes);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
    jtui_display_update($nbRows,'création',$message);
  }else {
    $dn = $nomContact . " " . $prenomContact;
    $idContact=jtmysql_get_idContact_from_dnContact($dn);
    jtui_display_update($nbRows,'création',$message,'viewContact','idContact',$idContact);
  }
}

function jtengine_modifyContact($valuesArray){

  //should check parameters as $valuesArray is a $_POST array

  $idContact     = addslashes($valuesArray['idContact']);
  $nomContact    = addslashes($valuesArray['nomContact']);

  if ($nomContact =='') {
    jtui_display_update(-1,'mise à jour','le nom du contact ne peut être vide','viewContact','idContact',$idContact);
    return;
  }

  $idSte         = jtmysql_get_idSte_from_nomSte(addslashes($valuesArray['nomSte']));

  $prenomContact = addslashes($valuesArray['prenomContact']);
  $fct           = addslashes($valuesArray['fct']);
  $mail          = addslashes($valuesArray['mail']);
  $tel           = addslashes($valuesArray['tel']);
  $mobile        = addslashes($valuesArray['mobile']);
  $addresse      = addslashes($valuesArray['addresse']);
  $notes         = addslashes($valuesArray['notes']);          

  $nbRows = jtmysql_modifyContact($idContact,$idSte,$nomContact,$prenomContact,$fct,$mail,$tel,$mobile,$addresse,$notes);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }
  jtui_display_update($nbRows,'mise à jour',$message,'viewContact','idContact',$idContact);
}

function jtengine_display_contact($idContact){
  $valuesArray = jtmysql_getContact($idContact);
  $valuesArray['nomSte']= jtmysql_get_nomSte_from_idSte($valuesArray['idSte']);
  $contact = new contact($valuesArray);
  jtui_display_viewContact($contact);
}

?>