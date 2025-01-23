const db = require('../database');

const account = {
    withdraw: function(account_id, amount, callback) {
        const query = 'CALL withdrawal(?, ?)';
        
        
        db.query(query, [account_id, amount], function(err, results) {
            if (err) {
                console.error("Error during withdrawal:", err);
                return callback(err); 
            }

            const result = results[0][0]; 
            callback(null, result); 
        });
    }
};

module.exports = account;
