const dotenv = require('dotenv');
const mysql = require('mysql2');
 
dotenv.config();
 
 
const connection = mysql.createPool({
    host: process.env.SQL_HOST,
    user: process.env.SQL_USER,
    password: process.env.SQL_PASSWORD,
    database: process.env.SQL_DATABASE,
    waitForConnections: true,
    connectionLimit: 10,
    queueLimit: 0
});
 
module.exports = connection;