<?php

function jtengine_display_docEditForm($valuesArray){
  if (array_key_exists('idDoc',$valuesArray)) {
    /* modify box */
    $idDoc   = $valuesArray['idDoc'];
    $values  = jtmysql_getDoc($idDoc);
    $id      = $values['idSte'];

    if ($id != '') {
      $owner='Ste';
    }else{
      $id = $values['idContact'];
      $owner='Cnt';
    }
  }else {
    /* new add box */
    $id = $valuesArray['idSte'];
    if ($id != '') {
      $owner='Ste';
    }else{
      $id = $valuesArray['idContact'];
      $owner='Cnt';
    }
    $values=array(idDoc=>'',descrDoc=>'',docPath=>'');
  }

  jtui_display_docEditForm($owner,$id,$values);
}

function jtengine_registerDoc($valuesArray){

  $descrDoc    = addslashes($valuesArray['descrDoc']);
  $metachar=array("\\","/","*",":","?","\"","|","<",">");
  $id = $valuesArray['idSte'];
  if ($id != '') {
    $owner='Ste';
    $nomSte = str_replace($metachar,"_",jtmysql_get_nomSte_from_idSte($id));  
    $destDir        = "./data/ste_" . $nomSte;
  }else {
    $owner='Cnt';
    $id = $valuesArray['idContact'];
    $dnContact = str_replace($metachar,"_",jtmysql_get_dnContact_from_idContact($id));
    $destDir        = "./data/cnt_" . $dnContact;
  }


  $newFile = addslashes($valuesArray['newFile']);
  if ($newFile != '') {
    $target=$newFile;
  } else if ($_FILES != '') {
    $doc            = $_FILES['docPath'];
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

  $nbRows        = jtmysql_registerDoc($owner,$id,$descrDoc,$target);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }

  if ($owner=='Ste') {
    jtui_display_update($nbRows,'création',$message,'viewSte','idSte',$id);
  } else {
    jtui_display_update($nbRows,'création',$message,'viewContact','idContact',$id);
  }
  
}

function jtengine_modifyDoc($valuesArray){
  $idDoc       = addslashes($valuesArray['idDoc']);
  $descrDoc    = addslashes($valuesArray['descrDoc']);

  $metachar=array("\\","/","*",":","?","\"","|","<",">");
  $id = $valuesArray['idSte'];
  if ($id != '') {
    $owner='Ste';
    $nomSte = str_replace($metachar,"_",jtmysql_get_nomSte_from_idSte($id));  
    $destDir        = "./data/ste_" . $nomSte;
  }else {
    $owner='Cnt';
    $id = $valuesArray['idContact'];
    $dnContact = str_replace($metachar,"_",jtmysql_get_dnContact_from_idContact($id));
    $destDir        = "./data/cnt_" . $dnContact;
  }

  if ($_FILES != '') {
    $doc            = $_FILES['docPath'];
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
  
  $nbRows        = jtmysql_modifyDoc($idDoc,$owner,$id,$descrDoc,$target);

  if($nbRows == -1){
    $message = jtmysql_getErrorMessage();
  }

  if ($owner=='Ste') {
    jtui_display_update($nbRows,'mise à jour',$message,'viewSte','idSte',$id);
  } else {
    jtui_display_update($nbRows,'mise à jour',$message,'viewContact','idContact',$id);
  }
}


?>