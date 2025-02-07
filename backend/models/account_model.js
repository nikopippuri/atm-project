const db = require('../database');

const account = {
    withdraw: function(account_id, amount, callback) {
        const query = 'CALL withdrawal(?, ?)';

        db.query(query, [account_id, amount], function(err, results) {
            if (err) {
                console.error("Error during withdrawal:", err);
                return callback(null, { message: err.sqlMessage || "Tuntematon virhe" });
            }

            if (results && results[0] && results[0][0]) {
                callback(null, results[0][0]); // Palauttaa { message: "Nosto onnistui" } tai muu viesti
            } else {
                callback(null, { message: "Tuntematon virhe nostossa" });
            }
        });
    }
};

module.exports = account;