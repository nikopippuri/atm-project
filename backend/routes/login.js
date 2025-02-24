const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

// Saadaan käyttäjältä requestina card_id ja pin-koodi

router.post('/', function (request, response) {
  if (request.body.card_id && request.body.pin) {

    const user = request.body.card_id;
    const pass = request.body.pin;

    // Vertaa salasanaa ja käyttäjätunnusta tietokannasta löytyviin

    card.checkPassword(user, function (dbError, dbResult) {
      if (dbError) {
        response.send("-11");
      } else {
        if (dbResult.length > 0) {
          const userData = dbResult[0];

          // Jos tietokannasta löytyy kortin tiedoilla locked = 1, ilmoitetaan siitä ja palautetaan False1

          if (userData.locked) {
            console.log("Kortti lukittu");
            return response.send("False1");
          }

          // Pin koodi on ollut oikein

          bcrypt.compare(pass, userData.pin, function (err, compareResult) {
            if (compareResult) {
              console.log("Kirjautuminen onnistui");

              // Arvausten nollataan aina onnistuneen kirjautumisen jälkeen

              card.resetTryLeft(user, function () {
                const token = generateAccessToken({ username: user });

                // Hakee kortin account_id ja account_typen

                card.getAccounts(user, function (accountError, accountResults) {
                  if (accountError) {
                    console.log("Virhe tilitietoja haettaessa:", accountError);
                    response.status(500).json({ message: 'Tietokantavirhe tilitietojen haussa' });
                  } else {
                    console.log("Tilitiedot:", accountResults);

                    // Palautetaan responsena vastaus, joka sisältää json muodossa (token,card_type,fname,lname,message)

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

              // Väärä PIN  koodi syötetty ja jäljellä olevia arvauksia vähennetään

              console.log("Väärä PIN");

              let remainingTries = userData.try_left - 1;
              if (remainingTries <= 0) {
                console.log("Arvaukset loppu, kortti lukitaan");
                card.lockCard(user, function () {
                  response.send("False2");
                });
              } else {
                card.updateTryLeft(user, remainingTries, function () {
                  console.log("Väärä arvaus, jäljellä: " + remainingTries);
                  response.send("False3");
                });
              }
            }
          });

        } else {
          console.log("Käyttäjää ei löydy");
          response.send("False4");
        }
      }
    });
  } else {
    console.log("Käyttäjätunnus tai PIN puuttuu");
    response.send("False5");

  }
});

// Tokenin luontiin funktio

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports = router;
