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
    jtui_display_update(-1,'cr�ation','le nom du contact ne peut �tre vide');
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
    jtui_display_update($nbRows,'cr�ation',$message);
  }else {
    $dn = $nomContact . " " . $prenomContact;
    $idContact=jtmysql_get_idContact_from_dnContact($dn);
    jtui_display_update($nbRows,'cr�ation',$message,'viewContact','idContact',$idContact);
  }
}

function jtengine_modifyContact($valuesArray){

  //should check parameters as $valuesArray is a $_POST array

  $idContact     = addslashes($valuesArray['idContact']);
  $nomContact    = addslashes($valuesArray['nomContact']);

  if ($nomContact =='') {
    jtui_display_update(-1,'mise � jour','le nom du contact ne peut �tre vide','viewContact','idContact',$idContact);
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
  jtui_display_update($nbRows,'mise � jour',$message,'viewContact','idContact',$idContact);
}

function jtengine_display_contact($idContact){
  $valuesArray = jtmysql_getContact($idContact);
  $valuesArray['nomSte']= jtmysql_get_nomSte_from_idSte($valuesArray['idSte']);
  $contact = new contact($valuesArray);
  jtui_display_viewContact($contact);
}

?>