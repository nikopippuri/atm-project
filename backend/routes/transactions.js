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
 *          description: The primary key of the transaction
 *        sum:
 *          type: number
 *          format: decimal(10,2)
 *          description: The sum of the transaction
 *        timestamp:
 *          type: string
 *          format: date-time
 *          description: When the transaction was made
 *        account_id:
 *          type: integer
 *          description: ID of the account who made the transaction
 */

/**
 * @swagger
 * tags:
 *   - name: transactions
 *     description: CRUD operations for the transactions table.
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
 *     summary: Create a new transaction (use timestamp format:2025-02-11 05:56:29)
 *     tags:
 *       - transactions
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             $ref: '#/components/schemas/transactions'
 *     responses:
 *       201:
 *         description: New transaction created
 *         content:
 *           application/json:
 *             schema:
 *               $ref: '#/components/schemas/transactions'
 */

/** 
 * @swagger
 * /transactions/{id}:
 *   get:
 *     summary: Get a transaction by ID
 *     tags:
 *       - transactions
 *     parameters:
 *       - name: id
 *         in: path
 *         required: true
 *         schema:
 *           type: integer
 *     responses:
 *       200:
 *         description: Transaction details
 *         content:
 *           application/json:
 *             schema:
 *               $ref: '#/components/schemas/transactions'
 */

/** 
 * @swagger
 * /transactions/{id}:
 *   put:
 *     summary: Update a transaction by ID
 *     tags:
 *       - transactions
 *     parameters:
 *       - name: id
 *         in: path
 *         required: true
 *         schema:
 *           type: integer
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             $ref: '#/components/schemas/transactions'
 *     responses:
 *       200:
 *         description: Transaction updated
 */

/** 
 * @swagger
 * /transactions/{id}:
 *   delete:
 *     summary: Delete a transaction by ID
 *     tags:
 *       - transactions
 *     parameters:
 *       - name: id
 *         in: path
 *         required: true
 *         schema:
 *           type: integer
 *     responses:
 *       204:
 *         description: Transaction deleted successfully
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