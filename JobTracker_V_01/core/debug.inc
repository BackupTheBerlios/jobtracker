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