CREATE DATABASE  IF NOT EXISTS `sarasvati` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `sarasvati`;
-- MySQL dump 10.13  Distrib 5.5.52, for debian-linux-gnu (x86_64)
--
-- Host: 127.0.0.1    Database: sarasvati
-- ------------------------------------------------------
-- Server version	5.5.52-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `data`
--

DROP TABLE IF EXISTS `data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `data` (
  `id_env` int(11) NOT NULL,
  `register` varchar(5) NOT NULL,
  `value` float NOT NULL DEFAULT '0',
  `create_by` varchar(45) NOT NULL,
  `update_by` varchar(45) NOT NULL,
  `create_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `update_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id_env`,`register`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'1001',1.1001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1003',2.3001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1005',3.5001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1007',4.7001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1009',5.8001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1011',6.9001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-10-03 02:46:27'),(1,'1013',7.1101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1015',8.1501,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1017',9.1701,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1019',10.1901,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(1,'1021',11.2101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1001',1.1001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1003',2.3001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1005',3.5001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1007',4.7001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1009',5.9001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1011',6.1101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1013',7.1301,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1015',8.1501,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1017',9.1701,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1019',10.1901,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(2,'1021',11.2101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1001',1.1001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'10011',6.9001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1003',2.3001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1005',3.5001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1007',4.7001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1009',5.8001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1013',7.1101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1015',8.1501,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1017',9.1701,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1019',10.1901,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(3,'1021',11.2101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1001',1.1001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1003',2.3001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1005',3.5001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1007',4.7001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1009',5.9001,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1011',6.1101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1013',7.1301,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1015',8.1501,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1017',9.1701,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1019',10.1901,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02'),(4,'1021',11.2101,'root@localhost','root@localhost','2016-09-29 10:57:02','2016-09-29 10:57:02');
/*!40000 ALTER TABLE `data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `environment`
--

DROP TABLE IF EXISTS `environment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `environment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_user` int(11) NOT NULL DEFAULT '0',
  `module_name` varchar(45) NOT NULL,
  `serial_number` varchar(45) NOT NULL,
  `latitude` float DEFAULT NULL,
  `longitude` float DEFAULT NULL,
  `server` varchar(45) DEFAULT NULL,
  `file` varchar(45) DEFAULT NULL,
  `web_client` int(1) NOT NULL DEFAULT '0',
  `interval` int(11) NOT NULL DEFAULT '0',
  `create_by` varchar(45) NOT NULL,
  `update_by` varchar(45) NOT NULL,
  `create_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `update_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `environment`
--

LOCK TABLES `environment` WRITE;
/*!40000 ALTER TABLE `environment` DISABLE KEYS */;
INSERT INTO `environment` VALUES (1,1,'Module 1','RTU.01',-6.40333,106.888,'119.18.154.235','/ml.php',1,10,'root@localhost','root@localhost','2016-09-30 04:05:24','2016-10-03 04:06:33'),(2,1,'Module 2','RTU.02',-6.4,106.888,'119.18.154.235','/ml.php',0,5,'root@localhost','root@localhost','2016-09-30 04:05:24','2016-10-03 04:06:33'),(3,2,'Module 3','RTU.03',-6.40333,106.888,'119.18.154.235','/ml.php',1,3,'root@localhost','root@localhost','2016-09-30 04:05:24','2016-10-03 04:06:33'),(4,2,'Module 4','RTU.04',-6.4,106.888,'119.18.154.235','/ml.php',0,7,'root@localhost','root@localhost','2016-09-30 04:05:24','2016-10-03 04:06:33');
/*!40000 ALTER TABLE `environment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gsm`
--

DROP TABLE IF EXISTS `gsm`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gsm` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_env` int(11) NOT NULL,
  `operator` varchar(45) NOT NULL,
  `device_name` varchar(45) DEFAULT NULL,
  `status` int(11) NOT NULL DEFAULT '0',
  `communication` varchar(45) NOT NULL,
  `number` varchar(45) NOT NULL,
  `apn` varchar(45) DEFAULT NULL,
  `username` varchar(45) DEFAULT NULL,
  `password` varchar(45) DEFAULT NULL,
  `create_by` varchar(45) NOT NULL,
  `update_by` varchar(45) NOT NULL,
  `create_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `update_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gsm`
--

LOCK TABLES `gsm` WRITE;
/*!40000 ALTER TABLE `gsm` DISABLE KEYS */;
INSERT INTO `gsm` VALUES (1,1,'TELKOMSEL','Hape 1',0,'GSM','081234567890','tsel','tsel','tsel','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56'),(2,1,'3','Hape 2',1,'SMS','089678901234','3gprs','3gprs','3gprs','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56'),(3,2,'XL','HP.01',1,'GSM','081789012345','xlgprs','xlgprs','xlgprs','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56'),(4,2,'IM3','HP.02',0,'SMS','085566778899','isat','isat','isat','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56'),(5,3,'TELKOMSEL','Hape 1',0,'GSM','081234567890','tsel','tsel','tsel','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56'),(6,3,'3','Hape 2',1,'SMS','089678901234','3gprs','3gprs','3gprs','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56'),(7,4,'XL','HP.01',1,'GSM','081789012345','xlgprs','xlgprs','xlgprs','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56'),(8,4,'IM3','HP.02',0,'SMS','085566778899','isat','isat','isat','root@localhost','root@localhost','2016-09-29 10:25:56','2016-09-29 10:25:56');
/*!40000 ALTER TABLE `gsm` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(45) NOT NULL,
  `password` varchar(45) NOT NULL,
  `api_key` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,'admin1','admin1','abc123'),(2,'admin2','admin2','123abc');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-10-04 13:42:13
