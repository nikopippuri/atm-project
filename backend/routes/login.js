const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.card_id && request.body.pin){
      const user = request.body.card_id;
      const pass = request.body.pin;
      
        card.checkPassword(user, function(dbError, dbResult) {
          if(dbError){
            response.send("-11");
          }
          else{
            if (dbResult.length > 0) {
             bcrypt.compare(pass,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");

                  console.log("dbResult:", dbResult[0]);

                  const cardType = dbResult[0].card_type;
                  let cardTypeInt = 1;  // Oletuksena debit
  
                  if (cardType === 'credit') {
                    cardTypeInt = 2;
                  } else if (cardType === 'combo') {
                    cardTypeInt = 3;
                    
                  }
                  const token = generateAccessToken({ username: user });

                  response.json({
                    token: token,
                    card_type: cardTypeInt,
                    fname: dbResult[0].fname,
                    lname: dbResult[0].lname,
                                message: `Tervetuloa ${dbResult[0].fname} ${dbResult[0].lname}!`
                  });

                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("username or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;