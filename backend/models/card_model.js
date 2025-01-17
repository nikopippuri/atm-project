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
return db.query('INSERT INTO card(card_id,pin,debit_limit,type,locked,try_left)VALUES(?,?,?,?,?,?)',[card_data.card_id,hashed_pin,card_data.debit_limit,card_data.type,card_data.locked,card_data.try_left],callback);
    })

},
update:function(upd,card_data,callback){
    bcrypt.hash(card_data.pin,10,function(err,hashed_pin){
        return db.query('UPDATE card SET pin=?,debit_limit=?,type=?,locked=?,try_left=? WHERE card_id=?',[hashed_pin,card_data.debit_limit,card_data.type,card_data.locked,card_data.try_left,upd],callback);
    })
},
delete:function(del,callback){
return db.query('DELETE FROM card WHERE card_id=?',[del],callback);

},
checkPassword:function(card_id,callback){
return db.query('SELECT pin FROM card WHERE card_id=?',[card_id],callback);
}
}

module.exports=card;