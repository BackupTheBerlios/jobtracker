<?php

  // includes

include './core/debug.inc';
include './core/jtui.inc';
include './core/jtengine.inc';
include './core/jtmysql.inc';


// assign parameters

$action=$_GET['action'];

debug_getpost();
// main section

switch($action) {  

 case 'listOpenCandidature' :
   jtengine_listCandidature('open');
   break;
 case 'listProspect' :
   jtengine_listCandidature('prospection');
   break;
 case 'listAllCandidature' :
   jtengine_listCandidature('all');
   break;
 case 'addCandidature' :
   jtengine_display_candidatureEditForm('');
   break;

 case 'viewCandidature' :
   jtengine_display_candidature($_GET['idCandidature']);
   break;
 case 'editCandidature' :
   jtengine_display_candidatureEditForm($_POST);
   break;
 case 'registerCandidature' :
   jtengine_registerCandidature($_POST);
   break;
 case 'modifyCandidature' :
   jtengine_modifyCandidature($_POST);
   break;

 case 'addEvent' :
   /* fall through */
 case 'editEvent' :
   jtengine_display_eventEditForm($_POST);
   break;
 case 'registerEvent' :
   jtengine_registerEvent($_POST);
   break;
 case 'modifyEvent' :
   jtengine_modifyEvent($_POST);
   break;
   
 case 'listSte' :
   jtengine_listSte();
   break;
 case 'viewSte' :
   jtengine_display_ste($_GET['idSte']);
   break;
 case 'addSte' :
   jtengine_display_steEditForm('');
   break;
 case 'editSte' :
   jtengine_display_steEditForm($_POST);
   break;
 case 'registerSte' :
   jtengine_registerSte($_POST);
   break;
 case 'modifySte' :
   jtengine_modifySte($_POST);
   break;

 case 'addDoc' :
   /* fall through */
 case 'editDoc' :
   jtengine_display_docEditForm($_POST);
   break;
 case 'registerDoc' :
   jtengine_registerDoc($_POST);
   break;
 case 'modifyDoc' :
   jtengine_modifyDoc($_POST);
   break;

 case 'listContact' :
   jtengine_listContact();
   break;
 case 'viewContact' :
   jtengine_display_contact($_GET['idContact']);
   break;
 case 'addContact' :
   jtengine_display_contactEditForm('');
   break;
 case 'editContact' :
   jtengine_display_contactEditForm($_POST);
   break;
 case 'registerContact' :
   jtengine_registerContact($_POST);
   break;
 case 'modifyContact' :
   jtengine_modifyContact($_POST);
   break;
   
 default :
   jtengine_display_homepage();
   break;
}

?>
