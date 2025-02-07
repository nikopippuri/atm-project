const pool = require('../database'); 

const accountModel = {
    getBalance: (account_id, callback) => {
        pool.query(
            'SELECT balance FROM account WHERE account_id = ?',
            [account_id],
            (err, results) => {
                if (err) {
                    return callback(err, null);
                }
                if (results.length === 0) {
                    return callback(null, null); 
                }
                callback(null, results[0]); 
            }
        );
    }
};

module.exports = accountModel;