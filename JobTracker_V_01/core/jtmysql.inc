<?php
include "./setup/jt_db_setup.ini";

mysql_connect("$dbhost","$dbuser","$dbpwd") or die ("<br>connection impossible");
mysql_select_db("$db") or die ("<br> selection de la base impossible");

function jtmysql_getErrorMessage(){
  return mysql_error();
}

function jtmysql_free($result){
  mysql_free_result($result);
}

function jtmysql_getListOfCandidature($status){

  $query = "SELECT idCandidature,refCandidature,nomSte,poste,etat FROM candidature,entreprise WHERE candidature.idSte=entreprise.idSte ";
  switch($status) {
  case open :
    /* fall through */
  case prospection :
    $query = $query . "AND candidature.etat='$status' ";
    break;
  }

  $query .= "ORDER BY nomSte";

  $result=mysql_query($query);
  return $result;
}

function jtmysql_registerCandidature($refCandidature,$idSte,$dep,$poste,$lieu,$dateInit,$dateMAJ,$etat,$origine,$notes) {

  if ($etat != '') {
    $query = "INSERT INTO candidature(idSte,departement,poste,lieu,dateInit,dateMAJ,etat,origine,notes) VALUES ('$idSte','$dep','$poste','$lieu','$dateInit','$dateMAJ','$etat','$origine','$notes')";
  } else {
    $query = "INSERT INTO candidature(idSte,departement,poste,lieu,dateInit,dateMAJ,origine,notes) VALUES ('$idSte','$dep','$poste','$lieu','$dateInit','$dateMAJ','$origine','$notes')";
  }

  mysql_query($query);

  $id = mysql_insert_id();
  $nrows = mysql_affected_rows();
  if ($nrows <= 0) {
    return $nrows;
  }

  $completeRef = "$refCandidature" . "$id";
  $query_update = "UPDATE candidature SET refCandidature='$completeRef' WHERE idCandidature='$id'" ;
  mysql_query($query_update);

  return mysql_affected_rows();
}

function jtmysql_modifyCandidature($idCandidature,$refCandidature,$idSte,$dep,$poste,$lieu,$dateMAJ,$etat,$origine,$notes) {
  $query = "UPDATE candidature SET refCandidature='$refCandidature',idSte='$idSte',departement='$dep',poste='$poste',lieu='$lieu',dateMAJ='$dateMAJ',etat='$etat',origine='$origine',notes='$notes' WHERE idCandidature='$idCandidature'";
  mysql_query($query);
  return mysql_affected_rows();
}

function jtmysql_getCandidature($idCandidature){
  $query="SELECT * FROM candidature WHERE idCandidature='$idCandidature'";
  $result=mysql_query($query);
  $valuesArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $valuesArray;
}

function jtmysql_get_refCandidature_from_idCandidature($idCandidature) {
  $query="SELECT refCandidature FROM candidature WHERE idCandidature='$idCandidature'";
  $result=mysql_query($query);
  $resultArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $resultArray['refCandidature'];

}

function jtmysql_getCandidatureEvents($idCandidature){
  $query="SELECT * FROM historique WHERE idCandidature='$idCandidature'";
  $result=mysql_query($query);
  return $result;
}

function jtmysql_getEvent($idEvent){
  $query="SELECT * FROM historique WHERE idEvent='$idEvent'";
  $result=mysql_query($query);
  $resultArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);  
  return $resultArray;
}

function jtmysql_registerEvent($idCandidature,$idContact,$dateEvent,$descrEvent,$docPath){
  $query="INSERT INTO historique(idCandidature,idContact,dateEvent,descrEvent,docPath) VALUES ('$idCandidature','$idContact','$dateEvent','$descrEvent','$docPath')";

  mysql_query($query);
  return mysql_affected_rows();
}

function jtmysql_modifyEvent($idEvent,$idContact,$dateEvent,$descrEvent,$docPath){

  $query="UPDATE historique SET idContact='$idContact',dateEvent='$dateEvent',descrEvent='$descrEvent'";
  if ($docPath != '') {
    $query .=",docPath='$docPath'";
  }
  $query .=" WHERE idEvent='$idEvent'";

  mysql_query($query);
  return mysql_affected_rows();
}

function jtmysql_getListOfAllSte(){
  $query="SELECT idSte,nomSte FROM entreprise ORDER BY nomSte";
  $listeSte=mysql_query($query);
  return $listeSte;
};

function jtmysql_getSte($idSte){
  $query="SELECT * FROM entreprise WHERE idSte='$idSte'";
  $result=mysql_query($query);
  $valuesArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $valuesArray;
}

function jtmysql_get_idSte_from_nomSte($nomSte){
  $query="SELECT idSte FROM entreprise WHERE nomSte='$nomSte'";
  $result=mysql_query($query);
  $resultArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $resultArray['idSte'];
}

