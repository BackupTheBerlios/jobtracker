#
# 08/02/2004  M   version initiale
#

                                   +-----------------+
                                   | JobTracker V0.1 |
                                   +-----------------+

                                        README
                                       +------+


PRE-REQUIS
===========

un serveur web avec support php
un serveur mysql
un navigateur web


CONFIGURATION VALIDEE
=====================

Pour l'instant l'appli a été testée avec une installation de EasyPhp 1.7
qui contient un serveur apache 1.3.27, php 4.3.3 et mysql 4.0.15. 

EasyPhp peut-être téléchargé et utilisé gratuitement sur le site http://www.easyphp.org/

Le navigateur utilisé est mozilla firebird 0.7


INSTALLATION
=============

- installer et démarrer easyphp 
- decompresser l'archive de jobtracker 
- ceci donne un repertoire Jobtracker, qu'il faut placer dans le répertoire EasyPHP1-7\www
- créer une base de donnée et un utilisateur dédié (*)
- mettre à jour avec ces paramètres les fichiers :

  Jobtracker/setup/jt_db_setup.ini 
  Jobtracker/setup/jt_db_setup.bat 
  Jobtracker/setup/jt_db_reset.bat 

- lancer Jobtracker/setup/jt_db_setup.bat qui va créer les tables nécessaires (**)
- Jobtracker est accessible dans votre navigateur via l'URL

                   http://localhost/Jobtracker


(*)  Par défaut, la base de donnée est 'jobtracker', l'utilisateur et 'jt', le mot de passe est 'jt'


(**) On peut lancer Jobtracker/setup/jt_db_reset.bat pour effacer toutes les tables et les reconstruire.



ENJOY ! ;-)

M.