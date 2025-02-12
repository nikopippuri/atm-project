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

      card.getById(user, function (dbError, dbResult) {
          if (dbError) {
              response.send("-11");
          } else {
              if (dbResult.length > 0) {
                  const userData = dbResult[0];  
                  console.log(userData); // Ota pois lopuksi, nayttaa konsoliin vaan mita tietoja tarjolla
                  
                  if (userData.locked) {
                      console.log("Kortti lukittu, node");
                      return response.send("False");
                  }

                  bcrypt.compare(pass, userData.pin, function (err, compareResult) {
                      if (compareResult) {
                          console.log("Success");
                          const token = generateAccessToken({ username: user });
                          
                          // Onnistuneen kirjautumisen jälkeen nollataan arvaukset
                          card.resetTryLeft(user, function () {
                              response.send(token);
                          });
                      } else {
                          console.log("Vaara salasana. Node");
                          
                          // Vahenna try_lefteista yksi arvaus ja mikali menee nollaan lukitse kortti. 
                          let remainingTries = userData.try_left - 1;
                          if (remainingTries <= 0) {
                              console.log("Arvaukset loppu, kortti lukitaan. Node");
                              card.lockCard(user, function () {
                                  response.send("False");
                              });
                          } else {
                              card.updateTryLeft(user, remainingTries, function () {
                                  console.log("Oli vaara arvaus. Arvauksia jaljella: " + remainingTries);
                                  response.send("False");
                              });
                          }
                      }
                  });
              } else {
                  console.log("User does not exist. Node");
                  response.send("False");
              }
          }
      });
  } else {
      console.log("Username or password missing. Node");
      response.send("False"); 
  }
});

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;