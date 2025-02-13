const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', function (request, response) {
  if (request.body.card_id && request.body.pin) {
    const user = request.body.card_id;
    const pass = request.body.pin;

    card.checkPassword(user, function (dbError, dbResult) {
      if (dbError) {
        response.send("-11");
      } else {
        if (dbResult.length > 0) {
          const userData = dbResult[0];

          // 🔹 Kortin lukituslogiikka ryhmäläisesi versiosta
          if (userData.locked) {
            console.log("Kortti lukittu");
            return response.send("False");
          }

          bcrypt.compare(pass, userData.pin, function (err, compareResult) {
            if (compareResult) {
              console.log("Kirjautuminen onnistui");

              // 🔹 Arvausten nollaus (ryhmäläisesi logiikka)
              card.resetTryLeft(user, function () {
                const token = generateAccessToken({ username: user });

                // 🔹 Haetaan tilitiedot (sinun logiikkasi)
                card.getAccounts(user, function (accountError, accountResults) {
                  if (accountError) {
                    console.log("Virhe tilitietoja haettaessa:", accountError);
                    response.status(500).json({ message: 'Tietokantavirhe tilitietojen haussa' });
                  } else {
                    console.log("Tilitiedot:", accountResults);

                    // 🔹 Palautetaan vastaus, joka sisältää sinun toteutuksesi tiedot
                    response.json({
                      token: token,
                      card_type: userData.card_type === 'credit' ? 2 : userData.card_type === 'combo' ? 3 : 1,
                      fname: userData.fname,
                      lname: userData.lname,
                      accounts: accountResults,
                      message: `Tervetuloa ${userData.fname} ${userData.lname}!`
                    });
                  }
                });
              });

            } else {
              // 🔹 Väärä PIN ja arvausten vähennys (ryhmäläisesi logiikka)
              console.log("Väärä PIN");

              let remainingTries = userData.try_left - 1;
              if (remainingTries <= 0) {
                console.log("Arvaukset loppu, kortti lukitaan");
                card.lockCard(user, function () {
                  response.send("False");
                });
              } else {
                card.updateTryLeft(user, remainingTries, function () {
                  console.log("Väärä arvaus, jäljellä: " + remainingTries);
                  response.send("False");
                });
              }
            }
          });

        } else {
          console.log("Käyttäjää ei löydy");
          response.send("False");
        }
      }
    });
  } else {
    console.log("Käyttäjätunnus tai PIN puuttuu");
    response.send("False");
  }
});

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports = router;