function jtmysql_get_nomSte_from_idSte($idSte){
  $query="SELECT nomSte FROM entreprise WHERE idSte='$idSte'";
  $result=mysql_query($query);
  $resultArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $resultArray['nomSte'];
}

function jtmysql_registerSte($nomSte,$activite,$implantations,$effectif,$siege,$url,$notes){
    $query="INSERT INTO entreprise(nomSte,activite,implantations,effectif,siege,url,notes) VALUES('$nomSte','$activite','$implantations','$effectif','$siege','$url','$notes')";
  mysql_query($query);
  return mysql_affected_rows();
}

function jtmysql_modifySte($idSte,$nomSte,$activite,$implantations,$effectif,$siege,$url,$notes){
    $query="UPDATE entreprise SET nomSte='$nomSte',activite='$activite',implantations='$implantations',effectif='$effectif',siege='$siege',url='$url',notes='$notes' WHERE idSte='$idSte'";
  mysql_query($query);
  return mysql_affected_rows();
}


function jtmysql_getListOfAllContact(){
  $query="SELECT idContact,dnContact,nomSte FROM contact,entreprise WHERE contact.idSte=entreprise.idSte ORDER BY nomSte,dnContact";
  $listeContact=mysql_query($query);
  return $listeContact;
};

function jtmysql_getContact($idContact){
  $query="SELECT * FROM contact WHERE idContact='$idContact'";
  $result=mysql_query($query);
  $valuesArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $valuesArray;
}

function jtmysql_registerContact($idSte,$nomContact,$prenomContact,$fct,$mail,$tel,$mobile,$addresse,$notes){
  $dnContact=$nomContact . " " . $prenomContact;
  $query="INSERT INTO contact(idSte,dnContact,nomContact,prenomContact,fct,mail,tel,mobile,addresse,notes) VALUES ('$idSte','$dnContact','$nomContact','$prenomContact','$fct','$mail','$tel','$mobile','$addresse','$notes')";
  mysql_query($query);
  return mysql_affected_rows();
}

function jtmysql_modifyContact($idContact,$idSte,$nomContact,$prenomContact,$fct,$mail,$tel,$mobile,$addresse,$notes){
  $dnContact=$nomContact . " " . $prenomContact;
  $query="UPDATE contact SET idSte='$idSte', dnContact='$dnContact', nomContact='$nomContact',prenomContact='$prenomContact',fct='$fct',mail='$mail',tel='$tel',mobile='$mobile',addresse='$addresse', notes='$notes' WHERE idContact='$idContact'";

  debug($query);
  mysql_query($query);
  return mysql_affected_rows();
}

function jtmysql_get_idContact_from_dnContact($dnContact){
  $query="SELECT idContact FROM contact WHERE dnContact='$dnContact' ";
  $result=mysql_query($query);
  $valuesArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $valuesArray['idContact'];
}

function jtmysql_get_dnContact_from_idContact($idContact) {
  $query="SELECT dnContact FROM contact WHERE idContact='$idContact' ";
  $result=mysql_query($query);
  $valuesArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);
  return $valuesArray['dnContact'];
}


function jtmysql_getDoc($idDoc){
  $query="SELECT * FROM document WHERE idDoc='$idDoc'";
  $result=mysql_query($query);
  $resultArray = mysql_fetch_array($result,MYSQL_ASSOC);
  mysql_free_result($result);  
  return $resultArray;
}

function jtmysql_registerDoc($owner,$id,$descrDoc,$docPath){
  if ($owner == 'Ste') {
    $idlabel='idSte';
  } else {
    $idlabel='idContact';
  }

  $query = "INSERT INTO document($idlabel,descrDoc,docPath) VALUES ('$id','$descrDoc','$docPath')";
  mysql_query($query);
  return mysql_affected_rows();
}

function jtmysql_modifyDoc($idDoc,$owner,$id,$descrDoc,$docPath){
  if ($owner == 'Ste') {
    $idlabel='idSte';
  } else {
    $idlabel='idContact';
  }
  $query = "UPDATE document SET $idlabel='$id', descrDoc='$descrDoc'";
  if ($docPath != '') {
    $query .=",docPath='$docPath'";
  }
  $query .=" WHERE idDoc='$idDoc'";
  mysql_query($query);
  return mysql_affected_rows();

}

function jtmysql_getSteDocs($idSte){
  $query="SELECT * FROM document WHERE idSte='$idSte'";
  $result=mysql_query($query);
  return $result;
}

function jtmysql_getCntDocs($idContact){
  $query="SELECT * FROM document WHERE idContact='$idContact'";
  $result=mysql_query($query);
  return $result;
}



?>