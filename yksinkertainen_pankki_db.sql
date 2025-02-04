-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: yksinkertainen_pankki
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
  `customer_id` int NOT NULL,
  PRIMARY KEY (`account_id`),
  KEY `customer_id` (`customer_id`),
  CONSTRAINT `account_ibfk_1` FOREIGN KEY (`customer_id`) REFERENCES `customer` (`customer_id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,1000.00,1),(2,1500.00,2),(3,2000.00,3),(4,500.00,4),(5,3000.00,5),(6,750.00,6),(7,1250.00,7),(8,400.00,8),(9,6000.00,9),(10,850.00,10);
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
  `locked` tinyint(1) DEFAULT '0',
  `try_left` int DEFAULT '3',
  `account_id` int NOT NULL,
  PRIMARY KEY (`card_id`),
  KEY `account_id` (`account_id`),
  CONSTRAINT `card_ibfk_1` FOREIGN KEY (`account_id`) REFERENCES `account` (`account_id`)
) ENGINE=InnoDB AUTO_INCREMENT=100 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,'$2b$10$WRaKiPR3IDffyJxo.vgL3u2WkVCx6G2oRp1iSVUuSmrBiLvwU6kcK',0,3,1),(2,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,2),(3,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,3),(4,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,4),(5,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,5),(6,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,6),(7,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,7),(8,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,8),(9,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,9),(10,'$2b$10$abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij',0,3,10);
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
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'John','Doe'),(2,'Jane','Smith'),(3,'Alice','Johnson'),(4,'Bob','Brown'),(5,'Charlie','Davis'),(6,'Diana','Evans'),(7,'Edward','Wilson'),(8,'Fiona','Miller'),(9,'George','Taylor'),(10,'Hannah','Anderson');
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
  KEY `account_id` (`account_id`),
  CONSTRAINT `transaction_ibfk_1` FOREIGN KEY (`account_id`) REFERENCES `account` (`account_id`)
) ENGINE=InnoDB AUTO_INCREMENT=77 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,-100.00,'2025-01-07 12:00:00',1),(2,-99.00,'2025-01-07 12:00:00',1),(3,100.00,'2025-01-03 10:00:00',2),(4,-10.00,'2025-01-04 11:00:00',3),(5,-200.00,'2025-01-05 12:00:00',4),(6,300.00,'2025-01-06 13:00:00',5),(7,-100.00,'2025-01-07 14:00:00',6),(8,50.00,'2025-01-08 15:00:00',7),(9,-500.00,'2025-01-09 16:00:00',8),(10,-100.00,'2025-01-10 17:00:00',9),(11,-100.00,'2025-01-07 12:00:00',1),(12,-100.00,'2025-01-07 12:00:00',1),(55,55.00,NULL,1),(66,66.00,'2025-01-07 12:00:00',1),(67,100.50,'2024-02-01 08:00:00',1),(68,-50.25,'2024-02-01 09:15:00',2),(69,200.00,'2024-02-01 10:30:00',3),(70,-75.75,'2024-02-01 11:45:00',1),(71,500.00,'2024-02-01 13:00:00',2),(72,-120.00,'2024-02-01 14:20:00',3),(73,60.00,'2024-02-01 15:40:00',1),(74,-30.50,'2024-02-01 16:55:00',2),(75,90.25,'2024-02-01 18:10:00',3),(76,-200.00,'2024-02-01 19:25:00',1);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'yksinkertainen_pankki'
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
        SET MESSAGE_TEXT = 'Insufficient funds';
    ELSE
        
        UPDATE account
        SET balance = current_balance - p_amount
        WHERE account_id = p_account_id;
        
        INSERT INTO transaction (account_id, sum, timestamp)
        VALUES (p_account_id, -p_amount, NOW());
        
        SELECT 'Withdrawal successful' AS message, current_balance - p_amount AS new_balance;
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

-- Dump completed on 2025-02-04 14:47:25
