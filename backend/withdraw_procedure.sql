// aja tämä omassa tietokannassa
DELIMITER //

 PROCEDURE `withdrawal`(
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
    END
DELIMITER ;