<?php

function jtui_display_header(){

  $header="
 <html>\n
 <head>\n
 <link type=\"text/css\" rel=\"stylesheet\" href=\"jtstyle.css\" />\n
 </head>\n
 <body>\n 
 ";
  
  print($header);
}

function jtui_display_footer(){
  $footer="
 <div class=\"footer\">JobTracker v0.1</div>\n 
 </body>\n
 </html>\n";
  
  print($footer);
}

function jtui_display_title(){
  $title="<h1>JobTracker</h1>\n";
  print($title);
};


function jtui_display_navbar(){
  
  $navbar="
 <div class=\"navbar\">
 <table class=\"navbar\"><tr>
 <td class=\"navbar2\"><img src=\"./images/back.gif\" onClick=\"history.back()\"></td>
 <td class=\"navbar1\"><a class=\"navbar\" href=\"./index.php\">retour menu</a></td>
 </tr></table></div>\n
 ";

  print($navbar);
};


function jtui_display_tableWLinkOnFirst($result,$action,$field) {
  
  $output = " <table>\n";

  if($action=='viewCandidature'){
    $output = $output . "\t<tr>\n\t\t<th>Référence</th>\n\t\t<th>Entreprise</th>\n\t\t<th>Poste</th>\n\t\t<th>Etat</th>\n\t\t<th></th>\t\n\n</tr>\n";
  }

  while($line=mysql_fetch_array($result, MYSQL_NUM))
    { 

      $output= $output . "\t<tr>\n";
      
      $length = count($line);

      for($i=1 ; $i< $length; $i++){	
	$output = $output . "\t\t<td>$line[$i]</td>\n";
      }
      
      $output = $output . "\t\t<td class=\"linkcell\"><a href=\"./index.php?action=$action&$field=$line[0]\">voir detail</a></td>\n";
      
      $output = $output . "\t</tr>\n";
    }
  
  $output = $output . " </table>";

  return $output;
};

function jtui_display_table($labelArray,$fieldsArray,$valueArray) {
  
  $output = " <table>\n";

  $lenght = count($labelArray);
  for($i = 0; $i < $lenght; $i++){
  
    $output= $output . "\t<tr>\n";
    $output = $output . "\t\t<td class=\"label\">$labelArray[$i]</td>\n";
    $field = $fieldsArray[$i];
    $output = $output . "\t\t<td>";

    switch ($field) {
    case 'notes' : /* fall through */
    case 'addresse' : /* fall through */
    case 'siege' :
      $output = $output . "<pre>$valueArray[$field]</pre>";
      break;
    case 'nomSte' :
      $idSte = jtmysql_get_idSte_from_nomSte($valueArray['nomSte']);
      $output = $output . "<a href=\"index.php?action=viewSte&idSte=$idSte\" class=\"mail\">$valueArray[$field]</a>";
      break;
    case 'url' :
      $output = $output . "<a href=\"$valueArray[$field]\" target=\"_BLANK\">$valueArray[$field]</a>";
      break;
    case 'mail' :
      $output = $output . "<a href=\"mailto:$valueArray[$field]\" class=\"mail\">$valueArray[$field]</a>";
      break;
    default :
      $output = $output . "$valueArray[$field]";
    }

    $output = $output . "</td>\n\t</tr>\n";
  }
  
  $output = $output . " </table>\n";
  
  return $output;
};


function jtui_display_form($action,$labelsArray,$fieldsArray,$valuesArray,$hiddenArray){

  $output = " <form method=\"post\" action=\"./index.php?action=$action\">\n";
  $output = $output . "<table>\n";

  $lenght = count($labelsArray);

  for ($i = 0; $i < $lenght; $i++) {

    $output = $output . "\t<tr ";

    if($fieldsArray[$i] == 'notes'){
      $output = $output . "class=\"notesBox\" ";
    }
    
    $output = $output . ">\n\t\t<td>$labelsArray[$i]</td>\n";
    $output = $output . "\t\t<td> ";
    
    if($fieldsArray[$i] == 'notes'){
      $output = $output . "<textarea rows=\"8\" cols=\"80\" name=\"$fieldsArray[$i]\">";
      if ($valuesArray != '') {
	$output = $output . "$valuesArray[$i]";
      }
      $output = $output . "</textarea>";
    } else if($fieldsArray[$i] == 'siege'){
      $output = $output . "<textarea rows=\"2\" cols=\"30\" name=\"$fieldsArray[$i]\">";
      if ($valuesArray != '') {
	$output = $output . "$valuesArray[$i]";
      }
      $output = $output . "</textarea>";
    } else {
      $output = $output . "<input type=\"text\" name=\"$fieldsArray[$i]\" ";
      if ($valuesArray != '') {
	$output = $output . "value=\"$valuesArray[$i]\" ";
      }
      $output = $output . ">";
    }
    
    $output = $output . "</td>\n\t</tr>";
  }

  $output = $output . "</table>";
  $output = $output . "<br>\n";
  if ($hiddenArray != '') {
    while (list ($key, $val) = each ($hiddenArray)) {
      $output = $output . "<input type=\"hidden\" name=\"$key\" value=\"$val\">\n";
    }
  }
  $output = $output . "<input type=submit value=\"enregistrer\">";
  $output = $output . "</form>";
  

  return $output;
}

function buildSelectBoxOfSte($default) {
  $listofstebox = "<select name=\"nomSte\">\n";
  $listofstebox = $listofstebox . "<option value=\"$default\">$default</option>\n";
  if($default != '') {
    $listofstebox = $listofstebox . "<option value=\"\"> </option>\n";
  }
  
  $result = jtmysql_getListOfAllSte();
  
  while($line=mysql_fetch_array($result)){
    $ste=$line['nomSte'];
    if ($ste != $default) {
      $listofstebox = $listofstebox . "<option value=\"$ste\">$ste</option>\n";
    }
  }
  
  jtmysql_free($result);

  return $listofstebox;
}

function buildSelectBoxOfContact($default) {
  $listofcontactbox = "<select name=\"dnContact\">\n";
  $listofcontactbox = $listofcontactbox . "<option value=\"$default\">$default</option>\n";

  if($default != '') {
    $listofstebox = $listofstebox . "<option value=\"\"> </option>\n";
  }

  $result = jtmysql_getListOfAllContact();
  
  while($line=mysql_fetch_array($result)){
    $contact=$line['dnContact'];
    if ($contact != $default) {
      $listofcontactbox = $listofcontactbox . "<option value=\"$contact\">$contact</option>\n";
    }
  }
  
  jtmysql_free($result);

  return $listofcontactbox;
}
?>