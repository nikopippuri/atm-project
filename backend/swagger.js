const express = require('express'); 
const swaggerJSDoc = require("swagger-jsdoc");
const swaggerUi = require("swagger-ui-express");
const cardRouter = require('./routes/card');
const transactionRouter = require('./routes/transactions');

const app = express(); 

app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(express.json());

app.use('/card', cardRouter);
app.use('/transactions',transactionRouter);

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
                url: "http://localhost:3000",
            },
        ],
    },
    apis: ['./routes/*.js'],
};
const specs = swaggerJSDoc(options);
app.use(
    "/swagger",
    swaggerUi.serve,
    swaggerUi.setup(specs, { explorer: true })
);

const port = 3000; 
app.listen(port, function() {
    console.log("Sovellus kuuntelee porttia " + port);
});


module.exports = app;
