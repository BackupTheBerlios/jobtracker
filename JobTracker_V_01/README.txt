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

Pour l'instant l'appli a �t� test�e avec une installation de EasyPhp 1.7
qui contient un serveur apache 1.3.27, php 4.3.3 et mysql 4.0.15. 

EasyPhp peut-�tre t�l�charg� et utilis� gratuitement sur le site http://www.easyphp.org/

Le navigateur utilis� est mozilla firebird 0.7


INSTALLATION
=============

- installer et d�marrer easyphp 
- decompresser l'archive de jobtracker 
- ceci donne un repertoire Jobtracker, qu'il faut placer dans le r�pertoire EasyPHP1-7\www
- cr�er une base de donn�e et un utilisateur d�di� (*)
- mettre � jour avec ces param�tres les fichiers :

  Jobtracker/setup/jt_db_setup.ini 
  Jobtracker/setup/jt_db_setup.bat 
  Jobtracker/setup/jt_db_reset.bat 

- lancer Jobtracker/setup/jt_db_setup.bat qui va cr�er les tables n�cessaires (**)
- Jobtracker est accessible dans votre navigateur via l'URL

                   http://localhost/Jobtracker


(*)  Par d�faut, la base de donn�e est 'jobtracker', l'utilisateur et 'jt', le mot de passe est 'jt'


(**) On peut lancer Jobtracker/setup/jt_db_reset.bat pour effacer toutes les tables et les reconstruire.



ENJOY ! ;-)

M.