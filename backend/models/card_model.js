const db=require('../database');
const bcrypt=require('bcryptjs');

const card={
getAll:function(callback){
    return db.query('SELECT * FROM card', callback);
},
getById:function(id,callback){
    return db.query('SELECT * FROM card WHERE card_id=?',[id],callback);
},
add:function(card_data,callback){
    bcrypt.hash(card_data.pin, 10,function(err, hashed_pin){
return db.query('INSERT INTO card(card_id,pin,locked,try_left,account_id)VALUES(?,?,?,?,?)',[card_data.card_id,hashed_pin,card_data.locked,card_data.try_left,card_data.account_id],callback);
    })

},
update:function(upd,card_data,callback){
    bcrypt.hash(card_data.pin,10,function(err,hashed_pin){
        return db.query('UPDATE card SET pin=?,locked=?,try_left=? WHERE card_id=?',[hashed_pin,card_data.locked,card_data.try_left,upd],callback);
    })
},
delete:function(del,callback){
return db.query('DELETE FROM card WHERE card_id=?',[del],callback);

},

checkPassword: function(card_id, callback) {
    return db.query(`
        SELECT c.pin, c.card_type, cu.fname, cu.lname, try_left, locked
        FROM card c
        JOIN customer cu ON c.customer_id = cu.customer_id
        WHERE c.card_id = ?
    `, [card_id], callback);
},

getAccounts: function(card_id, callback) {
    const query = 'SELECT account_id, account_type FROM account WHERE card_id = ?';
    db.query(query, [card_id], function(err, results) {
      if (err) {
        console.error("Database query error:", err);
        callback(err, null);
      } else {
        callback(null, results);
      }
    });
  },


// päivittää yritysten määrän
updateTryLeft: function (card_id, tries, callback) {
    return db.query('UPDATE card SET try_left=? WHERE card_id=?', [tries, card_id], callback);
},
// lukitsee kortin
lockCard: function (card_id, callback) {
    return db.query('UPDATE card SET locked=1 WHERE card_id=?', [card_id], callback);
},
// onnistuneen kirjautumisen jälkeen nollaa käytetyt arvaukset
resetTryLeft: function (card_id, callback) {
    return db.query('UPDATE card SET try_left=3 WHERE card_id=?', [card_id], callback);
}
}


module.exports=card;