<?php
/*******************************************************************************
 *
 * JobTracker : outil de gestion et suivi de candidature
 *
 * Copyright (C) 2004  MANSOUR
 *
 * Cette bibliothèque est libre, vous pouvez la redistribuer et/ou la modifier 
 * selon les termes de la Licence Publique Générale GNU Limitée publiée par la 
 * Free Software Foundation (version 2 ou bien toute autre version ultérieure 
 * choisie par vous).
 *
 * Cette bibliothèque est distribuée car potentiellement utile, mais SANS AUCUNE
 * GARANTIE, ni explicite ni implicite, y compris les garanties de 
 * commercialisation ou d'adaptation dans un but spécifique. Reportez-vous à la 
 * Licence Publique Générale GNU Limitée pour plus de détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU Limitée 
 * en même temps que cette bibliothèque; si ce n'est pas le cas, écrivez à la 
 * Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307, Etats-Unis. 
 *
 *
 * pour prendre contact avec les développeurs : jobtracker-dev@lists.berlios.de
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

  /*
   DEBUG variable
   
   0 : debug output disabled
   1 : debug info inserted as html comments
   2 : debug info displayed as pre formated text in browser

   FUNCTIONTRACE variable

   FALSE : ouput disabled
   TRUE  : trace entering and leaving functions

  */

$DEBUG=1;
$FUNCTIONTRACE=FALSE;

function begin_debug(){
  if ($GLOBALS['DEBUG']>0) {
    print("\n<!-- DEBUG");
    if ($GLOBALS['DEBUG']>1) {
      print("-->\n<b><pre>");
    } else {
      print("\n");
    }
  }
}

function end_debug(){ 
  if ($GLOBALS['DEBUG']>0) {
    if ($GLOBALS['DEBUG']>1) {
      print(" </pre></b>\n");
    } else {
      print ("-->\n");
    }
  }
}

function log_debug($str) {
  if ($GLOBALS['DEBUG']>0) {
    print ("D: $str\n");
  }
}

function debug($str) {
  begin_debug();
  log_debug($str);
  end_debug();
}

function debug_enter($str) {
  if ($GLOBALS['FUNCTIONTRACE']){
    debug("}} $str()");
  }
}

function debug_leave($str) {
  if ($GLOBALS['FUNCTIONTRACE']){
    debug("{{ $str()");
  }
}

function debug_dumparray ($par) {
  reset ($par);
  while (list ($key, $val) = each ($par)) {
    log_debug("$key = $val");
  }
  reset ($par);
}

function debug_get(){
  begin_debug();
  log_debug('$_GET');
  debug_dumparray($_GET);
  end_debug();
}

function debug_post(){
  begin_debug();
  log_debug('$_POST');
  debug_dumparray($_POST);
  end_debug();
}

function debug_getpost(){
  debug_get();
  debug_post();
}

function debug_array($array){
  begin_debug();
  debug_dumparray($array);
  end_debug();
}
?>