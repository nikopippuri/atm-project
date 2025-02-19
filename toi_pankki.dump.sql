-- MySQL dump 10.13  Distrib 8.0.38, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: toi_pankki
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `account_id` int NOT NULL AUTO_INCREMENT,
  `balance` decimal(10,2) NOT NULL DEFAULT '0.00',
  `account_type` enum('debit','credit') NOT NULL,
  `card_id` int NOT NULL,
  PRIMARY KEY (`account_id`),
  KEY `account_card_idx` (`card_id`),
  CONSTRAINT `account_card` FOREIGN KEY (`card_id`) REFERENCES `card` (`card_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,330.00,'debit',1),(2,817.00,'credit',2),(3,980.00,'debit',3),(4,800.00,'credit',3);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `card_id` int NOT NULL AUTO_INCREMENT,
  `pin` varchar(255) NOT NULL,
  `locked` tinyint(1) NOT NULL DEFAULT '0',
  `try_left` int NOT NULL DEFAULT '3',
  `card_type` enum('debit','credit','combo') NOT NULL,
  `customer_id` int NOT NULL,
  PRIMARY KEY (`card_id`),
  KEY `card_customer_idx` (`customer_id`),
  CONSTRAINT `card_customer` FOREIGN KEY (`customer_id`) REFERENCES `customer` (`customer_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,'$2b$10$KTKGTyhtKDyQgPV0ZhlrEOvn2cK0Jph7ldTDRV0D5hy3RW1wMy7Ne',0,3,'debit',1),(2,'$2a$10$lFw/AqQtbc3PtJ2aIRgvku.yFkOhWJt1OMBlmFI5ZTy0zI/h0Phge',0,3,'credit',2),(3,'$2a$10$7cYv9scd/aALNlEGBVF22uOrPPh.9e0KOVDiJv.w4DttiZ3TKGAvi',0,3,'combo',3);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `customer_id` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) NOT NULL,
  `lname` varchar(45) NOT NULL,
  PRIMARY KEY (`customer_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Matti','Meikäläinen'),(2,'Maija','Mehiläinen'),(3,'Jari','Korhonen');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `transaction_id` int NOT NULL AUTO_INCREMENT,
  `sum` decimal(10,2) NOT NULL,
  `timestamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `account_id` int NOT NULL,
  PRIMARY KEY (`transaction_id`),
  KEY `transaction_account_idx` (`account_id`),
  CONSTRAINT `transaction_account` FOREIGN KEY (`account_id`) REFERENCES `account` (`account_id`)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,-50.00,'2025-02-09 17:43:10',1),(2,-20.00,'2025-02-09 19:26:24',1),(3,-20.00,'2025-02-09 19:40:35',1),(4,-20.00,'2025-02-09 19:40:36',1),(5,-20.00,'2025-02-09 19:40:37',1),(6,-20.00,'2025-02-09 19:40:38',1),(7,-20.00,'2025-02-09 19:40:38',1),(8,-20.00,'2025-02-09 19:40:38',1),(9,-20.00,'2025-02-09 19:40:39',1),(10,-20.00,'2025-02-09 19:40:39',1),(11,-20.00,'2025-02-09 19:40:39',1),(12,-20.00,'2025-02-09 19:40:39',1),(13,-20.00,'2025-02-09 19:40:39',1),(14,-20.00,'2025-02-09 19:40:39',1),(15,-20.00,'2025-02-09 19:40:40',1),(16,-20.00,'2025-02-09 19:40:40',1),(17,-20.00,'2025-02-09 19:40:40',1),(18,-20.00,'2025-02-09 19:40:40',1),(19,-20.00,'2025-02-09 19:40:40',1),(20,-20.00,'2025-02-09 19:40:40',1),(21,-20.00,'2025-02-09 19:40:40',1),(22,-20.00,'2025-02-09 19:40:41',1),(23,-20.00,'2025-02-09 19:40:41',1),(24,-20.00,'2025-02-09 19:40:41',1),(25,-20.00,'2025-02-09 19:40:41',1),(26,-20.00,'2025-02-09 19:40:41',1),(27,-20.00,'2025-02-09 19:40:41',1),(28,-20.00,'2025-02-09 19:40:41',1),(29,-200.00,'2025-02-10 16:26:08',4),(30,-20.00,'2025-02-10 16:26:37',3),(31,-40.00,'2025-02-10 16:27:51',2),(32,-20.00,'2025-02-10 16:36:32',1),(33,-40.00,'2025-02-10 17:27:36',1),(34,-20.00,'2025-02-10 19:08:17',1),(35,-20.00,'2025-02-10 19:09:23',2),(36,-123.00,'2025-02-10 19:09:27',2);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'toi_pankki'
--
/*!50003 DROP PROCEDURE IF EXISTS `withdrawal` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `withdrawal`(
    IN p_account_id INT, 
    IN p_amount DECIMAL(10, 2)
)
BEGIN
    DECLARE current_balance DECIMAL(10, 2);
    
     IF p_amount < 20 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Minimum withdrawal amount is 20 euros';
    END IF;
    
    SELECT balance INTO current_balance
    FROM account
    WHERE account_id = p_account_id;
    
    IF current_balance IS NULL THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Account not found';
    ELSEIF current_balance < p_amount THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Saldo ei riitä';
    ELSE
        
        UPDATE account
        SET balance = current_balance - p_amount
        WHERE account_id = p_account_id;
        
        INSERT INTO transaction (account_id, sum, timestamp)
        VALUES (p_account_id, -p_amount, NOW());
        
        SELECT 'Nosto onnistui' AS message, current_balance - p_amount AS new_balance;
    END IF;
    END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-02-10 21:13:03
