var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var cardRouter = require('./routes/card');
var loginRouter = require('./routes/login');
var transactionRouter = require('./routes/transactions');
const jwt = require('jsonwebtoken');

const swaggerJsdoc = require("swagger-jsdoc");
const swaggerUi = require("swagger-ui-express");

const app = express();
app.use(express.json());

const withdrawRouter = require('./routes/withdraw');
app.use('/api', withdrawRouter);

app.use(logger('dev'));
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));




//swagger
const options = {
  definition: {
      openapi: "3.1.0",
      info: {
          title: "Express API with Swagger",
          version: "0.1.0",
          description: "ATM Transactions & Card CRUD API"
      },
      servers: [
          {
              url: "http://localhost:3001",
          },
      ],
      components: {
        securitySchemes:{
          BearerAuth:{
            type:"http",
            scheme:"bearer",
            bearerFormat:"JWT"
          }
        }
  },
  security:[
    {
      BearerAuth:[],
    }
  ]
},
apis: ['./routes/*.js'],
};
const specs = swaggerJsdoc(options);

app.use("/swagger", swaggerUi.serve, swaggerUi.setup(specs, { explorer: true }));;
app.use('/', indexRouter);
app.use('/login', loginRouter);
app.use(authenticateToken);
app.use('/card', cardRouter);
app.use('/transactions', transactionRouter);

const port = 3001; 
app.listen(port, function() {
  console.log("Sovellus kuuntelee porttia " + port);
});

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)

      req.user = user
  
      next()
    })
  }



module.exports = app;
