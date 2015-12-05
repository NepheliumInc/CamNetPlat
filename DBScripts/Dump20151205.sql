CREATE DATABASE  IF NOT EXISTS `camera` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `camera`;
-- MySQL dump 10.13  Distrib 5.6.24, for Win64 (x86_64)
--
-- Host: localhost    Database: camera
-- ------------------------------------------------------
-- Server version	5.6.26-log

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
-- Table structure for table `cam14_video`
--

DROP TABLE IF EXISTS `cam14_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam14_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cam1_video`
--

DROP TABLE IF EXISTS `cam1_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam1_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cam22_video`
--

DROP TABLE IF EXISTS `cam22_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam22_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cam23_video`
--

DROP TABLE IF EXISTS `cam23_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam23_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cam28_video`
--

DROP TABLE IF EXISTS `cam28_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam28_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cam29_video`
--

DROP TABLE IF EXISTS `cam29_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam29_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cam6_video`
--

DROP TABLE IF EXISTS `cam6_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam6_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=357 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cam7_video`
--

DROP TABLE IF EXISTS `cam7_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cam7_video` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_1`
--

DROP TABLE IF EXISTS `camera_node_1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_1` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_14`
--

DROP TABLE IF EXISTS `camera_node_14`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_14` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_14_log`
--

DROP TABLE IF EXISTS `camera_node_14_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_14_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=11543 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_1_log`
--

DROP TABLE IF EXISTS `camera_node_1_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_1_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=9272 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_22`
--

DROP TABLE IF EXISTS `camera_node_22`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_22` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_22_log`
--

DROP TABLE IF EXISTS `camera_node_22_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_22_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=14378 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_23`
--

DROP TABLE IF EXISTS `camera_node_23`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_23` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_23_log`
--

DROP TABLE IF EXISTS `camera_node_23_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_23_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_28`
--

DROP TABLE IF EXISTS `camera_node_28`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_28` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_28_log`
--

DROP TABLE IF EXISTS `camera_node_28_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_28_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_29`
--

DROP TABLE IF EXISTS `camera_node_29`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_29` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_29_log`
--

DROP TABLE IF EXISTS `camera_node_29_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_29_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=6667 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_6`
--

DROP TABLE IF EXISTS `camera_node_6`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_6` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_6_log`
--

DROP TABLE IF EXISTS `camera_node_6_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_6_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=8314 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = cp850 */ ;
/*!50003 SET character_set_results = cp850 */ ;
/*!50003 SET collation_connection  = cp850_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER insertingToCameraNode6Log
BEFORE INSERT ON camera_node_6_log FOR EACH ROW
BEGIN
    IF NOT EXISTS(SELECT * FROM camera_node_6_log WHERE NEW.Profile_ID = Profile_ID AND NEW.TimeStamp = TimeStamp) 
    THEN
      INSERT INTO cam6_video(Video_ID, Profile_ID, TimeStamp) VALUES(NEW.Video_ID, NEW.Profile_ID, NEW.TimeStamp);
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `camera_node_7`
--

DROP TABLE IF EXISTS `camera_node_7`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_7` (
  `Record_ID` int(11) NOT NULL,
  `Video_ID` int(11) NOT NULL,
  `Profile_ID` varchar(10) NOT NULL,
  `TimeStamp` double NOT NULL,
  `Blob_Center_Point` varchar(10) NOT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `camera_node_7_log`
--

DROP TABLE IF EXISTS `camera_node_7_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `camera_node_7_log` (
  `Record_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Video_ID` int(11) DEFAULT NULL,
  `Profile_ID` varchar(10) DEFAULT NULL,
  `TimeStamp` double DEFAULT NULL,
  PRIMARY KEY (`Record_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=5579 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping routines for database 'camera'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-12-05  8:41:00
