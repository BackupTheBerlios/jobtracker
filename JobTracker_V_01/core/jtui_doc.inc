<?php

function jtui_formatDocs($owner,$id){
  
  if($owner == 'Ste') {
    $result = jtmysql_getSteDocs($id);
  } else {
    $result = jtmysql_getCntDocs($id);
  }
  
  $docsTable = "<table>\n";
  $docsTable = $docsTable . "\t<tr>\n";
  $docsTable = $docsTable . "\t\t<th class=\"doc\">Description</th>\n";
  $docsTable = $docsTable . "\t\t<th class=\"doc\">Document</th>\n";
  $docsTable = $docsTable . "\t\t<th class=\"doc\"></th>\n";
  $docsTable = $docsTable . "\t</tr>\n";
  
  while($doc=mysql_fetch_array($result,MYSQL_ASSOC)){
    $docPath=$doc['docPath'];
    $docsTable = $docsTable . "\t<tr>\n";
    $docsTable = $docsTable . "\t\t<td>$doc[descrDoc]</td>\n";
    $docsTable = $docsTable . "\t\t<td><a href=\"$docPath\" TARGET=\"_blank\">" . basename($docPath) . "</a></td>\n";
    $docsTable = $docsTable . "\t\t<td><form method=post action=index.php?action=editDoc>\n
 \t\t    <input type=hidden name=idDoc value=\"$doc[idDoc]\"><input type=submit value=\"modifier\">\n
 \t\t    </form>\n\t\t</td>\n";
    $docsTable = $docsTable . "\t</tr>\n";
  }
  $docsTable = $docsTable . "</table>\n";

  jtmysql_free($result);

  return $docsTable;
}


function jtui_display_docEditForm($owner,$id,$valuesArray){

  if ($owner=='Ste'){
    $idSte=$id;
    $nomSte=jtmysql_get_nomSte_from_idSte($idSte);
    $metachar = array("\\","/","*",":","?","\"","|","<",">");
    $ref = "ste_" . str_replace($metachar,"_",$nomSte);  
    $formname="docForm";
    if ($valuesArray['idDoc'] == ''){
      $editForm = " <h2>Ajouter un nouveau document à l'entreprise : $nomSte</h2>\n";
      $action='registerDoc';
    } else {
      $editForm = " <h2>Modification d'un document de l'entreprise : $nomSte</h2>\n";
      $action ='modifyDoc';
    }
  }else {
    $idContact=$id;
    $dnContact=jtmysql_get_dnContact_from_idContact($idContact);
    $metachar = array("\\","/","*",":","?","\"","|","<",">");
    $ref = "cnt_" . str_replace($metachar,"_",$dnContact);  
    $formname="docForm";
    if ($valuesArray['idDoc'] == ''){
      $editForm = " <h2>Ajouter un nouveau document au contact : $dnContact</h2>\n";
      $action='registerDoc';
    } else {
      $editForm = " <h2>Modification d'un document du contact : $dnContact</h2>\n";
      $action ='modifyDoc';
    }
  }  
  
  $doc="$valuesArray[docPath]";
  
  if (is_file($doc)) {
    $docfield="<a href=\"$doc\" TARGET=\"_blank\">" . basename($doc) . "</a>";
  } else {
    $docfield  = "<pre>s&eacute;lectionner un fichier existant </pre><input type=file name=docPath \">";
    $docfield .= "<pre>ou cr&eacute;er un nouveau fichier texte</pre><input type=text name=newFile>";
    $docfield .= "<input type=button value=\"cr&eacute;er\" 
 onClick=\"window.open('./core/addDoc.php?form=$formname&elem=newFile&ref=$ref','Nouveau document','width=440,height=250')\">";
  }
    
  $editForm = $editForm ."<form enctype=\"multipart/form-data\" method=post action=index.php?action=$action name=\"$formname\">
     <table>\n
     \t<tr>\n\t\t<td>Description</td>\n\t\t<td><input type=text name=descrDoc value=\"$valuesArray[descrDoc]\"></td>\n\t</tr>\n
     \t<tr>\n\t\t<td>Document</td>\n\t\t<td>$docfield</td>\n\t</tr>\n
 </table>\n
 
 <br>\n";
  if ($owner=='Ste'){
    $editForm .= "<input type=hidden name=idSte value=\"$idSte\">\n";
  } else {
    $editForm .= "<input type=hidden name=idContact value=\"$idContact\">\n";
  }
  
  $editForm .= "<input type=hidden name=idDoc value=\"$valuesArray[idDoc]\">\n
 <input type=submit value=\"enregistrer\">\n
 </form>\n
 ";

  jtui_display_page($editForm);
}


?>