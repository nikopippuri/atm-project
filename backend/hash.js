const bcrypt = require('bcrypt');
 
// Alkuperäinen PIN-koodi
const pin = '99';
 
// Hajautuksen luominen
bcrypt.hash(pin, 10, function(err, hashedPin) {
    if (err) {
        console.error('Virhe hajauttaessa:', err);
    } else {
        console.log('Hajautettu PIN:', hashedPin);
        // Kopioi tämä arvo tietokannan "pin"-kenttään
    }
});