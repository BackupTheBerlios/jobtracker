--
-- Script de creation des tables pour l'application JobTracker
--
-- 21/12/2003   M    version initiale
-- 12/01/2004   M    suppression groupe, ajout champ département dans candidature
--                   ajout table document

USE jobtracker

CREATE TABLE entreprise (
	idSte           int(11)     NOT NULL            auto_increment,
	nomSte          varchar(50) NOT NULL default '',
	activite        text,
	implantations   varchar(50)          default '',
	effectif        int(4)               default '',
	siege           varchar(70)          default '',
	url             varchar(50)          default '',
	notes           text,
	PRIMARY KEY (idSte),
	UNIQUE (nomSte)
) TYPE=MyISAM;

CREATE TABLE document (
	idDoc           int(11)     NOT NULL            auto_increment,	
	idSte           int(11)              default '' REFERENCES entreprise(idSte),
	idContact       int(11)              default '' REFERENCES contact(idContact),
	descrDoc        text,
	docPath         varchar(70)          default '',
	PRIMARY KEY (idDoc)    
) TYPE=MyISAM;

CREATE TABLE contact (
	idContact       int(11)     NOT NULL            auto_increment,	
 	idSte           int(11)                         REFERENCES entreprise(idSte),
	dnContact       varchar(99) NOT NULL default '',
	nomContact      varchar(49) NOT NULL default '',
	prenomContact   varchar(49) NOT NULL default '',
	fct             varchar(50)          default '',	
	mail            varchar(64)          default '',
	tel             varchar(30)          default '+(00) 0 00 00 00 00',
	mobile          varchar(30)          default '+(00) 0 00 00 00 00',
	addresse        varchar(70)          default '',
	notes           text,
	PRIMARY KEY (idContact),
	UNIQUE (dnContact)
) TYPE=MyISAM;


CREATE TABLE historique (
	idEvent         int(11)     NOT NULL            auto_increment,	
	idCandidature   int(11)              default '' REFERENCES candidature(idCandidature),
	idContact       int(11)                         REFERENCES contact(idContact),              
	dateEvent       datetime             default '0000-00-00 00:00:00',
	descrEvent      text,
	docPath         varchar(70)          default '',
	PRIMARY KEY (idEvent)    
) TYPE=MyISAM;


CREATE TABLE candidature (
	idCandidature   int(11)     NOT NULL            auto_increment,	
	refCandidature  varchar(20) NOT NULL default '',
 	idSte           int(11)                         REFERENCES entreprise(idSte),
	departement     varchar(50)          default '',
	poste           varchar(50)          default '',
	lieu            varchar(50)          default '',
	dateInit        date                 default '0000-00-00',
	dateMAJ         datetime             default '0000-00-00 00:00:00',
	etat            varchar(20) NOT NULL default 'prospection',
	origine         varchar(30)          default '',
	notes           text,
	PRIMARY KEY (idCandidature)
) TYPE=MyISAM;
