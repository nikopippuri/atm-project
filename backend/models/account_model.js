const db = require('../database'); 

const account = {
    withdraw: function(account_id, amount, callback) {
        
        if (isNaN(amount) || amount <= 0) {
            return callback(new Error('Invalid withdrawal amount'));
        }

       
        const checkBalanceQuery = 'SELECT balance FROM account WHERE account_id = ?';
        
        db.query(checkBalanceQuery, [account_id], function(err, results) {
            if (err) {
                console.error("Database error:", err);
                return callback(err); 
            }

           
            if (results.length === 0) {
                console.error("No account found with ID:", account_id);
                return callback(new Error('Account not found'));
            }

            const currentBalance = results[0].balance; 

            
            if (currentBalance < amount) {
                return callback(new Error('Insufficient funds'));
            }

            
            const newBalance = currentBalance - amount;
            const updateBalanceQuery = 'UPDATE account SET balance = ? WHERE account_id = ?';

            
            db.query(updateBalanceQuery, [newBalance, account_id], function(err, result) {
                if (err) {
                    console.error("Error updating balance:", err);
                    return callback(err); 
                }
                
                callback(null, { message: 'Withdrawal successful', newBalance }); 
            });
        });
    }
};


module.exports = account;
