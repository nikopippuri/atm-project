const db = require('../database');

const transactions = {
  getAll: function(callback) {
    return db.query('select * from transaction', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from transaction where account_id=? ORDER BY timestamp DESC LIMIT 70', [id], callback);
  },
  add: function(transactions, callback) {
    return db.query(
      'insert into transaction (transaction_id,sum,timestamp,account_id) values(?,?,?,?)',
      [transactions.transaction_id, transactions.sum, transactions.timestamp, transactions.account_id],
      callback);
    },
  update: function(id, transactions_data, callback){
    return db.query(
      'UPDATE transaction SET sum=?, timestamp=?, account_id=? WHERE transaction_id=?',
      [transactions_data.sum, transactions_data.timestamp, transactions_data.account_id, id],
      callback);
  },
  delete: function(id, callback){
    return db.query(
      'DELETE FROM transaction WHERE transaction_id=?',[id],
      callback);
  },
};
  
module.exports = transactions;