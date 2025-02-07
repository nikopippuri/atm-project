/**
 *@swagger
 *components:
 *  schemas:
 *    transactions:
 *      type: object
 *      required:
 *        - transaction_id
 *        - sum
 *        - timestamp
 *        - account_id
 *      properties:
 *        transaction_id:
 *          type: integer
 *          description: The primary key of the card
 *        sum:
 *          type: integer
 *          description: The sum of transaction
 *        timestamp:
 *          type: integer
 *          description: When the transaction was made
 *        account_id:
 *          type: integer
 *          description: ID of the account who made the transaction
 */

/**
 * @swagger
 * tags:
 *   - name: transactions
 *     description: CRUD operations for transaction table.
 */

/** 
 * @swagger
 * /transactions:
 *   get:
 *     summary: Lists all transactions
 *     tags:
 *       - transactions
 *     responses:
 *       200:
 *         description: Lists all transactions
 *         content:
 *           application/json:
 *             schema:
 *               type: array
 *               items:
 *                 $ref: '#/components/schemas/transactions'
 */

/** 
 * @swagger
 * /transactions:
 *   post:
 *     summary: Make a new transaction
 *     tags:
 *       - transactions
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             $ref: '#/components/schemas/transactions'
 *     responses:
 *       200:
 *         description: New transaction was made
 *         content:
 *           application/json:
 *             schema:
 *               items:
 *                 $ref: '#/components/schemas/transactions'
 */



const express = require('express');
const router = express.Router();
const transactions = require('../models/transactions_model');


router.get('/', function(req,res){
    transactions.getAll(function(err,result){
        if(err) {
            res.json(err)
        }
    
        else { 
        res.json(result);
    }
})
});

router.get('/:id',
    function (request, response) {
        transactions.getById(request.params.id, function (err, result) {
            if (err) {
                response.json(err);
            } else {
                response.json(result);
            }
        })
    });

    router.post('/', 
        function(request, response) {
          transactions.add(request.body, function(err, result) {
            if (err) {
              response.json(err.errno);
              console.log(err)
            } else {
              response.json(result.affectedRows);
            }
          });
        });    

        router.put('/:id', function(request, response) {
            transactions.update(request.params.id, request.body, function(err, result) {
              if (err) {
                response.json(err.errno);
                console.log(err)
              } else {
                response.json(result.changedRows);
              }
            });
          });    

        router.delete('/:id', function(request,response){
          transactions.delete(request.params.id,function(err, result) {
            if (err) {
              response.json(err.errno);
              console.log(err)
            } else {
              response.json(result);
            }
          });
        });    


module.exports=router;